#include "stdafx.h"
#include "TIME_TRAVEL.h"
#include "PATH.h"
const string pathc = "input_link.csv";
CTIME_TRAVEL::CTIME_TRAVEL()
{
}


CTIME_TRAVEL::~CTIME_TRAVEL()
{
}

bool CTIME_TRAVEL::read_travel_time(map<int, vector<ITEM>>& items,string tt, int day)
{
	if (!m_parser.OpenCSVFile(pathc, true)) {
		return false;
	}
	map<int, map<int, int>> mp;

	int t(0);
	while (m_parser.ReadRecord())  // if this line contains [] mark, then we will also read field headers.
	{
		if (m_parser.GetValueByFieldName(tt, t) == false)
			continue;

	}
	m_parser.CloseCSVFile();
	return items.size() != 0;
	return false;
}
