//scenery_graph.cpp
//scenery_graph类的实现文件
#include <algorithm>
#include "scenery_graph.h"

using std::fill;
using std::make_pair;

//Public Method

void scenery_graph::add_edge(const tuple<string, string, int, int>& one_route)
{
	auto start_it = hash_str.find(get<0>(one_route));
	auto end_it = hash_str.find(get<1>(one_route));
	if (start_it == hash_str.end())
	{
		int cur_size = hash_str.size();
		hash_str[get<0>(one_route)] = cur_size;
		hash_back[cur_size] = get<0>(one_route);
	}
	if (end_it == hash_str.end())
	{
		int cur_size = hash_str.size();
		hash_str[get<1>(one_route)] = cur_size;
		hash_back[cur_size] = get<1>(one_route);
	}

	int start_index = hash_str[get<0>(one_route)];
	int end_index = hash_str[get<1>(one_route)];
	int dist = get<2>(one_route);
	//0 for walk, 1 for ropeway
	int method_num = get<3>(one_route);

	adjectant_table[start_index].push_back(node(end_index, dist, method_num));
}

//Call private find_all_path method
void scenery_graph::find_all_path(vector<vector<string>>& point_res, 
	vector<vector<pair<int, int>>>& path_res, const string& start, const string& end)
{
	fill(visited.begin(), visited.end(), false);
	vector<int> recursion_board;
	find_all_path(point_res, path_res, recursion_board, hash_str[start], hash_str[end]);
}

//Call private find_short_path method
void scenery_graph::find_short_path(vector<vector<string>>& point_res,
	vector<vector<pair<int, int>>>& path_res, const string& start, const string& end)
{
	SPFA(hash_str[start]);
	fill(visited.begin(), visited.end(), false);
	vector<int> recursion_board;
	find_short_path(point_res, path_res, recursion_board, hash_str[start], hash_str[end]);
}

//Before call the two search func, use this func in main() to judge str's legality
bool scenery_graph::judge_scenery_exist(const string& scenery) const
{
	if (hash_str.find(scenery) == hash_str.end())
		return false;
	else
		return true;
}

//Private Method

//DFS from the give start point. every time it recur, push one point ID into current_route
//As long as it reaches the end point, iterate current_route from .begin(), and get path info
//with adjectant ID i and i + 1 in current_route, search the adjectant_table for the route_res
void scenery_graph::find_all_path(vector<vector<string>>& point_res,
	vector<vector<pair<int, int>>>& route_res, vector<int>& current_route, const int start, const int end)
{
	if (start == end)
	{
		//Judge from one place to the same place
		if (current_route.empty())
			return;
		//Long travel...Let's record the result
		else
		{
			current_route.push_back(start);
			vector<string> path_point_name;
			vector<pair<int, int>> path_route_condition;
			for (auto it = current_route.begin(); it < current_route.end(); it++)
			{
				path_point_name.push_back(hash_back[*it]);
				if (it != current_route.end() - 1)
				{
					int dest_node_index;

					//This loop will break with an available result for sure
					for (dest_node_index = 0; dest_node_index < adjectant_table[*it].size(); dest_node_index++)
					{
						if (adjectant_table[*it][dest_node_index].dest == *(it + 1))
							break;
					}
					path_route_condition.push_back(make_pair(adjectant_table[*it][dest_node_index].weight,
						adjectant_table[*it][dest_node_index].method));
				}
			}
			point_res.push_back(path_point_name);
			route_res.push_back(path_route_condition);

			current_route.pop_back();
			return;
		}
	}
	else if (visited[start] == true)
		return;
	else
	{
		visited[start] = true;
		current_route.push_back(start);
		for (auto& cur_node : adjectant_table[start])
		{			
			find_all_path(point_res, route_res, current_route, cur_node.dest, end);
		}
		current_route.pop_back();
		visited[start] = false;
	}
}

//Call SPFA() first. Then Use pre_path to recur. As long as it reaches the start, 
//iterate current_route from .rbegin() , and get path like above. Adjectant ID is i and i - 1
void scenery_graph::find_short_path(vector<vector<string>>& point_res, 
	vector<vector<pair<int, int>>>& route_res, vector<int>& current_route, const int start, const int end)
{
	if (start == end)
	{
		if (current_route.empty())
			return;
		else
		{
			current_route.push_back(start);
			vector<string> path_point_name;
			vector<pair<int, int>> path_route_condition;
			//Reverse iteration
			for (auto it = current_route.rbegin(); it < current_route.rend(); it++)
			{
				path_point_name.push_back(hash_back[*it]);
				if (it != current_route.rend() - 1)
				{
					int dest_node_index;

					//This loop will break with an available result for sure
					for (dest_node_index = 0; dest_node_index < adjectant_table[*it].size(); dest_node_index++)
					{
						if (adjectant_table[*it][dest_node_index].dest == *(it + 1))
							break;
					}
					path_route_condition.push_back(make_pair(adjectant_table[*it][dest_node_index].weight,
						adjectant_table[*it][dest_node_index].method));
				}
			}

			if (!route_res.empty() && 
				(get_method_sumval(route_res[0]) < get_method_sumval(path_route_condition)))
			{
				point_res.clear();
				route_res.clear();
			}
			point_res.push_back(path_point_name);
			route_res.push_back(path_route_condition);

			current_route.pop_back();
			return;
		}
	}
	else
	{
		current_route.push_back(end);
		for (auto it = pre_path[end].begin(); it != pre_path[end].end(); it++)
		{
			find_short_path(point_res, route_res, current_route, start, *it);
		}
		current_route.pop_back();
	}
}

//Get shortest distance and pre_path array
//Get all shortest path with one start point
//Concentrate on pre_path array, in this function I don't have to care about other weights
//Only short_dist and pre_path
void scenery_graph::SPFA(const int start)
{
	initialize_assist_array(start);
	deque<int> q;
	q.push_front(start);
	visited[start] = true;
	while (!q.empty())
	{
		int cur = q.front();
		q.pop_front();
		visited[cur] = false;

		//No num[MAXN]:
		//In this situation, negative-cost-cycle will be eliminated in the main() input
		for (auto& cur_node : adjectant_table[cur])
		{
			//All graph algorithms' frame are like each other
			if (short_distance[cur_node.dest] > short_distance[cur] + cur_node.weight)
			{
				pre_path[cur_node.dest].clear();
				pre_path[cur_node.dest].insert(cur);
				short_distance[cur_node.dest] = short_distance[cur] + cur_node.weight;
				if (!visited[cur_node.dest])
				{
					//SLF, small label first
					if (q.empty() || (short_distance[cur_node.dest] < short_distance[q.front()]))
					{
						q.push_front(cur_node.dest);
					}
					else
					{
						q.push_back(cur_node.dest);
					}

					visited[cur_node.dest] = true;
				}
			}
			else if (short_distance[cur_node.dest] == short_distance[cur] + cur_node.weight)
			{
				pre_path[cur_node.dest].insert(cur);
			}
		}
	}
}

//Initialize array for SPFA execution
void scenery_graph::initialize_assist_array(const int start)
{
	for (auto& cur : pre_path)
		cur.clear();
	fill(short_distance.begin(), short_distance.end(), infinity);
	fill(visited.begin(), visited.end(), false);
	short_distance[start] = 0;
}

int scenery_graph::get_method_sumval(const vector<pair<int, int>>& src_vec)
{
	int sum = 0;
	for (auto& it : src_vec)
		sum += it.second;
	return sum;
}