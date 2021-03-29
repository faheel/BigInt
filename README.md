<p align="center">
  <img alt="BigInt" src="logo.png">
</p>
<h3 align="center">Arbitrary-sized integer class for C++</h3>

---

[![Release version][release-shield]][release-link]
[![GitHub CI][github-ci-shield]][github-ci-link]
[![Codecov][codecov-shield]][codecov-link]
[![Try it online][try-online-shield]][try-online-link]
[![License][license-shield]][license-link]

:construction: Work in progress :construction:

#### Contents

* [Highlights](#highlights)
* [Usage](#usage)
* [Features](#features)
* [Development](#development)
* [Contributing](#contributing)
* [License](#license)

## Highlights

* No additional dependencies apart from the standard library.
* Modern C++ (compiles with C++11 / C++14 / C++17).
* No special compiling or linking required. Simply download the
  [single header file][release-link], include it in your code, and compile
  however you would.

## Usage

1. Download the [single-include header file][header-link] to a location under
    your include path. Then `#include` it in your code:
    ```c++
    #include "BigInt.hpp"   // the actual path may vary
    ```

1. Create objects of the `BigInt` class, and do what you got to do!
    ```c++
    BigInt big1 = 1234567890, big2;
    big2 = "9876543210123456789098765432101234567890";

    std::cout << big1 * big2 * 123456 << "\n";
    // Output: 1505331490682966620443288524512589666204282352096057600
    ```

## Features

### Operators

* #### Assignment: `=`
  The second operand can either be a `BigInt`, an integer (up to `long long`)
  or a string (`std::string` or a string literal).
  ```c++
  big1 = 1234567890;
  big1 = "123456789012345678901234567890";
  big1 = big2;
  ```

* #### Unary arithmetic: `+`, `-`
  ```c++
  big1 = +big2;   // doesn't return the absolute value
  big1 = -big2;
  ```

* #### Binary arithmetic: `+`, `-`, `*`, `/`, `%`
  One of the operands has to be a `BigInt` and the other can be a `BigInt`, an
  integer (up to `long long`) or a string (`std::string` or a string literal).
  ```c++
  big1 = big2 + 1234567890;
  big1 = big2 - "123456789012345678901234567890";
  big1 = big2 * big3;
  big1 = 1234567890 / big2;
  big1 = "123456789012345678901234567890" % big2;
  ```

* #### Arithmetic-assignment: `+=`, `-=`, `*=`, `/=`, `%=`
  The second operand can either be a `BigInt`, an integer (up to `long long`)
  or a string (`std::string` or a string literal).
  ```c++
  big1 += big2;
  big1 -= 1234567890;
  big1 *= "123456789012345678901234567890";
  big1 /= big2;
  big1 %= 1234567890;
  ```

* #### Increment and decrement: `++`, `--`
  ```c++
  big1 = ++big2;   // pre-increment
  big1 = --big2;   // pre-decrement

  big1 = big2++;   // post-increment
  big1 = big2--;   // post-decrement
  ```

* #### Relational: `<`, `>`, `<=`, `>=`, `==`, `!=`
  One of the operands has to be a `BigInt` and the other can be a `BigInt`, an
  integer (up to `long long`) or a string (`std::string` or a string literal).
  ```c++
  if (big1 < 1234567890
      or big1 > "123456789012345678901234567890"
      or big1 <= big2
      or 1234567890 >= big1
      or "123456789012345678901234567890" == big1
      or big1 != big3) {
      ...
  }
  ```

* #### I/O stream: `<<`, `>>`
  ```c++
  std::cout << big1 << ", " << big2 << "\n";
  output_file << big1 << ", " << big2 << "\n";

  std::cin >> big1 >> big2;
  input_file >> big1 >> big2;
  ```

### Functions

* #### Conversion: `to_string`, `to_int`, `to_long`, `to_long_long`
  Convert a `BigInt` to either a `string`, `int`, `long`, or `long long`.

  **Note**: If the `BigInt` is beyond the range of the target type, an
  [out_of_range exception][out_of_range-exception] is thrown.

  ```c++
  some_str = big1.to_string();

  some_int = big1.to_int();

  some_long = big1.to_long();

  some_long_long = big1.to_long_long();
  ```

* #### Math

  * #### `abs`
    Get the absolute value of a `BigInt`.

    ```c++
    big1 = abs(big2);
    ```

  * #### `big_pow10`
    Get a `BigInt` equal to _10<sup>exp</sup>_.

    ```c++
    big1 = big_pow10(5000);   // big1 = 10^5000
    ```

  * #### `gcd`
    Get the greatest common divisor (GCD aka. HCF) of two `BigInt`s. One of the
    arguments can be an integer (up to `long long`) or a string (`std::string`
    or a string literal).

    ```c++
    big1 = gcd(big2, big3);
    big1 = gcd(big2, 1234567890);
    big1 = gcd(big2, "123456789012345678901234567890");
    big1 = gcd(1234567890, big2);
    big1 = gcd("123456789012345678901234567890", big2);
    ```

  * #### `lcm`
    Get the least common multiple (LCM) of two `BigInt`s. One of the arguments
    can be an integer (up to `long long`) or a string (`std::string` or a
    string literal).

    ```c++
    big1 = lcm(big2, big3);
    big1 = lcm(big2, 1234567890);
    big1 = lcm(big2, "123456789012345678901234567890");
    big1 = lcm(1234567890, big2);
    big1 = lcm("123456789012345678901234567890", big2);
    ```

  * #### `pow`
    Get the value of _base<sup>exp</sup>_ as a `BigInt`. The base can either be
    a `BigInt`, an integer (up to `long long`) or a string (`std::string` or a
    string literal).

    ```c++
    big1 = pow(big2, 789);
    big1 = pow(987654321LL, 456);   // suffix literal with LL to prevent conflicts
    big1 = pow("1234567890", 123);
    ```

  * #### `sqrt`
    Get the integer square root of a `BigInt`.

    ```c++
    big1 = sqrt(big2);
    ```

* #### Random
  * #### `big_random`
    Get a random `BigInt`, that either has a random number of digits (up to
    1000), or a specific number of digits.

    ```c++
    // get a random BigInt that has a random number of digits (up to 1000):
    big1 = big_random();

    // get a random BigInt that has 12345 digits:
    big1 = big_random(12345);
    ```

## Development

Since this project is built as a header-only library, there are no source files.
However, there are unit tests for each header file that the project is split
into. These can be compiled and built either through the command line, or using
an IDE that has direct support for CMake (such as CLion, Qt Creator) or for
which CMake can generate project files (Visual Studio, Eclipse CDT, Code::Blocks
and more).

### Using the command line

On Linux and macOS, you can compile and run the tests using the command line from the project's root directory.
* To compile the tests, run **`make`**.
* To build and run the tests, run **`make test`**.
* To generate the single-include header file, run **`make release`**. The generated file will appear in the `release` folder.

### Using an IDE that supports CMake

1. Load the project directory in your IDE.
1. In the build settings for CMake, which can usually be found at
   `Settings > Build > CMake`, set the `Generation path` to `build`.

Then you can simply select which target (unit test) you want to build/run, and
your IDE will do the rest.

In case your IDE does not support CMake directly, you will need to run `cmake`
via the command line with the appropriate flags to generate the project files
for your IDE. Give it a try, it's not supposed to be hard!

## Contributing

Please read the [contributing guidelines][contributing-link] for details on
how to contribute to the project.

## License

This project is licensed under the terms of the [MIT license][license-link].


[release-shield]: https://img.shields.io/github/release/faheel/BigInt/all.svg?style=for-the-badge
[release-link]: https://github.com/faheel/BigInt/releases
[github-ci-shield]: https://img.shields.io/github/workflow/status/faheel/BigInt/CI?style=for-the-badge
[github-ci-link]: https://github.com/faheel/BigInt/actions/workflows/ci.yml
[codecov-shield]: https://img.shields.io/codecov/c/github/faheel/BigInt.svg?style=for-the-badge
[codecov-link]: https://codecov.io/gh/faheel/BigInt
[try-online-shield]: https://img.shields.io/badge/Try_it-Online-E91E63.svg?style=for-the-badge
[try-online-link]: https://wandbox.org/permlink/3Zlo2EDmgilQPTKc
[license-shield]: https://img.shields.io/github/license/faheel/BigInt.svg?style=for-the-badge
[license-link]: https://github.com/faheel/BigInt/blob/master/LICENSE
[out_of_range-exception]: http://en.cppreference.com/w/cpp/error/out_of_range
[contributing-link]: https://github.com/faheel/BigInt/blob/master/.github/CONTRIBUTING.md
[header-link]: https://github.com/faheel/BigInt/releases/download/v0.4.0-dev/BigInt.hpp
