# Matrix on C++
A small project on C++ for learning, which contains an implementation of matrix and different types of element matrix could contain.   
# What this project implements:
- **[Line](https://github.com/PoliOwl/c-plus-plus_matrix/blob/master/matrix/line.h):**
fixed-size sequence container with arithmetic operators(except division), equality operators, methods for adding elements and replacing them, operator [], input and output operators.
- **[Linealloc](https://github.com/PoliOwl/c-plus-plus_matrix/blob/master/matrix/linealloc.h):** 
allocator for `line`.
- **[Matrix](https://github.com/PoliOwl/c-plus-plus_matrix/blob/master/matrix/matrix.h):**
 contains a `line` with `line`s with elements of the matrix. It's a template class with three template parameters: first two are insight representing matrix size, third is elements type. This class has arithmetic operators(except division), equality operators, operator [], methods for converting rows and columns into a vector, transposing a matrix, changing rows and columns and input and output operators.
- **[BigInt](https://github.com/PoliOwl/c-plus-plus_matrix/blob/master/matrix/BigInt.h):** integer with no fix or max size.
- **[Rational](https://github.com/PoliOwl/c-plus-plus_matrix/blob/master/matrix/rational.h):** fractional, which has `BigInt` for both denominator and numerator.
- **[Finite](https://github.com/PoliOwl/c-plus-plus_matrix/blob/master/matrix/Finite.h):** implementation of elements of finite fields.
