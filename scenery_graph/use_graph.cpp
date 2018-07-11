//use_graph.cpp
//主程序
#include <iostream>
#include <fstream>
#include <cstdlib>
#include "scenery_graph.h"

using std::cin;
using std::cout;
using std::endl;
using std::ifstream;

void show_menu(int& lower, int& upper);
void judge_flag(int& flag, int lower, int upper);
bool switch_flag(scenery_graph& src_graph, const int flag);
tuple<string, string, int, int> get_route_info();
tuple<string, string> get_exist_scenery(const scenery_graph& src_graph);
void output_route(const vector<vector<string>>& point_res, const vector<vector<pair<int, int>>> route_res);

vector<vector<string>> point_result;
vector<vector<pair<int, int>>> route_result;

int main(void)
{
	ifstream ist("MapData.txt", std::ios_base::in);
	
	cout << "Welcome to scenery tour guide program.\n";
	
	/*cout << "Please enter the total scenery spots the place have:\n";
	cout << "Wait for input:\n";
	cout << ">>";*/
	int scenery_count;

	//Suit up teacher's file
	ist >> scenery_count;
	ist.get();
	judge_flag(scenery_count, 1, 100);
	scenery_graph opt_graph(scenery_count);

	string dummy;
	getline(ist, dummy);
	int add_base_edge_times;
	ist >> add_base_edge_times;
	for (int i = 0; i < add_base_edge_times; i++)
	{
		string st;
		string ed;
		string method;
		int method_id;
		int dist;
		ist >> st >> ed >> method >> dist;
		opt_graph.add_edge(make_tuple(st, ed, dist, method == "步行" ? 0 : 1));
	}
	ist.close();


	cout << "Initiazation complete.\n";
	cout << "Here are available options:\n";
	int lower_flag, upper_flag;
	show_menu(lower_flag, upper_flag);
	cout << "Wait for input:\n";
	cout << ">>";
	int command_flag;
	while (cin >> command_flag)
	{
		cin.get();
		judge_flag(command_flag, lower_flag, upper_flag);
		bool exit_sentinal = switch_flag(opt_graph, command_flag);
		if (exit_sentinal)
			break;
		else
		{
			cout << "Next input please: (Enter 4 to see menu again)\n";
			cout << "Wait for input:\n";
			cout << ">>";
		}
	}
	cout << "Program terminated. Bye!\n";
	system("pause");
	return 0;
}

void judge_flag(int& flag, int lower, int upper)
{
	while (flag < lower || flag > upper)
	{
		cout << "Input number should be less than " << lower << " or more than " << upper << ".\n";
		cout << "Try again.\n";
		cout << "Wait for input:\n";
		cout << ">>";
		cin >> flag;
	}
}

void show_menu(int& lower, int& upper)
{
	cout << "1: Add one path\n";
	cout << "2: Get total path from one scenery to another\n";
	cout << "3: Get shortest path from one scenery to another\n";
	cout << "4: Show menu again\n";
	cout << "5: Exit\n";
	cout << "Assumption: Use 0 for walk approach, 1 for ropeway approach\n";
	lower = 1;
	upper = 5;
}

bool switch_flag(scenery_graph& src_graph, const int flag)
{
	switch (flag)
	{
	case 1:
	{
		src_graph.add_edge(get_route_info());
		return false;
	}
	break;
	case 2:
	{
		tuple<string, string> points(get_exist_scenery(src_graph));
		src_graph.find_all_path(point_result, route_result, get<0>(points), get<1>(points));
		if (route_result.size())
		{
			cout << "All path are listed below:\n";
			output_route(point_result, route_result);
		}
		else
		{
			cout << "No available route.\n";
		}
		point_result.clear();
		route_result.clear();
		return false;
	}
	break;
	case 3:
	{
		tuple<string, string> points(get_exist_scenery(src_graph));
		src_graph.find_short_path(point_result, route_result, get<0>(points), get<1>(points));
		if (route_result.size())
		{
			cout << "All short path are listed below:\n";
			output_route(point_result, route_result);
		}
		else
		{
			cout << "No available route.\n";
		}
		point_result.clear();
		route_result.clear();
		return false;
	}
	break;
	case 4:
	{
		int dummy1, dummy2;
		show_menu(dummy1, dummy2);
		return false;
	}
	break;
	case 5:
	{
		;
	}
	break;
	}
	return true;
}

tuple<string, string, int, int> get_route_info()
{
	string start_pt;
	string end_pt;
	int distance;
	int method;
	cout << "Please enter the start scenery's name.\n";
	cout << "Wait for input:\n";
	cout << ">>";
	getline(cin, start_pt);
	cout << "Please enter the end scenery's name.\n";
	cout << "Wait for input:\n";
	cout << ">>";
	getline(cin, end_pt);
	cout << "Please enter the distance between the two scenery.\n";
	cout << "Wait for input:\n";
	cout << ">>";
	cin >> distance;
	judge_flag(distance, 1, 0x3eeeeeee);
	cout << "Please enter the method between the two scenery(By walking or by ropeway)\n";
	cout << "Wait for input:\n";
	cout << ">>";
	cin >> method;
	judge_flag(method, 0, 1);
	return make_tuple(start_pt, end_pt, distance, method);
}

tuple<string, string> get_exist_scenery(const scenery_graph& src_graph)
{
	string st;
	string ed;
	cout << "Please enter the start scenery:\n";
	getline(cin, st);
	bool search_guard;
	while ((search_guard = src_graph.judge_scenery_exist(st)) == false)
	{
		cout << "Input secenery doesn't exist in the record. Try again.\n";
		cout << "Wait for input:\n";
		cout << ">>";
		getline(cin, st);
	}
	cout << "Please enter the end scenery:\n";
	getline(cin, ed);
	while ((search_guard = src_graph.judge_scenery_exist(ed)) == false)
	{
		cout << "Input secenery doesn't exist in the record. Try again.\n";
		cout << "Wait for input:\n";
		cout << ">>";
		getline(cin, ed);
	}
	return make_tuple(st, ed);
}

void output_route(const vector<vector<string>>& point_res, const vector<vector<pair<int, int>>> route_res)
{

	cout << "Assumption: in (x, y), x means the route length. y means the method.\n";
	//How many route
	for (int i = 0; i < point_res.size(); i++)
	{
		cout << "Route " << i + 1 << ":\n";
		//The i th route
		for (int j = 0; j < point_res[i].size(); j++)
		{
			cout << point_res[i][j];
			if (j != point_res[i].size() - 1)
			{
				cout << " -- (" << route_res[i][j].first << ", " << ((route_res[i][j].second == 0) ? "步行" : "索道") << ") --> ";
			}
			else
			{
				cout << endl;
			}
		}
	}
	
}

/*
Test Case:
2
AAA
光明顶
石潭
3
光明顶
石潭
2
石潭
光明顶
*/
