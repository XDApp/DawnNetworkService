#pragma once

class DRSAKey;

class DRSA
{
public:
	DRSA();
	virtual ~DRSA();

	static void SavePubKey(DRSAKey* Key, const std::string &filename);
	static void SavePriKey(DRSAKey* Key, const std::string &filename, const std::string &Password);
	static std::string GenerateRandString();
	static void Randomize();
	static DRSAKey* CreateKey(const std::string &Rand_Str, unsigned long Key_Length);
	static void DestroyKey(DRSAKey *Key);

	static DRSAKey* LoadPubKey(const std::string &filename);
	static DRSAKey* LoadPriKey(const std::string &filename, const std::string &Password);

	static EVP_PKEY* ToEVP(DRSAKey *Key);
};

