#pragma once
class AES
{
public:
	AES();
	~AES();

	void KeyExpansion(); 
	void AddRoundKey();
	void SubBytes();
	void ShiftRows();
	void MixColumns();

	void Encrypt(int type);

};

