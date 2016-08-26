#!/bin/sh
cd ../../

mkdir OSXIncludes
cd OSXIncludes

ln -s /Library/Frameworks/SDL2.framework/Versions/A/Headers SDL2

ln -s /Library/Frameworks/SDL2_mixer.framework/Versions/A/Headers SDL2_mixer

ln -s /Library/Frameworks/SDL2_image.framework/Versions/A/Headers SDL2_image

echo done.
