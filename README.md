# rabin-karp
Efficient pattern matching of strings

## Usage
Returns position of the first instance of pattern
```
rabin-karp [text] [pattern]
```

## Installation
### Requirements
- C++17
- Cmake 3.30 or higher
- C++ Compiler
  - g++/clang for Linux
  - msvc for Windows
 
### Build
1. Create CMakeFiles
```
mkdir build
cmake -B build
```
2. Build the project
```
cmake --build ./build
```
3. Executable will be located at the `build` directory.

### Unit Tests
Unit tests are inside the `build/tests` directory.
