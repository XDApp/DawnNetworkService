#include "stdafx.h"
#include "DRSA.h"
#include "DException.h"
#include "DRSAKey.h"

DRSA::DRSA()
{
}


DRSA::~DRSA()
{
}
//	int generate_key_files(const char *pub_keyfile, const char *pri_keyfile,
// const unsigned char *passwd, int passwd_len)

void DRSA::Randomize()
{
	srand(time(NULL));
}

std::string DRSA::GenerateRandString()
{
	std::string rand_str = "";
	for (int i = 0; i < rand() % 20 + 20; i++)
	{
		rand_str.push_back(rand() % 255 + 1);
	}
	return rand_str;
}

void DRSA::SavePriKey(DRSAKey* Key, const std::string &filename, std::string Password)
{	
	BIO *bp = BIO_new_file(filename.c_str(), "w+");
	if (NULL == bp)
	{
		throw new DException("BIO File Generate Error");
	}

	if (PEM_write_bio_RSAPrivateKey(bp, Key->GetKey(),
		EVP_des_ede3_ofb(), (unsigned char *)Password.c_str(),
		Password.length(), NULL, NULL) != 1)
	{
		throw new DException("PEM_write_bio_RSAPublicKey error!");
	}
	BIO_free_all(bp);
}

void DRSA::SavePubKey(DRSAKey* Key, const std::string &filename)
{
	BIO *bp = BIO_new(BIO_s_file());
	if (NULL == bp)
	{
		throw new DException("BIO File Generate Error");
	}

	if (BIO_write_filename(bp, (void *)filename.c_str()) <= 0)
	{
		throw new DException("BIO_write_filename error!");
	}

	if (PEM_write_bio_RSAPublicKey(bp, Key->GetKey()) != 1)
	{
		throw new DException("PEM_write_bio_RSAPublicKey error!");
	}
	BIO_free_all(bp);
}