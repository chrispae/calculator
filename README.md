# Calculator

C++ implementation of a calculator

## Usage

This project uses `cmake` as build system. The project can be build by running

```[sh]
  cmake -S . -B <build-dir>
  cmake --build <build-dir> 
```

To automatically run all provided tests, use

```[sh]
  cd <build-dir>
  ctest
```

These test have been implemented using `googletest`.

## ToDo

- [ ] implement calculator functionality
  - [ ] provide handbuilt heap implementation to store all terms
  - [ ] add operators
    - [ ] addition
    - [ ] substraction
    - [ ] multiplication
    - [ ] division
    - [ ] exponentiation
    - [ ] modulo, logarithmus, sin, cos, tan, ...
  - [ ] add brackets for encapsulation of terms
- [ ] provide build system for demos and library
  - [x] basic build structure has been established
- [ ] add tests to ensure correct calculations
  - [x] dummy test with `googletest` has been established
