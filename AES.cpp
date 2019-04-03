#include "pch.h"
#include "AES.hpp"


AES::AES()
{
}


AES::~AES()
{
}

void AES::KeyExpansion()
{
}

void AES::AddRoundKey()
{
}

void AES::ByteSub()
{
}

void AES::ShiftRows()
{
}

void AES::MixColumns()
{
}

void AES::Encrypt(int type)
{
	KeyExpansion();
	AddRoundKey();

	for (int i = 0; i < type; i++)
	{
		ByteSub();
		ShiftRows();
		MixColumns();
		AddRoundKey();
	}

	ByteSub();
	ShiftRows();
	AddRoundKey();
}
