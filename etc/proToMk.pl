#!/usr/bin/perl

use strict;

# Take the contents of a *.pro file and make it a *.mk file for Android compilation. End the nonsense with forgetting to add new files and other Scheiße


### Configurables

# List of known files to be excluded

my @excludeList = ('keyboardcontrol', 'main', 'ComputerInput');



# Remove the $${MJENGINE} prefix?

my $removePrefix = '\$\$\{MJENGINE\}\/';



# Is part of the engine

my $engineFile = 'mj.+\.cpp|extLibs';

my $cppExtension = '\.cpp|\.c';



# Get the boilerplate out of the way

my $boilerplateStart = 
'
# Copyright (C) 2014-2017 Alejandro Valenzuela Roca
#
';



my $boilerplateContinue =
'
#
# -------------

# no idea what this does but if you remove it the world ends so better not touch it
# ndk-build works in mysterious ways, whatever
LOCAL_PATH:= $(call my-dir)




# getting libPNG into the project
include $(CLEAR_VARS)

LOCAL_MODULE    := png
LOCAL_SRC_FILES := precompiled/png/$(TARGET_ARCH_ABI)/libpng.a

include $(PREBUILT_STATIC_LIBRARY)
# -------------

# getting freetype2 into the project
include $(CLEAR_VARS)

LOCAL_MODULE    := freetype2
LOCAL_SRC_FILES := precompiled/freetype2/$(TARGET_ARCH_ABI)/libfreetype.a

include $(PREBUILT_STATIC_LIBRARY)
# -------------
';



my $boilerplateEngineOnly = 
'

# compile the mjEngine, as a library
include $(CLEAR_VARS)


LOCAL_MODULE    := libmjEngine

LOCAL_C_INCLUDES := $(LOCAL_PATH)/extLibs/freetype2/include

# Now, the file from the engine are specified:
LOCAL_SRC_FILES := \\
';



my $boilerplateGameOnly = 
'
# getting libmjEngine into the project
include $(CLEAR_VARS)

LOCAL_MODULE    := libmjEngine
LOCAL_SRC_FILES := precompiled/mjEngine/$(TARGET_ARCH_ABI)/libmjEngine.a

include $(PREBUILT_STATIC_LIBRARY)
# -------------

# Now, the files from the game are specified:

include $(CLEAR_VARS)

LOCAL_C_INCLUDES := $(LOCAL_PATH)//extLibs/freetype2/include

LOCAL_MODULE    := libmjGame
LOCAL_SRC_FILES := \\
';



my $boilerplateMixed =
'
# Now, the files from the engine and the game are specified:

include $(CLEAR_VARS)

LOCAL_C_INCLUDES := $(LOCAL_PATH)//extLibs/freetype2/include

LOCAL_MODULE    := libmjGame
LOCAL_SRC_FILES := \\
';



my $boilerplateEngineOnlyEnd =
'
# -------------


# finally we tell ndk-build that the output is a static library. This will be included by Android Studio in the final *.so shared library - see Android.mk.gameOnly
include $(BUILD_STATIC_LIBRARY)
';



my $boilerplateGameOnlyEnd =
'
# -------------

# now, the shared and static libs to be used are specified				   
LOCAL_LDLIBS    := -llog -lGLESv2 -lz -landroid
LOCAL_STATIC_LIBRARIES := libmjEngine png freetype2

# finally we tell ndk-build that the output is a shared library. This will be loaded by Java in the android device
include $(BUILD_SHARED_LIBRARY)
';



my $boilerplateMixedEnd = 
'
# -------------

# now, the shared and static libs to be used are specified		   
LOCAL_LDLIBS    := -llog -lGLESv2 -lz
LOCAL_STATIC_LIBRARIES := png freetype2

# finally we tell ndk-build that the output is a shared library (libmjGame.so) . This will be loaded by Java in the android device
include $(BUILD_SHARED_LIBRARY)

';



# Subroutine for printing the file list into the mk file

sub printListToFile {
     my @fileListArray = @{$_[0]};
     my $file = $_[1];
     
     for (my $i = 0; $i < scalar @fileListArray; $i++)
     {
          print $file "    $fileListArray[$i]";
          if ($i < (scalar @fileListArray)-1)
          {
               print $file " \\";
          }
          print $file "\n";
     }
     
}







###### Actual script start

my $proFilename = $ARGV[0];
my $localPrefix = $ARGV[1];

my $mkFilename = "$proFilename.mk";

if (not defined $proFilename)
{
	die "Usage: proToMk.pl projectFile.pro [localPrefix]\n";
}
if (defined $localPrefix)
{
     print "Using local prefix $localPrefix...\n";
     $localPrefix = "$localPrefix\/";
} else
{
     $localPrefix = "";
}


print "Opening $proFilename, writing to $mkFilename...\n";

open(my $proFILE, '<', $proFilename);
open(my $mkFILE, '>', $mkFilename);

my @engineFiles;
my @gameFiles;

while (my $row = <$proFILE>)
{
	chomp $row;
	
	my $exclude;
	my $isNotExcluded = 1;
	
	foreach $exclude (@excludeList)
	{
          if ($row =~ /$exclude/)
          {
               print "Excluding $row..\n";
               $isNotExcluded = 0;
          
          }
	}
	
	if ($isNotExcluded)
	{
	
	     my @rowComponents;

             if ($removePrefix)
             {
               $row =~ s/$removePrefix//;
             }
	
	     if ($row =~ /$engineFile/ )
	     {
               @rowComponents = split ' ', $row;
               
               my $component;
               
               foreach $component (@rowComponents)
               {
                    if ($component =~ /$cppExtension/)
                    {
                         push @engineFiles, $component;
                    }
               }
	          
	     } elsif ($row =~ /$cppExtension/)
	     {
               @rowComponents = split ' ', $row;
               my $component;
               foreach $component (@rowComponents)
               {
                    if ($component =~ /$cppExtension/)
                    {
                         push @gameFiles, "${localPrefix}${component}";
                    }
               }
	     }
	}
	
}

print $mkFILE $boilerplateStart;

my @engineFilesSorted = sort (@engineFiles);
my @gameFilesSorted = sort(@gameFiles);

if (! scalar @gameFiles) # engine only
{
     print "Writing engine-only mk...\n";
     
     print $mkFILE "# Only the engine will be compiled, into a static library.";
     
     print $mkFILE $boilerplateContinue;
     
     print $mkFILE $boilerplateEngineOnly;
     
     printListToFile(\@engineFilesSorted, $mkFILE);
     
     print $mkFILE $boilerplateEngineOnlyEnd;
     
} elsif (! scalar @engineFiles) # game only
{
     print "Writing game-only mk...\n";

     print $mkFILE "# Only the game will be compiled. The engine will be loaded as a static library.";
     
     print $mkFILE $boilerplateContinue;
          
     print $mkFILE $boilerplateGameOnly;
     
     printListToFile(\@gameFilesSorted, $mkFILE);
     
     print $mkFILE $boilerplateGameOnlyEnd;
     
} else # compiling everything
{
     print "Writing 'everything' mk...\n";

     print $mkFILE "# EVERYTHING will be compiled. This is more of a sanity test for the system since it takes a significant amount of time to be done.";
     
     print $mkFILE $boilerplateContinue;
     
     print $mkFILE $boilerplateMixed;
     
     my @mixedFiles;
     
     push @mixedFiles, @engineFilesSorted;
     push @mixedFiles, @gameFilesSorted;
     
     
     printListToFile(\@mixedFiles, $mkFILE);

     print $mkFILE $boilerplateMixedEnd;
}

close($mkFILE);
close($proFILE);

print "Done.\n\n"

