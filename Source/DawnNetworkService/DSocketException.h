#pragma once
class DSocketException
{
public:
	const std::string ErrorInfo;
	DSocketException(const std::string& errorInfo);
	~DSocketException();
};

