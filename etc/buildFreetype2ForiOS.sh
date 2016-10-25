#!/bin/bash

# Original script from here: http://stackoverflow.com/a/27161949/1527560
# Many thanks to "Mobile Ben"!

# Modified to build freetype2 by alejandro

# I recommend to build only one platform first, to make sure everything is working fine (disable all the others).
# Then enable all the others again and let the script work on its own

SDKMINVERSION="8.0"

PLATFORMPATH="/Applications/Xcode.app/Contents/Developer/Platforms"
TOOLSPATH="/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin"
export IPHONEOS_DEPLOYMENT_TARGET="8.0"
pwd=`pwd`

findLatestSDKVersion()
{
sdks=`ls $PLATFORMPATH/$1.platform/Developer/SDKs`
arr=()
for sdk in $sdks
do
arr[${#arr[@]}]=$sdk
done

# Last item will be the current SDK, since it is alpha ordered
count=${#arr[@]}
if [ $count -gt 0 ]; then
sdk=${arr[$count-1]:${#1}}
num=`expr ${#sdk}-4`
SDKVERSION=${sdk:0:$num}
else
SDKVERSION="8.0"
fi
}

buildit()
{
target=$1
hosttarget=$1
platform=$2

if [[ $hosttarget == "x86_64" ]]; then
hostarget="i386"
elif [[ $hosttarget == "arm64" ]]; then
hosttarget="arm"
fi

export CC="$(xcrun -sdk iphoneos -find clang)"
export CPP="$CC -E"
export CFLAGS="-arch ${target} -fembed-bitcode-marker -isysroot $PLATFORMPATH/$platform.platform/Developer/SDKs/$platform$SDKVERSION.sdk -miphoneos-version-min=$SDKMINVERSION"
export AR=$(xcrun -sdk iphoneos -find ar)
export RANLIB=$(xcrun -sdk iphoneos -find ranlib)
export CPPFLAGS="-arch ${target} -fembed-bitcode-marker -isysroot $PLATFORMPATH/$platform.platform/Developer/SDKs/$platform$SDKVERSION.sdk -miphoneos-version-min=$SDKMINVERSION"
export LDFLAGS="-arch ${target} -isysroot $PLATFORMPATH/$platform.platform/Developer/SDKs/$platform$SDKVERSION.sdk"

mkdir -p $pwd/output/$target

./configure --prefix="$pwd/output/$target" --disable-shared --without-png --without-harfbuzz --host=$hosttarget-apple-darwin

make clean
make
make install
}

findLatestSDKVersion iPhoneOS

buildit armv7 iPhoneOS
buildit armv7s iPhoneOS
buildit arm64 iPhoneOS
buildit i386 iPhoneSimulator
buildit x86_64 iPhoneSimulator

LIPO=$(xcrun -sdk iphoneos -find lipo)
$LIPO -create $pwd/output/armv7/lib/libfreetype.a  $pwd/output/armv7s/lib/libfreetype.a $pwd/output/arm64/lib/libfreetype.a $pwd/output/x86_64/lib/libfreetype.a $pwd/output/i386/lib/libfreetype.a -output libfreetype.a
