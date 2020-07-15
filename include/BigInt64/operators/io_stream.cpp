#pragma once

#include "../BigInt64.hpp"

std::ostream& operator<<(std::ostream& out, const BigInt64& num) {
	out << num.numArr;
	return out;
}