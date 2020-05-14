#pragma once
#include "CSVParser.h"
#include <string>
#include <iostream>
using namespace std;
struct PASSENGER {
	int start, end;
};
struct NODE {
	int nodeid, nodetype;
	PASSENGER p;
};

struct ITEM {
	NODE from_node, to_node;
	int travel_time;
	int tntype() { return to_node.nodetype; }
	bool is_common_node() {
		return to_node.nodetype == 0;
	}
	bool is_passenger() {
		return to_node.nodetype == 1;
	}
	bool is_passenger_reach() {
		return to_node.nodetype == 2;
	}
	bool is_car_start_end() {
		return to_node.nodetype == 3;
	}
	int p_start() {
		return to_node.p.start;
	}
	int p_end() {
		return to_node.p.end;
	}
};
class CPATH
{
public:
	CPATH();
	~CPATH();
	bool readpath();
	void out();
	map<int, vector<ITEM>> m_item;
	void setitem(string& paths, int day);
private:
	
	vector<string> m_paths;
	CCSVParser m_parser;
};

double CalculateCostForDays(vector<ITEM>& paths);