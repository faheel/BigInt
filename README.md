<p align="center">
  <img alt="BigInt" src="logo.png">
</p>
<h3 align="center">Arbitrary-sized integer class for C++</h3>

---

## Basic usage
1. Download the [single-include header file](../../releases) to a location under
    your include path. Then `#include` it in your code:
    ```C++
    #include "BigInt.hpp"   // the actual path may vary
    ```

1. Create objects of the `BigInt` class, and do what you got to do!
    ```C++
    BigInt num1 = 1234567890;
    BigInt num2 = "12345678901234567890123456789012345678901234567890";

    std::cout << num1 * num2 << "\n";
    // Output: 15241578751714678875171467887517146788751714678875019052100
    ```

## Features
### Operators
* #### Assignment
  * #### `=`
* #### Arithmetic
  * #### Unary
    * #### `+`
    * #### `-`
  * #### Binary
    * #### `+`
    * #### `-`
    * #### `*`
    * #### `/`
    * #### `%`
* #### Arithmetic-assignment
  * #### `+=`
  * #### `-=`
  * #### `*=`
  * #### `/=`
  * #### `%=`
* #### Increment and decrement (both pre- and post-)
  * #### `++`
  * #### `--`
* #### Relational
  * #### `<`
  * #### `>`
  * #### `<=`
  * #### `>=`
  * #### `==`
  * #### `!=`
* #### I/O stream
  * #### `>>`
  * #### `<<`

## License
This project is licensed under the terms of the [MIT license](LICENSE).
