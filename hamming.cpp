#include "hamming.h"

/*
	File:    hamming.cpp
	Purpose: implementation Hamming encode and decode routines.
	Author:  Aoizora
	Year:    2023
*/

/*
* Function: xor_sum
* Purpose:  performs modulo 2 sum of all bits in the word.
* Returns:  0 if even number of bits set to 1
*           1 if odd number of bits set to 1
*/
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

/*
* Function: encode
* Purpose:  Uses generator matrix of Hamming code to encode a DATA_BITS long value.
*           Notice that '&' is used for modulo 2 multiplication.
* Returns:  Hamming codeword for given data word
*/
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
		result |= xor_sum(message & gen_matrix[col]); /* mod 2 multiplication of vectors and summing bits of result modulo 2 */
	}
	return result;
}

/*
* Function: syndrome
* Purpose:  Uses parity check matrix to calculate a syndrome of a hamming codeword. Notice that '&' is used for modulo 2 multiplication.
* Returns:  Syndrome of given codeword.
*/
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
		result |= xor_sum(parity_matrix[row] & message); /* mod 2 multiplication of vectors and summing bits of result modulo 2 */
	}
	return result;
}

static uint8_t code[DATA_VALUES];

void fill_code_table()
{
	for (uint8_t message = 0; message <= 0x0F; message++)
	{
		code[message] = encode(message);
	}
}


uint8_t table_encode(uint8_t message)
{
	return code[message];
}