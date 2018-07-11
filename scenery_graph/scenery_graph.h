//scenery_graph.h
//scenery_graph类的声明文件
#pragma once
#include <set>
#include <vector>
#include <string>
#include <tuple>
#include <deque>
#include <unordered_map>

using std::set;
using std::vector;
using std::pair;
using std::tuple;
using std::deque;
using std::string;
using std::unordered_map;
using std::make_tuple;
using std::get;

//This class needs a total scenery number to function
class scenery_graph
{
private:
	struct node
	{
		int dest;
		int weight;
		int method;  //0 for walk, 1 for ropeway
		node(int dst = 0, int wt = 0, int md = 0) : dest(dst), weight(wt), method(md) {}
	};
	const int infinity = 0x3fffffff;
	vector<vector<node>> adjectant_table;
	vector<set<int>> pre_path;
	vector<int> short_distance;
	deque<bool> visited;
	unordered_map<string, int> hash_str;
	unordered_map<int, string> hash_back;
	int get_method_sumval(const vector<pair<int, int>>& src_vec);
	
	void find_all_path(vector<vector<string>>& point_res, vector<vector<pair<int, int>>>& route_res,
		vector<int>& current_route, const int start, const int end);

	void find_short_path(vector<vector<string>>& point_res, vector<vector<pair<int, int>>>& route_res,
		vector<int>& current_route, const int start, const int end);

	void SPFA(const int start);

	void initialize_assist_array(const int start);
public:
	scenery_graph(int tot_scenery = 0) 
	{ 
		adjectant_table.resize(tot_scenery); pre_path.resize(tot_scenery); 
		short_distance.resize(tot_scenery); visited.resize(tot_scenery);
	}

	void add_edge(const tuple<string, string, int, int>& one_route);

	void find_all_path(vector<vector<string>>& point_res, vector<vector<pair<int, int>>>& path_res, 
		const string& start, const string& end);

	void find_short_path(vector<vector<string>>& res, vector<vector<pair<int, int>>>& path_res,
		const string& start, const string& end);

	bool judge_scenery_exist(const string& scenery) const;
};