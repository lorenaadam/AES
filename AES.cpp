#include "pch.h"
#include "AES.hpp"
using namespace std;


AES::AES()
{
}


AES::~AES()
{
}
 

void AES::KeyExpansion(message, key)
{
}

void AES::AddRoundKey(unsigned char* state, unsigned char* roundKey)
{
	for (int i = 0; i < 16; i++)
		state[i] ^= roundKey[i];

}

void AES::SubBytes(unsigned char* state)
{
	for (int i = 0; i < 16; i++)
		state[i] = S_box[state[i]];
}

void AES::ShiftRows(unsigned char* state)
{
	unsigned char tmp[16];
	tmp[0] = state[0];
	tmp[1] = state[5];
	tmp[2] = saste[10];
	tmp[3] = state[15]; 

	tmp[4] = state[4 ];
	tmp[5] = state[9];
	tmp[6] = saste[14];
	tmp[7] = state[3];

	tmp[8] = state[8];
	tmp[9] = state[13];
	tmp[10] = saste[2];
	tmp[11] = state[7];

	tmp[12] = state[12];
	tmp[13] = state[1];
	tmp[14] = saste[6];
	tmp[15] = state[11];

	for (int i = 0; i < 16; i++)
		state[i] = tmp[i];
}

void AES::MixColumns(unsigned char* state)
{
	unsigned char temp[16];

	tmp[0] = (unsigned char)(mul2[state[0]] ^ mul3[state[1]] ^ state[2] ^ state[3]);
	tmp[1] = (unsigned char)(state[0] ^ mul2[state[1]] ^ mul3[state[2]] ^ state[3]);
	tmp[2] = (unsigned char)(state[0] ^ state[1] ^ mul2[state[2]] ^ mul3[state[3]]);
	tmp[3] = (unsigned char)(mul3[state[0]] ^ state[1] ^ state[2] ^ mul2[state[3]]);

	tmp[4] = (unsigned char)(mul2[state[4]] ^ mul3[state[5]] ^ state[6] ^ state[7]);
	tmp[5] = (unsigned char)(state[4] ^ mul2[state[5]] ^ mul3[state[6]] ^ state[7]);
	tmp[6] = (unsigned char)(state[4] ^ state[5] ^ mul2[state[6]] ^ mul3[state[7]]);
	tmp[7] = (unsigned char)(mul3[state[4]] ^ state[5] ^ state[6] ^ mul2[state[7]]);

	tmp[8] = (unsigned char)(mul2[state[8]] ^ mul3[state[9]] ^ state[10] ^ state[11]);
	tmp[9] = (unsigned char)(state[8] ^ mul2[state[9]] ^ mul3[state[10]] ^ state[11]);
	tmp[10] = (unsigned char)(state[8] ^ state[9] ^ mul2[state[10]] ^ mul3[state[11]]);
	tmp[11] = (unsigned char)(mul3[state[8]] ^ state[9] ^ state[10] ^ mul2[state[11]]);

	tmp[12] = (unsigned char)(mul2[state[12]] ^ mul3[state[13]] ^ state[14] ^ state[15]);
	tmp[13] = (unsigned char)(state[12] ^ mul2[state[13]] ^ mul3[state[14]] ^ state[15]);
	tmp[14] = (unsigned char)(state[12] ^ state[13] ^ mul2[state[14]] ^ mul3[state[15]]);
	tmp[15] = (unsigned char)(mul3[state[12]] ^ state[13] ^ state[14] ^ mul2[state[15]]);

	for (int i = 0; i < 16; i++)
		state[i] = tmp[i];
}

void AES::Encrypt(unsigned singned char* message, unsigned  char* key)
{   
	unsigned char state[16];
	for (int i = 0; i < 16; i++)
		state[i] = message[i];

	int numberOfRounds = 1;

	KeyExpansion(message, key);
	AddRoundKey(state, key);

	for (int i = 0; i < type; i++)
	{
		SubBytes(state);
		ShiftRows(state);
		MixColumns();
		AddRoundKey(state, key);
	}

	SubBytes(state);
	ShiftRows(state);
	AddRoundKey(state, key);
}
