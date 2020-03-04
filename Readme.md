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
