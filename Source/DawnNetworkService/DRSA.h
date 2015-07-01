#pragma once

class DRSAKey;

class DRSA
{
public:
	DRSA();
	virtual ~DRSA();

	static void SavePubKey(DRSAKey* Key, const std::string &filename);
	static void SavePriKey(DRSAKey* Key, const std::string &filename, std::string Password);
	static std::string GenerateRandString();
	static void Randomize();
};

