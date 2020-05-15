#include "stdafx.h"
#include "TIME_TRAVEL.h"
#include "PATH.h"
const string pathc = "input_link.csv";
const string pathout = "output_link.csv";
const string pathpassenger = "input_agent.csv";
CTIME_TRAVEL::CTIME_TRAVEL()
{
}


CTIME_TRAVEL::~CTIME_TRAVEL()
{
}

bool CTIME_TRAVEL::read_travel_time_in(vector<ITEM>& item,string tt)
{
	if (!m_parser.OpenCSVFile(pathc, true)) {
		return false;
	}
	map<int, map<int, int>> mp;

	
	while (m_parser.ReadRecord())  // if this line contains [] mark, then we will also read field headers.
	{
		int t(0);
		int from(0);
		int to(0);
		if (m_parser.GetValueByFieldName(tt, t) == false)
			continue;
		if (m_parser.GetValueByFieldName("from_node_id", from) == false)
			continue;
		if (m_parser.GetValueByFieldName("to_node_id", to) == false)
			continue;
		mp[from][to] = t;
	}
	for (vector<ITEM>::size_type i= 0; i < item.size();++i)
	{
		auto v = item[i];
		item[i].travel_time = mp[v.from_node.nodeid][v.to_node.nodeid];
	}
	m_parser.CloseCSVFile();
	return item.size() != 0;
	return false;
}

bool CTIME_TRAVEL::read_link_type (vector<ITEM>& item)
{
	if (!m_parser.OpenCSVFile(pathout, true)) {
		return false;
	}
	map<int, map<int, int>> mp;
	while (m_parser.ReadRecord())  // if this line contains [] mark, then we will also read field headers.
	{
		int link_type(0);
		int from(0);
		int to(0);
		if (m_parser.GetValueByFieldName("link_type", link_type) == false)
			continue;
		if (m_parser.GetValueByFieldName("from_node_id", from) == false)
			continue;
		if (m_parser.GetValueByFieldName("to_node_id", to) == false)
			continue;
		mp[from][to] = link_type;
	}
	for (vector<ITEM>::size_type i = 0; i < item.size(); ++i)
	{
		auto v = item[i];
		item[i].link_type = mp[v.from_node.nodeid][v.to_node.nodeid];
		if (item[i].link_type == 0)
			continue;
		item[i].travel_time = 1;
	}
	m_parser.CloseCSVFile();
	return true;
}
struct AGENT {
	int from_node_id, to_node_id;
	int departure_time_start, departure_time_end;
	int arrival_time_start, arrival_time_end;
};
bool CTIME_TRAVEL::read_passenger(vector<ITEM>& item)
{
	if (!m_parser.OpenCSVFile(pathpassenger, true)) {
		return false;
	}
	vector<AGENT> agents;
	while (m_parser.ReadRecord())
	{
		AGENT agent;
		if (m_parser.GetValueByFieldName("from_node_id", agent.from_node_id) == false)
			continue;
		if (m_parser.GetValueByFieldName("to_node_id", agent.to_node_id) == false)
			continue;
		if (m_parser.GetValueByFieldName("departure_time_start", agent.departure_time_start) == false)
			continue;
		if (m_parser.GetValueByFieldName("departure_time_window", agent.departure_time_end) == false)
			continue;
		agent.departure_time_end += agent.departure_time_start;
		if (m_parser.GetValueByFieldName("arrival_time_start", agent.arrival_time_start) == false)
			continue;
		if (m_parser.GetValueByFieldName("arrival_time_window", agent.arrival_time_end) == false)
			continue;
		agent.arrival_time_end += agent.arrival_time_start;
		agents.push_back(agent);
	}
	for (auto v : agents)
	{

	}
	m_parser.CloseCSVFile();
	return true;
}
