#include "stdafx.h"
#include "DConfig.h"
#include "DResource.h"
#include "DRSA.h"

DConfig::DConfig()
{
}


DConfig::~DConfig()
{
}

void DConfig::Load(const std::string &path)
{
}

void DConfig::Save(const std::string &path)
{
	using namespace rapidjson;
	StringBuffer s;
	Writer<StringBuffer> writer(s);
	{
		writer.StartObject();
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
		{
			writer.StartObject();
			writer.EndObject();
		}
		writer.EndObject();
	}
	std::cout << s.GetString() << std::endl;
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
	auto key = DRSA::CreateKey(DRSA::GenerateRandString(), 1024);
	std::string CurrentPath = DResource::UnicodeToANSI(DResource::GetPath(nullptr)) + "\\";

	DRSA::SavePubKey(key, CurrentPath + PubKeyPath);
	DRSA::SavePriKey(key, CurrentPath + PriKeyPath, DefaultPriKeyPassword);


	this->Save();
}