#include "hamming.h"

/*
	File:    hamming.cpp
	Purpose: implementation Hamming encode and decode routines.
	Author:  Aoizora
	Year:    2023
*/

/*
* Function: sum_bits
* Purpose:  performs modulo 2 sum of all bits in the word.
* Returns:  0 if even number of bits set to 1
*           1 if odd number of bits set to 1
*/
uint8_t sum_bits(uint8_t a)
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
		result |= sum_bits(message & gen_matrix[col]); /* mod 2 multiplication of vectors and summing bits of result modulo 2 */
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
		result |= sum_bits(parity_matrix[row] & message); /* mod 2 multiplication of vectors and summing bits of result modulo 2 */
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

const uint8_t syndrome_mask[PARITY_VALUES] =
{
	0x00,	/* syndrome = 0 0 0 */
	0x01,	/* syndrome = 0 0 1 */
	0x02,	/* syndrome = 0 1 0 */
	0x20,	/* syndrome = 0 1 1 */
	0x04,	/* syndrome = 1 0 0 */
	0x08,	/* syndrome = 1 0 1 */
	0x40,	/* syndrome = 1 1 0 */
	0x10	/* syndrome = 1 1 1 */
};

/*
* Function: decode
* Purpose:  This function uses syndrome decoding algorithm to determine value encoded by a CODE_BITS long code.
*           Syndrome is a result of multiplying of code by parity check matrix: s = HcT.
*           If there are no errors in the code, the syndrome will be a 0 vector.  If the syndrome is not 0, 
*           it will match a column in H.  The column it matches is likely the errored bit.
* Returns:  Nearest value to encoded data
*/
uint8_t decode(uint8_t code)
{
	uint8_t s = syndrome(code);

	return (code ^ syndrome_mask[s]) >> PARITY_BITS;
}