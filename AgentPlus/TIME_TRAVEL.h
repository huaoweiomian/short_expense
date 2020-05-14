#pragma once
#include "CSVParser.h"
struct ITEM;
class CTIME_TRAVEL
{
public:
	CTIME_TRAVEL();
	~CTIME_TRAVEL();
	bool read_travel_time(map<int, vector<ITEM>>& items, string tt, int day);
	CCSVParser m_parser;
};

