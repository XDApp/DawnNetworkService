#pragma once
class DException
{
public:
	const std::string ErrorInfo;
	DException(const std::string& errorInfo);
	~DException();
};