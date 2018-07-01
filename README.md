# GM WatchDog

GM Watchdog is a plugin for any GMod server that can detect problems with server execution, and take appropriate action (usually restarting the server executable)

# How Do I Use It?

GM WatchDog is written in C++, and needs to be loaded by the server as a module. 

First, WatchDog needs to be built. There is a visual studio project provided: ```watchdog\windows-vs2010\gmsv_watchdog.sln```. The file is configured for use with visual studio 2017, but may work with other versions. If you don't feel like building it yourself, a binary can be downloaded here: https://drive.google.com/file/d/1N39DHRAS1ichBjcF2i5K7PBksLdVr_BV/view?usp=sharing

If you've already compiled the binary module, or downloaded it pre-built, you can now install it.

To do this, place **gmsv_watchdog_win32.dll** into the folder ```garrysmod\lua\bin\``` located in the directory of your server executable.

This won't enable the timer by itself. To do this, we need to start it with a lua script. The recommended way of doing this would be to use the following in a script located in ```garrysmod\lua\autorun\server```.

``` lua
local lib = require('watchdog')

timeout = 5000 -- 5 second timeout
WatchdogStart(timeout) -- Start the watchdog timer

hook.Add("Tick", "Watchdog", KickDog)
```

# Compiling
Before we can compile the project, we need a few things. These are  the **boost** library, and the **hl2sdk-gmod** files.
## *Boost*
To get boost, download the boost windows binaries and source files here: https://sourceforge.net/projects/boost/files/boost-binaries/1.67.0/boost_1_67_0-msvc-14.1-32.exe/download

Install the library to the location of your choice.

## *hl2sdk-gmod*
This is simply a collection of source code for gmod. It is a derivative of the hl2sdk from allied modders. You can download the origional here: https://github.com/alliedmodders/hl2sdk/tree/gmod. To get everything to compile, I had to make a slight modification to hl2sdk, but cant remember what the modification was. For now, i've uploaded my modified version here: https://drive.google.com/file/d/1ISXEkYH4Oyj9Ax8F7EsCp6hr5DZhc8Vf/view?usp=sharing

Extract the files to a folder of your 

## *Configuration*
Open up the project file in visual studio. We need to set the appropriate include and lib directories. Right click the project (inside of the solution), and click **properties**. Under **C/C++** go to **General**. In **Additional Include Directories** paste this (assuming you extracted to **D:\hl2sdk-gmod**):

```D:\hl2sdk-gmod\game\client\hl2;D:\hl2sdk-gmod\vstdlib;D:\hl2sdk-gmod\vpc_scripts;D:\hl2sdk-gmod\vgui2;D:\hl2sdk-gmod\utils;D:\hl2sdk-gmod\tier1;D:\hl2sdk-gmod\tier0;D:\hl2sdk-gmod\raytrace;D:\hl2sdk-gmod\mathlib;D:\hl2sdk-gmod\materialsystem;D:\hl2sdk-gmod\lib;D:\hl2sdk-gmod\gcsdk;D:\hl2sdk-gmod\game\shared;D:\hl2sdk-gmod\game\server;D:\hl2sdk-gmod\game\client;D:\hl2sdk-gmod\game;D:\hl2sdk-gmod\fgdlib;D:\hl2sdk-gmod\dx9sdk;D:\hl2sdk-gmod\dx10sdk;D:\hl2sdk-gmod\devtools;D:\hl2sdk-gmod\public\engine;D:\hl2sdk-gmod\public\fgdlib;D:\hl2sdk-gmod\public\filesystem;D:\hl2sdk-gmod\public\Friends;D:\hl2sdk-gmod\public\g15;D:\hl2sdk-gmod\public\game;D:\hl2sdk-gmod\public\haptics;D:\hl2sdk-gmod\public\inputsystem;D:\hl2sdk-gmod\public\jpeglib;D:\hl2sdk-gmod\public\keyframe;D:\hl2sdk-gmod\public\materialsystem;D:\hl2sdk-gmod\public\mathlib;D:\hl2sdk-gmod\public\matsys_controls;D:\hl2sdk-gmod\public\maya;D:\hl2sdk-gmod\public\mdllib;D:\hl2sdk-gmod\public\p4lib;D:\hl2sdk-gmod\public\particles;D:\hl2sdk-gmod\public\phonemeextractor;D:\hl2sdk-gmod\public\scenefilecache;D:\hl2sdk-gmod\public\shaderapi;D:\hl2sdk-gmod\public\shaderlib;D:\hl2sdk-gmod\public\SoundEmitterSystem;D:\hl2sdk-gmod\public\soundsystem;D:\hl2sdk-gmod\public\sourcevr;D:\hl2sdk-gmod\public\steam;D:\hl2sdk-gmod\public\tier0;D:\hl2sdk-gmod\public\tier1;D:\hl2sdk-gmod\public\tier2;D:\hl2sdk-gmod\public\tier3;D:\hl2sdk-gmod\public\togl;D:\hl2sdk-gmod\public\toolframework;D:\hl2sdk-gmod\public\tools;D:\hl2sdk-gmod\public\unicode;D:\hl2sdk-gmod\public\unitlib;D:\hl2sdk-gmod\public\vgui_controls;D:\hl2sdk-gmod\public\vaudio;D:\hl2sdk-gmod\public\vgui;D:\hl2sdk-gmod\public\VGuiMatSurface;D:\hl2sdk-gmod\public\video;D:\hl2sdk-gmod\public\vphysics;D:\hl2sdk-gmod\public\vstdlib;D:\hl2sdk-gmod\public\vtf;D:\hl2sdk-gmod\public\zip;D:\hl2sdk-gmod\public\datamodel;D:\hl2sdk-gmod\public\datacache;D:\hl2sdk-gmod\public\bitmap;D:\hl2sdk-gmod\public\avi;D:\hl2sdk-gmod\public\appframework;D:\hl2sdk-gmod\public;D:\hl2sdk-gmod\common;D:\hl2sdk-gmod```

Now we need to add the library directory, and dependencies. In **Linker** > **General** under **Additional Library Directories** add the location of the **lib\public** folder. Since I extracted to **D:\hl2sdk-gmod** I would add ```D:\hl2sdk-gmod\lib\public```

Now, move down to **Linker** > **Input**. Under **Additional Dependencies**, add: ```tier0.lib;tier1.lib;tier2.lib;tier3.lib;bitmap.lib;choreoobjects.lib;dmxloader.lib;mathlib.lib;matsys_controls.lib;nvtristrip.lib;particles.lib;raytrace.lib;steam_api.lib;vgui_controls.lib;vmpi.lib;vstdlib.lib;vtf.lib;```

Now, you should be able to build the module.

# Other Things
This module is far from being perfect. In it's current state, there are plenty of bugs that need to be fixed, and features to be added.
