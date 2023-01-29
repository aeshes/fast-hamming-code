#include "hamming.h"

uint8_t xor_sum(uint8_t a)
{
	uint8_t sum = 0;
	while (a > 0)
	{
		if (a & 1)
			sum ^= 1;
		a >>= 1;
	}
	return sum;
}

uint8_t encode(uint8_t message)
{
	const size_t matrix_cols = 7;
	uint8_t result = 0;

	/* [1 0 0 0 1 1 1]
	*  [0 1 0 0 0 1 1]
	*  [0 0 1 0 1 0 1]
	*  [0 0 0 1 1 1 0]
	* 
	*   8 4 2 1 B D E
	*/
	uint8_t gen_matrix[matrix_cols] = { 0x08, 0x04, 0x02, 0x01, 0x0B, 0x0D, 0x0E };

	for (int col = 0; col < matrix_cols; col++)
	{
		result <<= 1;
		result |= xor_sum(message & gen_matrix[col]);
	}
	return result;
}

uint8_t syndrome(uint8_t message)
{
	const size_t matrix_rows = 3;
	uint8_t result = 0;

	/* [1 0 1 1 1 0 0] 0x5C
	*  [1 1 0 1 0 1 0] 0x6A
	*  [1 1 1 0 0 0 1] 0x71
	*/
	uint8_t parity_matrix[matrix_rows] = { 0x5C, 0x6A, 0x71 };

	for (int row = 0; row < matrix_rows; row++)
	{
		result <<= 1;
		result |= xor_sum(parity_matrix[row] & message);
	}
	return result;
}