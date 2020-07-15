#include "BigInt64.hpp"

#include <iostream>

int main(){

	BigInt64 t = BigInt64("1");
	std::cout<< t << std::endl;

	t = BigInt64("18446744073709551616");
	std::cout<< t << std::endl;

	return 0;


}