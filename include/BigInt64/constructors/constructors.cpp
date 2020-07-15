#pragma once

#include "../BigInt64.hpp"

BigInt64::BigInt64(){
	this->numArr = new std::vector<uint64_t>();
	this->numArr->push_back(0);
	this->positive = true;
	this->negative = false; //in the 2s complement system zero is repersented as 0x0 with the sign bit being zero
}

BigInt64::BigInt64(const std::string& s){
	this->numArr = new std::vector<uint64_t>();
	std::string newS;
	if(s[0] == '-'){
		this->negative = true;
		this->positive = false;
		newS = s.substr(1,s.length()-1);
	}else if ( s[0] == '+'){
		this->negative = false;
		this->positive = true;
		newS = s.substr(1,s.length()-1);
	}else{
		this->negative = false;
		this->positive = true;
		newS = s;
	}

	BigInt num = BigInt(newS);
	BigInt base = BigInt("18446744073709551616"); // 2**64

	while(num > 0){
		uint64_t remainder = (uint64_t)(num%base).to_long_long();
		this->numArr->push_back(remainder);
		num /= base;
	}
}

BigInt64::~BigInt64(){
	delete numArr;
}