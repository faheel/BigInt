#pragma once

#include <iostream>
#include <cstdint>
#include <vector>

#include "../../release/BigInt.hpp"

/*

Some notes about big int 64:
sign cannot be stored conventionally so all intergers
will be stored with their positive values.
sign wil be dictated by using the positive and negative boolean values.
I have used 2 values here for user comfort but these can be easily changed to a 
single sign boolean.

*/
class BigInt64 {
private:
    std::vector<uint64_t>* numArr;
public:
    bool positive;
    bool negative;
    //bool zero;
	BigInt64();
	BigInt64(const std::string&);
	~BigInt64();
	//ops
	std::string toString() const;
	friend std::ostream& operator<<(std::ostream&, const BigInt64&);
};