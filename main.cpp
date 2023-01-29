#include <iostream>
#include <bitset>
#include "hamming.h"

using namespace std;

int main()
{
	uint8_t message = 0x0A;
	uint8_t encoded = encode(message);
	uint8_t s = syndrome(encoded);
	uint8_t decoded = decode(encoded);

	cout << "encoded: " << bitset<7>(encoded) << endl;
	cout << "decoded: " << bitset<4>(decoded) << endl;
	cout << "syndrome: " << bitset<3>(s) << endl;

	cout << "error 0 bit" << endl;
	encoded |= 1 << 5;
	cout << "errored: " << bitset<7>(encoded) << endl;
	s = syndrome(encoded);
	cout << "syndrome: " << bitset<3>(s) << endl;
	decoded = decode(encoded);
	cout << "decoded: " << bitset<4>(decoded) << endl;
}