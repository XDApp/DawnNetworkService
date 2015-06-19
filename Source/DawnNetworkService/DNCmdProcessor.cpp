#include "stdafx.h"
#include "DNCmdProcessor.h"


DNCmdProcessor::DNCmdProcessor()
{
}


DNCmdProcessor::~DNCmdProcessor()
{
}

DNCmd* DNCmdProcessor::GetCmd(DNCmdType Type)
{
	return this->cmdTable[Type];
}

void DNCmdProcessor::Register(DNCmdType Type, DNCmd* Command)
{
	this->cmdTable[Type] = Command;
}
