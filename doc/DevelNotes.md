# The Database Thing Development Notes #

This project requires a C++17 conform compiler.

## Build Options
option(DbThings_BuildTests "Build DbThings unit tests" ON) #-DDbThings_BuildTests:BOOL=ON
option(ENABLE_PCRE "Enable Precompiled Headers" ON) #-DENABLE_PCRE:BOOL=ON

_Todo: describe the options_ 
```
#set(CMAKE_CXX_COMPILER "clang++") #-DCMAKE_CXX_COMPILER=clang++
#set(CMAKE_TOOLCHAIN_PREFIX "llvm-")
#set(CMAKE_VERBOSE_MAKEFILE ON) #-DCMAKE_VERBOSE_MAKEFILE:BOOL=ON
```

## Building under Windows/MSYS2
Use `MSYS2 MSYS` to start the shell. `The MSYS2 MinGW 32-bit` or `MSYS2 MinGW 64-bit` 
links will not work and produce 
```
System is unknown to cmake 
Platform/MINGW64_NT-6.1
```
errors when configuring with **CMake**.

### Does not work with MSYS2
std gcc 7 works fine
```
Jedzia@pubsiX MSYS ~
$ gcc --version
gcc (GCC) 7.3.0
```
, but `export PATH=/d/Users/Jedzia.pubsiX/.cargo/bin:/mingw64/bin:${PATH}` in `.bash_profile`
for using a different toolset has problems with **cotire**.
```
Jedzia@pubsiX MSYS ~
$ export PATH=/mingw64/bin:${PATH}

Jedzia@pubsiX MSYS ~
$ gcc --version
gcc.exe (Rev3, Built by MSYS2 project) 8.2.0
```