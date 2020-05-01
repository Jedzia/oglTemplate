# The Database Thing Development Notes #

This project requires a C++20 conform compiler.

## Workflow ##

* Make sure the build works on GCC and CLang.
* Write Documentation
* Commit Changes  

## Build Options
option(DbThings_BuildTests "Build DbThings unit tests" ON) #-DDbThings_BuildTests:BOOL=ON
option(ENABLE_PCRE "Enable Precompiled Headers" ON) #-DENABLE_PCRE:BOOL=ON

_Todo: describe the options_ 
```
#set(CMAKE_CXX_COMPILER "clang++") #-DCMAKE_CXX_COMPILER=clang++
#set(CMAKE_TOOLCHAIN_PREFIX "llvm-")
#set(CMAKE_VERBOSE_MAKEFILE ON) #-DCMAKE_VERBOSE_MAKEFILE:BOOL=ON
```

TAKE A LOOK AT E:\Projects\Elektronik\ARM\stlink\cmake\*. Nice implementation of compiler config.

## Building under Windows/MSYS2
Use the provided `start-clion-msys2.bat`, `shell-msys2.bat` and `shell-msys2win.bat` scripts to start a shell with
the appropriate toolchain or tweak the existing ones. Where
- **start-clion-msys2.bat:** is the startup script to call the IDE and the generator is 
  `-G"CodeBlocks - MinGW Makefiles"`, 
- **shell-msys2.bat:** starts a native windows cmd prompt with adjusted paths for use with 
  `-G"CodeBlocks - MinGW Makefiles"`,
- and **shell-msys2win.bat:** invokes a native terminal MSys session for use with `-G"MSYS Makefiles"`.

### Building under Windows command prompt

* Build documentation under MSys/Clang/Clion Terminal. Config is for mingw32-make.
  Here the CMake-Option `-DENABLE_DOXYGEN:BOOL=ON` is used to switch doc generation on.

        E:\Projects\C++\oglTemplate\cmake-build-debug>
        "C:\Program Files\JetBrains\CLion\bin\cmake\win\bin\cmake.exe" --build E:\Projects\C++\oglTemplate\cmake-build-debug --target GrCore_doxygen-docs -- -j4

### Building under MSys2 native terminal

* Build documentation

        cmake .. -G"MSYS Makefiles" -DENABLE_DOXYGEN:BOOL=ON
        make GrCore_doxygen-docs    


### Obsolete?:
Obsolete:
> Use `MSYS2 MSYS` to start the shell. `The MSYS2 MinGW 32-bit` or `MSYS2 MinGW 64-bit` 
> links will not work and produce 
> ```
> System is unknown to cmake 
> Platform/MINGW64_NT-6.1
> ```
> errors when configuring with **CMake**.
------------------------------------------------------------------------------------------------------

> ##### Does not work with MSYS2 (Obsolete? use the right tools. cmake from mingw for -G"UNIX MAKEFILES"...)
> std gcc 7 works fine
> ```
> Jedzia@pubsiX MSYS ~
> $ gcc --version
> gcc (GCC) 7.3.0
> ```
> , but `export PATH=/d/Users/Jedzia.pubsiX/.cargo/bin:/mingw64/bin:${PATH}` in `.bash_profile`
> for using a different toolset has problems with **cotire**.
> ```
> Jedzia@pubsiX MSYS ~
> $ export PATH=/mingw64/bin:${PATH}
> 
> Jedzia@pubsiX MSYS ~
> $ gcc --version
> gcc.exe (Rev3, Built by MSYS2 project) 8.2.0
> ```
------------------------------------------------------------------------------------------------------

## Evolution ##

    playground/grgraphics/simple_window.cpp -> playground/grgraphics/simple_cursor.cpp
     |
     |-> playground/grgraphics/simple_graph.cpp
     |
     v
     |-> playground/grgraphics/simple_tilemap.cpp
     v
    playground/grgraphics/simple_backscroll.cpp

## Notes ##

CMake option `-DBUILD_SHARED_LIBS=TRUE` does not work with fmt -> https://github.com/fmtlib/fmt/issues/1204
> vitaut commented on Nov 17, 2019
>
> Looks like a GCC bug: https://gcc.gnu.org/bugzilla/show_bug.cgi?id=50044. A possible workaround is to define 
> `FMT_EXTERN_TEMPLATE_API` to `FMT_API` on MinGW or use a static library. Closing as this is not a bug in {fmt} but 
> would be happy to accept a PR to workaround the issue.

    Jedzia@pubsiX MINGW64 /e/Projects/C++/GrCore/cmake-build-debug/bin
    $ VERBOSE=1 cmake --build "E:\Projects\C++\GrCore\cmake-build-debug" --target GrCoreBench_unity -- -j 4


-----------------------------------------------------------------------------------------------
###### 29.03.2020 23:55 ToDo 

Utilize Q:\Projects\C++\HumbugGL\projects\Humbug\src\HumbugFileLoader.cpp for the new VFS

 

### Devel Links ###

https://github.com/ocornut/imgui
https://github.com/ocornut/imgui/blob/master/examples/example_glfw_opengl3/main.cpp
https://github.com/ocornut/imgui/issues/2096
https://www.google.de/search?sxsrf=ALeKk026L-o6H0fEUBoENIIuNQGPjF4p1A%3A1583230298394&source=hp&ei=Wi1eXuPqFYaRk74P2P26qA0&q=gl3w.h&oq=gl3w.h&gs_l=psy-ab.3..0j0i30l4j0i5i30l2.117.117..794...0.0..0.119.119.0j1......0....2j1..gws-wiz.trpQPPrqliM&ved=0ahUKEwjj_5-8iP7nAhWGyMQBHdi-DtUQ4dUDCAc&uact=5
https://github.com/ocornut/imgui/issues/880
https://www.khronos.org/opengl/wiki/OpenGL_Loading_Library
https://github.com/cginternals/glbinding
https://github.com/cginternals/glbinding/blob/master/source/examples/callbacks/main.cpp
https://github.com/cginternals/glbinding/blob/master/source/examples/cubescape-log/main.cpp
https://github.com/cginternals/glbinding/blob/master/source/examples/cubescape/main.cpp
https://github.com/cginternals/glbinding#basic-example
https://github.com/glfw/glfw
https://github.com/cginternals/glbinding/wiki/examples#callbacks
https://github.com/anholt/libepoxy/tree/49bec45b281d2beda4dff64c8ebf832adbdc7c92
https://github.com/anholt/libepoxy/search?q=main%28&unscoped_q=main%28
https://github.com/anholt/libepoxy/blob/49bec45b281d2beda4dff64c8ebf832adbdc7c92/test/wgl_core_and_exts.c
https://github.com/anholt/libepoxy/blob/49bec45b281d2beda4dff64c8ebf832adbdc7c92/test/wgl_usefontbitmaps.c
