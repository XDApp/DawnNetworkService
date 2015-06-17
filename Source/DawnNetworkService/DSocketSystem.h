#pragma once
class DSocketSystem
{
public:
	DSocketSystem();
	virtual ~DSocketSystem();

	static WSADATA wsaData;
	static void Initialize();
	static void Dispose();
	static void Exception(const std::string& errorInfo);
};
