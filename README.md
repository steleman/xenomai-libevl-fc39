Xenomai LibEVL on Fedora 39
===========================

What's this?
------------

See [https://evlproject.org/overview/](https://evlproject.org/overview/)

This is a port of `libevl` for Fedora 39 with Linux Kernel `6.10.10`. You can find the sources and build system for Linux `6.10.10` here on Github:

[https://github.com/steleman/xenomai-fc39](https://github.com/steleman/xenomai-fc39)

It's based on `libevl` release 49. That's because of the ABI Compatibility Level (36) required by the Linux Kernel `6.10.10`'s `evl` header files. You need to build and install the Xenomai Linux Kernel to use `libevl`.

I have made changes to `include/evl/atomic.h`. The original implementation created two different - and incompatible - types for the `atomic_t` type: one for C, the other for C++. The C++ Standard doesn't guarantee compatibility of `std::atomic<T>` with C11's `_Atomic` type until C++23. And that compatibility is not even guaranteed, it needs to be feature-tested:

[https://en.cppreference.com/w/cpp/header/stdatomic.h](https://en.cppreference.com/w/cpp/header/stdatomic.h)

`libevl` might very well be used in mixed C / C++ development. This is a problem. I solved this problem by using compiler builtins for the atomic operations used in `atomic.h`. The builtins work identically in C and in C++, and `atomic_t` becomes a simple `int`. The Linux kernel only builds with GCC and / or GCC-compatible compilers. `clang` supports GCC's `atomic` builtins. Commercial compilers that can build the Linux Kernel - from Intel, AMD or ARM - are all based on `clang` at this point.

How to build?
-------------

See [https://evlproject.org/core/build-steps/](https://evlproject.org/core/build-steps/)

