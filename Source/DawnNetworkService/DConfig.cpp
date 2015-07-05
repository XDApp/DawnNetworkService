#include "stdafx.h"
#include "DConfig.h"
#include "DResource.h"
#include "DRSA.h"

DConfig::DConfig()
	:pubKeyPath(PubKeyPath),
	priKeyPassword(PriKeyPassword),
	priKeyPath(PriKeyPath),
	PubKey(nullptr),
	PriKey(nullptr)
{
}


DConfig::~DConfig()
{
}

void DConfig::Load(const std::string &path)
{
	using namespace rapidjson;
	FILE* fp = fopen(path.c_str(), "rb");
	char readBuffer[65536];
	FileReadStream fStream(fp, readBuffer, sizeof(readBuffer));
	Document d;
	d.ParseStream(fStream);
	//RSA
	std::string CurrentPath = DResource::UnicodeToANSI(DResource::GetPath(nullptr)) + "\\";
	this->PubKey = DRSA::ToEVP(DRSA::LoadPubKey(CurrentPath + d["Key"]["PublicKeyPath"].GetString()));
	this->PriKey = DRSA::ToEVP(DRSA::LoadPriKey(CurrentPath + d["Key"]["PrivateKeyPath"].GetString(), d["Key"]["PrivateKeyPassword"].GetString()));
	fclose(fp);
}

void DConfig::Save(const std::string &path)
{
	using namespace rapidjson;
	FILE* fp = fopen(path.c_str(), "wb");
	char writeBuffer[65536];
	FileWriteStream fStream(fp, writeBuffer, sizeof(writeBuffer));

	Writer<FileWriteStream> writer(fStream);
	{
			writer.StartObject();
			writer.Key("Key");
			{
				writer.StartObject();
				writer.String("PublicKeyPath");
				writer.Key(this->PubKeyPath.c_str());
				writer.String("PrivateKeyPath");
				writer.Key(this->PriKeyPath.c_str());
				writer.String("PrivateKeyPassword");
				writer.Key(this->PriKeyPassword.c_str());
				writer.EndObject();
			}
			writer.EndObject();
	}
	fclose(fp);
}

std::string DConfig::GetDefaultPath() const
{
	return DResource::UnicodeToANSI(DResource::GetPath(nullptr)) + "\\config.json";
}

void DConfig::Load()
{
	this->Load(this->GetDefaultPath());
}

void DConfig::Save()
{
	this->Save(this->GetDefaultPath());
}


const std::string DefaultPubKeyPath = "Public.DRSAKey";
const std::string DefaultPriKeyPath = "Private.DRSAKey";
const std::string DefaultPriKeyPassword = "123456";

void DConfig::Generate()
{
	using namespace rapidjson;

	this->PubKeyPath = DefaultPubKeyPath;
	this->PriKeyPath = DefaultPriKeyPath;
	this->PriKeyPassword = DefaultPriKeyPassword;

	DRSA::Randomize();
	auto key = DRSA::CreateKey(DRSA::GenerateRandString(), 2048);
	std::string CurrentPath = DResource::UnicodeToANSI(DResource::GetPath(nullptr)) + "\\";

	DRSA::SavePubKey(key, CurrentPath + PubKeyPath);
	DRSA::SavePriKey(key, CurrentPath + PriKeyPath, DefaultPriKeyPassword);


	this->Save();
}
