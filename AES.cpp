#include "pch.h"
#include "AES.hpp"
using namespace std;


AES::AES()
{
}


AES::~AES()
{
}
 

void AES::KeyExpansion(unsigned char inputKey[16], unsigned char expandedKeys[176]) {
	// The first 128 bits are the original key
	for (int i = 0; i < 16; i++) {
		expandedKeys[i] = inputKey[i];
	}

}

void AES::AddRoundKey(unsigned char* state, unsigned char* roundKey)
{
	for (int i = 0; i < 16; i++)
		state[i] ^= roundKey[i];

}

void AES::SubBytes(unsigned char* state)
{
	for (int i = 0; i < 16; i++)
		state[i] = s_box[state[i]];
}

void AES::ShiftRows(unsigned char* state)
{
	unsigned char tmp[16];
	tmp[0] = state[0];
	tmp[1] = state[5];
	tmp[2] = state[10];
	tmp[3] = state[15]; 

	tmp[4] = state[4 ];
	tmp[5] = state[9];
	tmp[6] = state[14];
	tmp[7] = state[3];

	tmp[8] = state[8];
	tmp[9] = state[13];
	tmp[10] = state[2];
	tmp[11] = state[7];

	tmp[12] = state[12];
	tmp[13] = state[1];
	tmp[14] = state[6];
	tmp[15] = state[11];

	for (int i = 0; i < 16; i++)
		state[i] = tmp[i];
}

void AES::MixColumns(unsigned char* state)
{
	unsigned char tmp[16];

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

//type --> AES -128, 192, 256
void AES::Encrypt(unsigned char * message, unsigned char * expandedKey, unsigned char * encryptedMessagey, int type)
{   
	unsigned char state[16];
	for (int i = 0; i < 16; i++)
		state[i] = message[i];

	int numberOfRounds = 1;

	KeyExpansion(message, expandedKey);
	AddRoundKey(state, expandedKey);

	for (int i = 0; i < type; i++)
	{
		SubBytes(state);
		ShiftRows(state);
		MixColumns(state);
		AddRoundKey(state, expandedKey);
	}

	SubBytes(state);
	ShiftRows(state);
	AddRoundKey(state, expandedKey);
}

void AES::Decrypt(unsigned char * encryptedMessage, unsigned char * expandedKey, unsigned char * decryptedMessage)
{
	unsigned char state[16]; // Stores the first 16 bytes of encrypted message

	for (int i = 0; i < 16; i++) {
		state[i] = encryptedMessage[i];
	}

	InitialRound(state, expandedKey + 160);

	int numberOfRounds = 9;

	for (int i = 8; i >= 0; i--) {
		Round(state, expandedKey + (16 * (i + 1)));
	}

	SubRoundKey(state, expandedKey); // Final round

	// Copy decrypted state to buffer
	for (int i = 0; i < 16; i++) {
		decryptedMessage[i] = state[i];
	}
}

void AES::InitialRound(unsigned char * state, unsigned char * key) {
	SubRoundKey(state, key);
	ShiftRows(state);
	SubBytes(state);
}

void AES::SubRoundKey(unsigned char * state, unsigned char * roundKey) {
	for (int i = 0; i < 16; i++) {
		state[i] ^= roundKey[i];
	}
}

void AES::Round(unsigned char * state, unsigned char * key) {
	SubRoundKey(state, key);
	InverseMixColumns(state);
	ShiftRows(state);
	SubBytes(state);
}

void AES::InverseMixColumns(unsigned char * state) {
	unsigned char tmp[16];

	tmp[0] = (unsigned char)mul14[state[0]] ^ mul11[state[1]] ^ mul13[state[2]] ^ mul9[state[3]];
	tmp[1] = (unsigned char)mul9[state[0]] ^ mul14[state[1]] ^ mul11[state[2]] ^ mul13[state[3]];
	tmp[2] = (unsigned char)mul13[state[0]] ^ mul9[state[1]] ^ mul14[state[2]] ^ mul11[state[3]];
	tmp[3] = (unsigned char)mul11[state[0]] ^ mul13[state[1]] ^ mul9[state[2]] ^ mul14[state[3]];

	tmp[4] = (unsigned char)mul14[state[4]] ^ mul11[state[5]] ^ mul13[state[6]] ^ mul9[state[7]];
	tmp[5] = (unsigned char)mul9[state[4]] ^ mul14[state[5]] ^ mul11[state[6]] ^ mul13[state[7]];
	tmp[6] = (unsigned char)mul13[state[4]] ^ mul9[state[5]] ^ mul14[state[6]] ^ mul11[state[7]];
	tmp[7] = (unsigned char)mul11[state[4]] ^ mul13[state[5]] ^ mul9[state[6]] ^ mul14[state[7]];

	tmp[8] = (unsigned char)mul14[state[8]] ^ mul11[state[9]] ^ mul13[state[10]] ^ mul9[state[11]];
	tmp[9] = (unsigned char)mul9[state[8]] ^ mul14[state[9]] ^ mul11[state[10]] ^ mul13[state[11]];
	tmp[10] = (unsigned char)mul13[state[8]] ^ mul9[state[9]] ^ mul14[state[10]] ^ mul11[state[11]];
	tmp[11] = (unsigned char)mul11[state[8]] ^ mul13[state[9]] ^ mul9[state[10]] ^ mul14[state[11]];

	tmp[12] = (unsigned char)mul14[state[12]] ^ mul11[state[13]] ^ mul13[state[14]] ^ mul9[state[15]];
	tmp[13] = (unsigned char)mul9[state[12]] ^ mul14[state[13]] ^ mul11[state[14]] ^ mul13[state[15]];
	tmp[14] = (unsigned char)mul13[state[12]] ^ mul9[state[13]] ^ mul14[state[14]] ^ mul11[state[15]];
	tmp[15] = (unsigned char)mul11[state[12]] ^ mul13[state[13]] ^ mul9[state[14]] ^ mul14[state[15]];

	for (int i = 0; i < 16; i++) {
		state[i] = tmp[i];
	}
}