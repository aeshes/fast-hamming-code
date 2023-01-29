#include <iostream>
#include <bitset>
#include "hamming.h"

using namespace std;

int main()
{
	uint8_t message = 0x0A;
	uint8_t encoded = encode(message);
	uint8_t s = syndrome(encoded);

	cout << "encoded: "  << bitset<7>(encoded) << endl;
	cout << "syndrome: " << bitset<7>(s) << endl;
}