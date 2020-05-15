#pragma once
#include "CSVParser.h"
struct ITEM;
class CTIME_TRAVEL
{
public:
	CTIME_TRAVEL();
	~CTIME_TRAVEL();
	bool read_travel_time_in(vector<ITEM>& item, string tt);
	bool read_link_type(vector<ITEM>& item);
	bool read_passenger(vector<ITEM>& item);
	CCSVParser m_parser;
};

