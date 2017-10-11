<p align="center">
  <img alt="BigInt" src="logo.png">
</p>
<h3 align="center">Arbitrary-sized integer class for C++</h3>

---

## Usage
1. Download the [single-include header file](../../releases) to a location under
    your include path. Then `#include` it in your code:
    ```C++
    #include "BigInt.hpp"   // the actual path may vary
    ```

1. Create objects of the `BigInt` class, and do what you got to do!
    ```C++
    BigInt num1 = 1234567890;
    BigInt num2;
    num2 = "9876543210123456789098765432101234567890";
    BigInt num3 = num2 - num1;

    std::cout << num2 + num3 << "\n";
    // Output: 19753086420246913578197530864201234567890
    ```

## Features
### Operators
* #### Assignment
  * #### `=`
    ```C++
    my_big_int = 1234567890;
    my_big_int = "123456789012345678901234567890";
    my_big_int = my_other_big_int;
    ```
* #### Arithmetic
  * #### Unary
    * #### `+`
      ```C++
      my_big_int = +my_other_big_int;
      ```
    * #### `-`
      ```C++
      my_big_int = -my_other_big_int;
      ```
  * #### Binary
    * #### `+`
      ```C++
      big_int_1 = big_int_2 + 1234567890;
      big_int_1 = big_int_2 + "123456789012345678901234567890";
      big_int_1 = big_int_2 + big_int_3;
      ```
    * #### `-`
      ```C++
      big_int_1 = big_int_2 - 1234567890;
      big_int_1 = big_int_2 - "123456789012345678901234567890";
      big_int_1 = big_int_2 - big_int_3;
      ```
* #### Arithmetic-assignment
  * #### `+=`
    ```C++
    my_big_int += 1234567890;
    my_big_int += "123456789012345678901234567890";
    my_big_int += my_other_big_int;
    ```
  * #### `-=`
    ```C++
    my_big_int -= 1234567890;
    my_big_int -= "123456789012345678901234567890";
    my_big_int -= my_other_big_int;
    ```
* #### Increment and decrement
  * #### `++`
    ```C++
    some_big_int = ++my_big_int;   // pre-increment
    some_big_int = my_big_int++;   // post-increment
    ```
  * #### `--`
    ```C++
    some_big_int = --my_big_int;   // pre-decrement
    some_big_int = my_big_int--;   // post-decrement
    ```
* #### Relational
  * #### `<`
    ```C++
    if (big_int_1 < 1234567890 or
        big_int_1 < "123456789012345678901234567890" or
        big_int_1 < big_int_2) {
        ...
    }
    ```
  * #### `>`
    ```C++
    if (big_int_1 > 1234567890 or
        big_int_1 > "123456789012345678901234567890" or
        big_int_1 > big_int_2) {
        ...
    }
    ```
  * #### `<=`
    ```C++
    if (big_int_1 <= 1234567890 or
        big_int_1 <= "123456789012345678901234567890" or
        big_int_1 <= big_int_2) {
        ...
    }
    ```
  * #### `>=`
    ```C++
    if (big_int_1 >= 1234567890 or
        big_int_1 >= "123456789012345678901234567890" or
        big_int_1 >= big_int_2) {
        ...
    }
    ```
  * #### `==`
    ```C++
    if (big_int_1 == 1234567890 or
        big_int_1 == "123456789012345678901234567890" or
        big_int_1 == big_int_2) {
        ...
    }
    ```
  * #### `!=`
    ```C++
    if (big_int_1 != 1234567890 or
        big_int_1 != "123456789012345678901234567890" or
        big_int_1 != big_int_2) {
        ...
    }
    ```
* #### I/O stream
  * #### `>>`
    ```C++
    std::cin >> big_int_1 >> big_int_2;
    input_file >> my_big_int >> big_int_2;
    ```
  * #### `<<`
    ```C++
    std::cout << big_int_1 << ", " << big_int_2 << "\n";
    output_file << big_int_1 << ", " << big_int_2 << "\n";
    ```

### Functions
* #### Math
  * #### `abs`
    ```C++
    my_big_int = abs(my_other_big_int);
    ```

## License
This project is licensed under the terms of the [MIT license](LICENSE).
