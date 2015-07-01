#pragma once
class DRSAKey
{
private:
	RSA *rsa;
public:
	DRSAKey(const std::string &Rand_Str, unsigned long Key_Length);
	~DRSAKey();
	RSA* GetKey();
};

