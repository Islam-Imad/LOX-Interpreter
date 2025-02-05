# Loxie Interpreter  
A Tree-Walk Interpreter for the Lox Programming Language.

## Overview  
Loxie is a dynamically-typed, interpreted programming language designed for simplicity and flexibility. Its syntax is concise and easy to understand, making it an excellent choice for learning programming concepts and building interpreters.

The language supports a variety of features such as:

- **<code>Arithmetic Operations</code>**: Supports standard operators like `+`,`-`,`*`,`/`, and exponentiation `**`.
- **<code>Variables</code>**: Allowing you to store and manipulate data with simple variable assignments.
- **<code>Functions</code>**: Define reusable code blocks with support for recursion and higher-order functions.
- **<code>Conditionals</code>**: Using `if`, `else if`, and `else` statements for conditional execution.
- **<code>Loops</code>**: Both `while` and `for` loops for iterating over code.
- **<code>Closures</code>**: Functions that capture and remember the environment where they were created, enabling powerful functional programming patterns.
- **<code>Printing</code>**: Output to the console using the `print` keyword.

## Example Usage

Here’s a quick example showcasing key features of Lox:

```js
var a = 3 ** 3 * 2 + 1 - 10 / 2;
print a;

fun fib(n) {
    if (n <= 1) { return n; }
    return fib(n - 1) + fib(n - 2);
}

var x = fib(10);
print x;

fun closure() {
    var a = 1;
    fun inner() {
        a = a + 1;
        print a;
    }
    return inner;
}

var c = closure();
c();
c();
c();

c = 10;
while (c > 0) {
    print c;
    c = c - 1;
}

for (var i = 0; i < 10; i = i + 1) {
    print i;
}

c = 3;

if (c == 1) {
    print "c is 1";
} else if (c == 2) {
    print "c is 2";
} else if (c == 3) {
    print "c is 3";
} else {
    print "c is not 1, 2, or 3";
}

c = 4;

if (c == 1) {
    print "c is 1";
} else if (c == 2) {
    print "c is 2";
} else if (c == 3) {
    print "c is 3";
} else {
    print "c is not 1, 2, or 3";
}
```

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

## Testing
You can run the test suite to ensure the interpreter is working correctly. The test suite is written using the `GTest` framework.
```bash
ctest
```
## Contributing

Feel free to open issues or pull requests. Contributions are welcome!

## License

This project is licensed under the MIT License.

## Acknowledgment  
This project was heavily inspired by concepts and techniques from the book [Crafting Interpreters](https://craftinginterpreters.com) by Robert Nystrom.

