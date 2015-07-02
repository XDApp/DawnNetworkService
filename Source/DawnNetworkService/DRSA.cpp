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
		throw new DException("open_public_key EVP_PKEY_new failed");
		return nullptr;
	}
	EVP_PKEY_assign_RSA(evp_key, Key->GetKey());
	return evp_key;
}


int DRSA::RSAEncrypt(EVP_PKEY *key, const unsigned char *orig_data, size_t orig_data_len,
	unsigned char *enc_data, size_t &enc_data_len)
{
	EVP_PKEY_CTX *ctx = nullptr;
	OpenSSL_add_all_ciphers();

	ctx = EVP_PKEY_CTX_new(key, nullptr);
	if (ctx == nullptr)
	{
		throw new DException("ras_pubkey_encryptfailed to open ctx.");
		return -1;
	}

	if (EVP_PKEY_encrypt_init(ctx) <= 0)
	{
		throw new DException("ras_pubkey_encryptfailed to EVP_PKEY_encrypt_init.");
		return -1;
	}

	if (EVP_PKEY_encrypt(ctx,
		enc_data,
		&enc_data_len,
		orig_data,
		orig_data_len) < 0)
	{
		throw new DException("ras_pubkey_encryptfailed to EVP_PKEY_encrypt.");
		EVP_PKEY_CTX_free(ctx);
		return -1;
	}

	EVP_PKEY_CTX_free(ctx);
	return 0;
}

int DRSA::RSADecrypt(EVP_PKEY *key, const unsigned char *enc_data, size_t enc_data_len,
	unsigned char *orig_data, size_t &orig_data_len)
{
	EVP_PKEY_CTX *ctx = nullptr;
	OpenSSL_add_all_ciphers();

	ctx = EVP_PKEY_CTX_new(key, nullptr);
	if (ctx == nullptr)
	{
		throw new DException("ras_prikey_decryptfailed to open ctx.");
		return -1;
	}

	if (EVP_PKEY_decrypt_init(ctx) <= 0)
	{
		throw new DException("ras_prikey_decryptfailed to EVP_PKEY_decrypt_init.");
		return -1;
	}

	if (EVP_PKEY_decrypt(ctx,
		orig_data,
		&orig_data_len,
		enc_data,
		enc_data_len) < 0)
	{
		throw new DException("ras_prikey_decryptfailed to EVP_PKEY_decrypt.");
		EVP_PKEY_CTX_free(ctx);
		return -1;
	}

	EVP_PKEY_CTX_free(ctx);
	return 0;
}
