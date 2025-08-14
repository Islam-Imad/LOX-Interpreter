# LOX Interpreter 🚀

[![MIT License](https://img.shields.io/badge/License-MIT-green.svg)](https://choosealicense.com/licenses/mit/)
[![Build Status](https://img.shields.io/badge/build-passing-brightgreen.svg)](#)
[![C++](https://img.shields.io/badge/C++-17-blue.svg)](https://isocpp.org/)

A complete **tree-walking interpreter** implementation for the **Lox programming language**, built from scratch in C++ following the principles from "Crafting Interpreters" by Robert Nystrom.

## 📋 Table of Contents

- [About the Project](#about-the-project)
- [Language Features](#language-features)
- [Quick Start](#quick-start)
- [Installation](#installation)
- [Usage](#usage)
- [Language Syntax](#language-syntax)
- [Examples](#examples)
- [Architecture](#architecture)
- [Testing](#testing)
- [Contributing](#contributing)
- [License](#license)
- [Acknowledgments](#acknowledgments)

## 🎯 About the Project

**LOX** is a dynamically-typed, interpreted programming language designed for simplicity, clarity, and educational purposes. This interpreter implements the complete Lox language specification using a **tree-walking interpreter** approach, making it an excellent resource for understanding interpreter design and implementation.

### Why Lox?

- **Educational**: Perfect for learning interpreter construction concepts
- **Simple Syntax**: C-like syntax that's easy to read and write
- **Dynamic Typing**: Flexible type system for rapid prototyping
- **Functional Features**: First-class functions, closures, and higher-order programming
- **Modern Features**: Supports contemporary programming paradigms

## ✨ Language Features

### Core Language Features
- **🔢 Arithmetic Operations**: Standard operators (`+`, `-`, `*`, `/`) plus exponentiation (`**`)
- **📦 Variables**: Dynamic variable declaration and assignment
- **🔧 Functions**: First-class functions with support for recursion and higher-order functions
- **🌊 Control Flow**: Conditional statements (`if`/`else if`/`else`) and loops (`while`/`for`)
- **🎭 Closures**: Functions that capture their lexical environment
- **📤 I/O Operations**: Built-in `print` statement for output
- **🏗️ Scoping**: Lexical scoping with proper variable resolution

### Data Types
- **Numbers**: Double-precision floating-point
- **Strings**: Unicode string support
- **Booleans**: True/false values
- **Nil**: Null/void value
- **Functions**: First-class function objects

## 🚀 Quick Start

```bash
# Clone the repository
git clone https://github.com/Islam-Imad/LOX-Interpreter.git
cd LOX-Interpreter

# Build the project
mkdir build && cd build
cmake .. && make

# Run a simple example
./lox ../Grammer/hello_world.lox
```

## 🛠️ Installation

### Prerequisites

- **C++17** compatible compiler (GCC, Clang, or MSVC)
- **CMake** 3.10 or higher
- **Git** for cloning the repository

### Build Instructions

1. **Clone the repository**:

   ```bash
   git clone https://github.com/Islam-Imad/LOX-Interpreter.git
   cd LOX-Interpreter
   ```

2. **Install CMake** (if not already installed):

   - **Linux (Ubuntu/Debian)**:
   
     ```bash
     sudo apt-get install cmake
     ```
   
   - **macOS**:
   
     ```bash
     brew install cmake
     ```
   
   - **Windows**:
     Download the installer from the [official CMake website](https://cmake.org/download/)

3. **Build the project**:

   ```bash
   mkdir build
   cd build
   cmake ..
   make
   ```

4. **Verify installation**:

   ```bash
   ./lox ../Grammer/hello_world.lox
   ```

## 📖 Usage

### Command Line Interface

The interpreter accepts a single Lox source file as an argument:

```bash
./lox <source_file.lox>
```

### Example Usage

```bash
# Run a simple hello world program
./lox ../Grammer/hello_world.lox

# Execute a Fibonacci sequence program
./lox ../Grammer/fibonaci.lox

# Test closure functionality
./lox ../Grammer/closure.lox
```

## 📝 Language Syntax

### Variables
```lox
var name = "Lox";
var age = 25;
var isActive = true;
```

### Functions
```lox
fun greet(name) {
    print "Hello, " + name + "!";
}

fun fibonacci(n) {
    if (n <= 1) return n;
    return fibonacci(n - 1) + fibonacci(n - 2);
}
```

### Control Flow
```lox
// Conditionals
if (age >= 18) {
    print "Adult";
} else {
    print "Minor";
}

// Loops
for (var i = 0; i < 10; i = i + 1) {
    print i;
}

while (condition) {
    // loop body
}
```

### Closures
```lox
fun makeCounter() {
    var count = 0;
    fun increment() {
        count = count + 1;
        return count;
    }
    return increment;
}

var counter = makeCounter();
print counter(); // 1
print counter(); // 2
```

## 🎯 Examples

## How to Run

To run the Loxie interpreter on your system, follow the steps below:

1. **Clone the repository**:
    ```bash
    git clone https://github.com/Islam-Imad/Loxie-Interpreter.git
    cd Loxie-Interpreter
    ```

2. **Install CMake**:
    - **Linux**:
      ```bash
      sudo apt-get install cmake
      ```
    - **MacOS**:
      ```bash
      brew install cmake
      ```
    - **Windows**:
      - Download the installer from [here](https://cmake.org/download/).

3. **Build the project**:
    - Create a `build` directory and navigate into it:
      ```bash
      mkdir build
      cd build
      ```
    - Generate the build files using CMake:
      ```bash
      cmake ..
      ```
    - Build the project using `make`:
      ```bash
      make
      ```

4. **Run the interpreter**:
    - Use the following command to run an example Lox script:
      ```bash
      ./lox ../Grammer/HelloWorld.lox
      ```

The `Grammer/` directory contains various example programs demonstrating different language features:

| Example | Description |
|---------|-------------|
| `hello_world.lox` | Basic print statement |
| `fibonaci.lox` | Recursive Fibonacci sequence |
| `closure.lox` | Closure and lexical scoping demonstration |
| `function.lox` | Function definition and calls |
| `for.lox` | For loop examples |
| `while.lox` | While loop examples |
| `if_else_if_else.lox` | Conditional statement examples |
| `var.lox` | Variable declaration and assignment |

### Complete Example Program

```lox
// Comprehensive example showcasing multiple features
var message = "Welcome to Lox!";
print message;

fun factorial(n) {
    if (n <= 1) {
        return 1;
    }
    return n * factorial(n - 1);
}

fun makeMultiplier(factor) {
    fun multiply(x) {
        return x * factor;
    }
    return multiply;
}

var result = factorial(5);
print "5! = " + result;

var doubler = makeMultiplier(2);
var tripler = makeMultiplier(3);

for (var i = 1; i <= 5; i = i + 1) {
    print "Double " + i + " = " + doubler(i);
    print "Triple " + i + " = " + tripler(i);
}
```

## 🏗️ Architecture

The interpreter follows a classic tree-walking design with the following components:

### Core Components

1. **Scanner** (`scanner.h/cc`): Tokenizes source code into tokens
2. **Parser** (`parser.h/cc`): Builds an Abstract Syntax Tree (AST) from tokens
3. **Interpreter** (`interpreter.h/cc`): Evaluates the AST using the visitor pattern
4. **Environment** (`object.h/cc`): Manages variable scoping and storage

### Design Patterns

- **Visitor Pattern**: Used for AST traversal and evaluation
- **Strategy Pattern**: Implemented for operator handling
- **Factory Pattern**: Token and object creation

### Project Structure

```
src/
├── include/           # Header files
│   ├── scanner.h      # Lexical analysis
│   ├── parser.h       # Syntax analysis
│   ├── interpreter.h  # Execution engine
│   ├── expression.h   # Expression AST nodes
│   ├── statement.h    # Statement AST nodes
│   └── ...
├── scanner.cc         # Scanner implementation
├── parser.cc          # Parser implementation
├── interpreter.cc     # Interpreter implementation
└── ...
```

## 🧪 Testing

The project includes comprehensive unit tests using **Google Test** framework.

### Running Tests

```bash
# Build and run all tests
cd build
ctest

# Run specific test suites
./test/test_scanner
./test/test_parser
./test/test_interpreter
```

### Test Coverage

- **Scanner Tests**: Token recognition and lexical analysis
- **Parser Tests**: AST construction and syntax validation
- **Interpreter Tests**: Expression evaluation and statement execution
- **Environment Tests**: Variable scoping and closure behavior

## 🤝 Contributing

Contributions are welcome! Here's how you can help:

### Getting Started

1. Fork the repository
2. Create a feature branch (`git checkout -b feature/amazing-feature`)
3. Make your changes
4. Add tests for new functionality
5. Ensure all tests pass (`ctest`)
6. Commit your changes (`git commit -m 'Add amazing feature'`)
7. Push to the branch (`git push origin feature/amazing-feature`)
8. Open a Pull Request

### Areas for Contribution

- **Language Extensions**: Add new operators, control structures, or built-in functions
- **Error Handling**: Improve error messages and recovery
- **Performance**: Optimize interpreter performance
- **Documentation**: Improve code documentation and examples
- **Testing**: Add more comprehensive test cases

### Code Style

- Follow C++17 best practices
- Use consistent naming conventions
- Add appropriate comments and documentation
- Ensure code is properly formatted

## 📄 License

This project is licensed under the **MIT License** - see the [LICENSE](LICENSE) file for details.

## 🙏 Acknowledgments

- **[Robert Nystrom](https://github.com/munificent)** for the exceptional book "[Crafting Interpreters](https://craftinginterpreters.com/)" that inspired this implementation
- **[Google Test](https://github.com/google/googletest)** for providing the testing framework
- The **open-source community** for continuous inspiration and support

---

**Made with ❤️ by [Islam-Imad](https://github.com/Islam-Imad)**

*Happy interpreting! 🎉*

