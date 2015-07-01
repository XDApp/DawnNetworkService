#pragma once
class DResource
{
public:
	DResource();
	virtual ~DResource();

	static std::wstring GetPath(TCHAR* szpath);


	//ANSI <---> Unicode http://www.cnblogs.com/wind-net/archive/2012/10/31/2718329.html
	static std::wstring ANSIToUnicode(const std::string& str);
	static std::string UnicodeToANSI(const std::wstring& str);
};

