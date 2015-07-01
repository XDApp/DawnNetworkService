#include "stdafx.h"
#include "DRSAKey.h"
#include "DException.h"

DRSAKey::DRSAKey(const std::string &Rand_Str, unsigned long Key_Length)
	: rsa(nullptr)
{
	RAND_seed(Rand_Str.c_str(), sizeof(Rand_Str.c_str()));
	rsa = RSA_generate_key(Key_Length, RSA_F4, NULL, NULL);
	if (rsa == NULL)
	{
		throw new DException("RSA Generate Error");
	}
}

DRSAKey::DRSAKey(RSA *Rsa)
	:rsa(Rsa)
{

}


DRSAKey::~DRSAKey()
{
	RSA_free(rsa);
}

RSA* DRSAKey::GetKey()
{
	return rsa;
}