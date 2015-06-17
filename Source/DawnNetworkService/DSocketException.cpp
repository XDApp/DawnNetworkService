#include "stdafx.h"
#include "DSocketException.h"


DSocketException::DSocketException(const std::string& errorInfo)
	:ErrorInfo(errorInfo)
{
}


DSocketException::~DSocketException()
{
}
