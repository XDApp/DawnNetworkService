#pragma once
class DConfig
{
private:
	std::string PubKeyPath;
	std::string PriKeyPath;
	std::string PriKeyPassword;
public:
	DConfig();
	~DConfig();
	void Load(const std::string &path);
	void Save(const std::string &path);
	void Generate();
	std::string GetDefaultPath() const;
	void Load();
	void Save();

	const std::string &pubKeyPath;
	const std::string &priKeyPath;
	const std::string &priKeyPassword;

	EVP_PKEY* PriKey;
	EVP_PKEY* PubKey;
};

