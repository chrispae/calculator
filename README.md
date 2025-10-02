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
  - [ ] ~~provide handbuilt heap implementation to store all terms~~
    - creating tree only implicit through recursive term splitting
  - [ ] add operators
    - [x] addition
    - [x] substraction
    - [x] multiplication
    - [x] division
    - [x] exponentiation
    - [x] modulo
    - future functionality: logarithmus, sin, cos, tan, ...
  - [x] add brackets for encapsulation of terms
- [ ] provide build system for demos and library
  - [x] basic build structure has been established
    - calculator is header-only currently
- [ ] add tests to ensure correct calculations
  - [x] dummy test with `googletest` has been established
  - [x] test for basic calculations have been added
