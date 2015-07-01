#include "stdafx.h"
#include "DException.h"

DException::DException(const std::string& errorInfo)
	:ErrorInfo(errorInfo)
{
}


DException::~DException()
{
}
