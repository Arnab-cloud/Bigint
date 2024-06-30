# Bigint Class

## Overview
The **Bigint** class implements **arbitrary-precision arithmetic** for **integers**. It supports **addition, subtraction, multiplication (both traditional and using FFT), comparison operations, and more**. There is **no bound to the size** of the number.

## Dependencies
- Standard C++ libraries
- FFT library (included in Fft.h)
## Building
To build the project, use the provided **Makefile**. Navigate to the root directory and run:
```bash
make all
```
This will compile the source files and create an executable.

## Usage
### Constructors
The class provides several constructors:

- **`Bigint():`** Default constructor initializes with `0`.
- **`Bigint(const std::string& num)`**: Constructs from a string representation of a number.
### Asignment
```cpp
Bigint a("12345");
Bigint b = a;
// or
b = "-45799" // can be used
```
### Arithmetic Operations
Each arithmatic operation can be performed either with **Bigint** type or string type.
Operators such as 
```cpp
+= 
-=
*=
```
Can be used 
#### Addition
```cpp
Bigint a("123");
Bigint b("456");
Bigint sum = a + b;
sum = a + "1000";
// or
sum = a + "-1000";
```
#### Subtraction
```cpp
Bigint a("123");
Bigint b("456");
Bigint diff = a - b;
diff = a - "1000";
// or
diff = a - "-1000";
```
#### Multiplication: Traditional
```cpp
Bigint a("123");
Bigint b("456");
Bigint product = a * b;
```
#### FFT-based Multiplication
```cpp
Bigint a("123");
Bigint b("456");
Bigint fftProduct = a.mulFFT(b);
```
### Input and Output
```cpp
Bigint num;
std::cin >> num;  // Input a Bigint number
std::cout << num; // Output the Bigint number
```
### Comparison
```cpp
Bigint a("123");
Bigint b("456");

if (a == b) {
    // Equal
} else if (a < b) {
    // Less than
} else {
    // Greater than
}
```
### Power
```cpp
Bigint a("123");
Bigint b("456");
Bigint result = a ^ b;
```
## Contributing
Contributions are welcome! Please fork the repository, make your changes, and submit a pull request.

<!-- License -->
<!-- This project is licensed under the MIT License - see the LICENSE file for details. -->