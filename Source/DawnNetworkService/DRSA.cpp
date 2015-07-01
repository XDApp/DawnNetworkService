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
	srand(time(nullptr));
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

void DRSA::SavePriKey(DRSAKey* Key, const std::string &filename, const std::string &Password)
{	
	BIO *bp = BIO_new_file(filename.c_str(), "w+");
	if (bp == nullptr)
	{
		throw new DException("BIO File Generate Error");
		return;
	}

	if (PEM_write_bio_RSAPrivateKey(bp, Key->GetKey(),
		EVP_des_ede3_ofb(), (unsigned char *)Password.c_str(),
		Password.length(), nullptr, nullptr) != 1)
	{
		throw new DException("PEM_write_bio_RSAPublicKey error!");
		return;
	}
	BIO_free_all(bp);
}

void DRSA::SavePubKey(DRSAKey* Key, const std::string &filename)
{
	BIO *bp = BIO_new(BIO_s_file());
	if (bp == nullptr)
	{
		throw new DException("BIO File Generate Error");
		return;
	}

	if (BIO_write_filename(bp, (void *)filename.c_str()) <= 0)
	{
		throw new DException("BIO_write_filename error!");
		return;
	}

	if (PEM_write_bio_RSAPublicKey(bp, Key->GetKey()) != 1)
	{
		throw new DException("PEM_write_bio_RSAPublicKey error!");
		return;
	}
	BIO_free_all(bp);
}

DRSAKey* DRSA::CreateKey(const std::string &Rand_Str, unsigned long Key_Length)
{
	return new DRSAKey(Rand_Str, Key_Length);
}

void DRSA::DestroyKey(DRSAKey *Key)
{
	delete Key;
}

DRSAKey* DRSA::LoadPubKey(const std::string &filename)
{
	RSA *rsa = nullptr;

	OpenSSL_add_all_algorithms();
	BIO *bp = BIO_new(BIO_s_file());;
	BIO_read_filename(bp, filename.c_str());
	if (bp == nullptr)
	{
		throw new DException("open_public_key bio file new error!");
		return nullptr;
	}

	rsa = PEM_read_bio_RSAPublicKey(bp, nullptr, nullptr, nullptr);

	if (rsa == nullptr)
	{
		throw new DException("open_public_key failed to PEM_read_bio_RSAPublicKey!");
		BIO_free(bp);
		RSA_free(rsa);

		return nullptr;
	}

	return new DRSAKey(rsa);
}

DRSAKey* DRSA::LoadPriKey(const std::string &filename, const std::string &Password)
{
	RSA *rsa = RSA_new();
	OpenSSL_add_all_algorithms();
	BIO *bp = BIO_new_file(filename.c_str(), "rb");
	if (bp == nullptr)
	{
		throw new DException("open_private_key bio file new error!");
		return nullptr;
	}

	rsa = PEM_read_bio_RSAPrivateKey(bp, &rsa, nullptr, (void *)Password.c_str());
	if (rsa == nullptr)
	{
		throw new DException("open_private_key failed to PEM_read_bio_RSAPrivateKey!");
		BIO_free(bp);
		RSA_free(rsa);
		return nullptr;
	}
	return new DRSAKey(rsa);
}

EVP_PKEY* DRSA::ToEVP(DRSAKey *Key)
{
	EVP_PKEY *evp_key = EVP_PKEY_new();
	if (evp_key == nullptr)
	{
		throw new DException("open_public_key EVP_PKEY_new failed\n");
		return nullptr;
	}
	EVP_PKEY_assign_RSA(evp_key, Key->GetKey());
	return evp_key;
}
