#include "stdafx.h"
#include "PATH.h"
#include <sstream>
using namespace std;
const string pathc = "output_agent.csv";

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
		setitem(path);
		m_paths.push_back(path);
	}
	m_parser.CloseCSVFile();
	return m_paths.size() != 0;
}

void CPATH::out()
{
	for (auto v : m_paths) {
		cout << v << endl;
	}
}

void CPATH::setitem(string & paths)
{
	stringstream s(paths);
	m_item;
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
}
