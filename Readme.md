GrCore - Fast File IO and Serialization.
=========================================================

Bla Bla Bla Haha

## ToDo ##
- Bring doc/ up to date

## Notes ##

CMake option `-DBUILD_SHARED_LIBS=TRUE` does not work with fmt -> https://github.com/fmtlib/fmt/issues/1204
> vitaut commented on Nov 17, 2019
>
> Looks like a GCC bug: https://gcc.gnu.org/bugzilla/show_bug.cgi?id=50044. A possible workaround is to define 
> `FMT_EXTERN_TEMPLATE_API` to `FMT_API` on MinGW or use a static library. Closing as this is not a bug in {fmt} but 
> would be happy to accept a PR to workaround the issue.

    Jedzia@pubsiX MINGW64 /e/Projects/C++/GrCore/cmake-build-debug/bin
    $ VERBOSE=1 cmake --build "E:\Projects\C++\GrCore\cmake-build-debug" --target GrCoreBench_unity -- -j 4


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
