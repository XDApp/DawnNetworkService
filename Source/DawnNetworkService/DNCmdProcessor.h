#pragma once

#include "DNCmd.h"

class DNCmdProcessor
{
private:
	std::map<DNCmdType, DNCmd*>cmdTable;
public:
	DNCmdProcessor();
	~DNCmdProcessor();

	DNCmd* DNCmdProcessor::GetCmd(DNCmdType Type);
	void Register(DNCmdType Type, DNCmd* Command);
};

