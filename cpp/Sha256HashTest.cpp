/* 
 * A runnable main program that tests the functionality of class Sha256Hash.
 * 
 * Copyright (c) Project Nayuki
 * http://www.nayuki.io/
 */

#include <cstdio>
#include <cstdint>
#include <cstring>
#include "Sha256Hash.h"


struct TestCase {
	const bool matches;
	const char *hexHash;
	const uint8_t byteHash[32];
};


int main(int argc, char **argv) {
	// Test equality
	TestCase cases[] = {
		{true , "0000000000000000000000000000000000000000000000000000000000000000", {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}},
		{true , "ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff", {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF}},
		{true , "00112233445566778899aabbccddeeff0112233445566778899aabbccddeeff0", {0xF0,0xEF,0xDE,0xCD,0xBC,0xAB,0x9A,0x89,0x78,0x67,0x56,0x45,0x34,0x23,0x12,0x01,0xFF,0xEE,0xDD,0xCC,0xBB,0xAA,0x99,0x88,0x77,0x66,0x55,0x44,0x33,0x22,0x11,0x00}},
		{true , "fd1a91ca0b85a52ece4f73eb7c55a5021fa852f78d0390236219ea458c2ce991", {0x91,0xE9,0x2C,0x8C,0x45,0xEA,0x19,0x62,0x23,0x90,0x03,0x8D,0xF7,0x52,0xA8,0x1F,0x02,0xA5,0x55,0x7C,0xEB,0x73,0x4F,0xCE,0x2E,0xA5,0x85,0x0B,0xCA,0x91,0x1A,0xFD}},
		{false, "0000000000000000000000000000000000000000000000000000000000000001", {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}},
		{false, "8000000000000000000000000000000000000000000000000000000000000000", {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}},
		{false, "ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffefffff", {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF}},
	};
	for (unsigned int i = 0; i < sizeof(cases) / sizeof(cases[0]); i++) {
		bool actual = Sha256Hash(cases[i].byteHash, 32) == Sha256Hash(cases[i].hexHash);
		if (actual != cases[i].matches)
			goto fail;
	}
	
	// Test get byte
	{
		Sha256Hash hash("fd1a91ca0b85a52ece4f73eb7c55a5021fa852f78d0390236219ea458c2ce991");
		if (hash.getByte(0) != 0x91 || hash.getByte(1) != 0xE9 || hash.getByte(2) != 0x2C || hash.getByte(30) != 0x1A || hash.getByte(31) != 0xFD)
			goto fail;
	}
	
	// Epilog
	printf("Test passed\n");
	return 0;
fail:
	printf("Test failed\n");
	return 1;
}
