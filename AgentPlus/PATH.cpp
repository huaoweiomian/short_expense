#include "stdafx.h"
#include "PATH.h"
#include <sstream>
using namespace std;
const string pathc = "output_agent.csv";
const string path_input_link = "input_link.csv";

CPATH::CPATH()
{
}

CPATH::~CPATH()
{
}

bool CPATH::readpath() {
	if (!m_parser.OpenCSVFile(pathc, true)) {
		return false;
	}
	int day = 1;
	string path;
	string lr;
	const string ubc = "Upperbound:";
	while (m_parser.ReadRecord())  // if this line contains [] mark, then we will also read field headers.
	{
		if (m_parser.GetValueByFieldName("LR_iteration", lr) == false)
			continue;

		if (ubc != lr)
			continue;
		
		if(m_parser.GetValueByFieldName("path_node_seq", path)== false)
			continue;
		setitem(path,day++);
		
	}
	m_parser.CloseCSVFile();
	return m_item.size() != 0;
}

bool CPATH::readpassenger()
{
	for(map<int, vector<ITEM> >::iterator it = m_item.begin();
		it != m_item.end(); ++it){ 
		m_tt.read_passenger(it->second);
	}
	return true;
}

bool CPATH::read_link_type() {
	for (map<int, vector<ITEM> >::iterator it = m_item.begin();
		it != m_item.end(); ++it) {
		m_tt.read_link_type(it->second);
	}
	return true;
}

bool CPATH::update_trave_time(vector<ITEM>& path, string tt)
{
	return m_tt.read_travel_time(path, tt);
}

void CPATH::out()
{
	for (auto v : m_paths) {
		cout << v << endl;
	}
}

void CPATH::setitem(string & paths, int day)
{
	stringstream s(paths);
	vector<ITEM> items;
	string tmp1;
	int nodeid(0), nodeidpre(0);
	bool igore_first = true;
	while (getline(s, tmp1, ';'))
	{
		ITEM item;
		nodeid = atoi(tmp1.c_str());
		if (igore_first)
		{
			nodeidpre = nodeid;
			igore_first = false;
			continue;
		}
		item.from_node.nodeid = nodeidpre;
		item.to_node.nodeid = nodeid;
		items.push_back(item);
		nodeidpre = nodeid;
	}
	m_item[day] = items;
}

void CPATH::clean_files()
{
	FILE* f = fopen(pathc.c_str(), "w");
	fclose(f);
}

vector<string> CPATH::read_travel_time_label()
{
	if (!m_parser.OpenCSVFile(path_input_link, true)) {
		return vector<string>();
	}
	vector<string> tt;
	const string ttc = "travel_time";
	for (auto v : m_parser.Headers) {
		if (string::npos != v.find(ttc, 0))
			tt.push_back(v);
	}
	m_parser.CloseCSVFile();
	return tt;
}