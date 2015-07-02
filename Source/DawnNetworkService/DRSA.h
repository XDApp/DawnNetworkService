#pragma once

class DRSAKey;

class DRSA
{
public:
	DRSA();
	virtual ~DRSA();

	//RSA Load Save Generate Encrypt Decrypt http://blog.csdn.net/fenghaibo00/article/details/17248381

	static void SavePubKey(DRSAKey* Key, const std::string &filename);
	static void SavePriKey(DRSAKey* Key, const std::string &filename, const std::string &Password);
	static std::string GenerateRandString();
	static void Randomize();
	static DRSAKey* CreateKey(const std::string &Rand_Str, unsigned long Key_Length);
	static void DestroyKey(DRSAKey *Key);

	static DRSAKey* LoadPubKey(const std::string &filename);
	static DRSAKey* LoadPriKey(const std::string &filename, const std::string &Password);

	static EVP_PKEY* ToEVP(DRSAKey *Key);

	static int RSADecrypt(EVP_PKEY *key, const unsigned char *enc_data, size_t enc_data_len, unsigned char *orig_data, size_t &orig_data_len);
	static int RSAEncrypt(EVP_PKEY *key, const unsigned char *orig_data, size_t orig_data_len, unsigned char *enc_data, size_t &enc_data_len);
};

