# atomic

> A C++ atomics library that refines the standard atomic interface.

**Refined interface**&ensp;
`atomic` is an atomics library written in C++.
It refines the standard atomic interface's load operation, dividing it into two categories: strong and weak loads.
*Strong loads* are guaranteed to retrieve the globally latest written value of a variable, while *weak loads* might retrieve out of date values (the default behaviour for atomic loads).
This distinction is useful when writing lock-free algorithms with relaxed atomics.

**Shorthand notation**&ensp;
Shorthand notations for atomic operations are provided that save the hassle of writing `std::memory_order_*`, making the memory order part of the function name directly.

**Lockfree queue**&ensp;
`atomic` contains a lockfree queue implementation.

## License

`atomic` is released under the GNU Affero General Public License, version 3 or later (AGPLv3+).
A copy of the license text can be found in the `LICENSE` file.

## Compiling

Make sure you have a reasonably recent version of CMake installed.
Navigate into the `atomic` directory, and execute:

	cmake .

Now, an include directory has been created in `include/`, which can be used to import the library into other projects.
A makefile (or project files, depending on your setup) has been generated, which can be used to build the library.