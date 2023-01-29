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
}