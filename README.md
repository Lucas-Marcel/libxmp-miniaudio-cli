# libxmp-miniaudio-cli
A simple cli to play mod tracker files with libxmp that uses miniaudio as playback. 

you need libxmp and miniaudio libraries to build this project. You can download them from these pages:

https://github.com/libxmp/libxmp/tree/master/lite

https://github.com/mackron/miniaudio


This project uses xmp lite which is aimed at game development, but you can use regular xmp if that's the case.



When compiling On Windows and macOS you need to link to -lxmp-lite. On Linux just link to -lpthread, -lm -ldl and -lxmp-lite


For more information, read libxmp and miniaudio documentation. 

https://xmp.sourceforge.net/libxmp.html


https://miniaud.io/docs/

To understand more the appeal of trackers specially for game dev: https://www.youtube.com/watch?v=roBkg-iPrbw


