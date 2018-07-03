#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include "maze.h"

using std::ostream;
using std::cin;
using std::cout;
using std::endl;
using std::vector;

struct triple_coordinate
{
	int y, x;
	int direction;
	triple_coordinate() : y(-1), x(-1), direction(-1) {}
	triple_coordinate(int srcy, int srcx, int src_d) : y(srcy), x(srcx), direction(src_d) {}
	friend ostream& operator<<(ostream& os, const triple_coordinate& src_tri) {
		return os << '(' << src_tri.y << ", " << src_tri.x << ", " << src_tri.direction << ')';
	}
};

vector<vector<point>> res;
vector<point> board;
vector<vector<triple_coordinate>> tri_res;
y_stack<point> stk;

void output_coordinate(const vector<vector<point>>& route_res);
void output_triple_coordinate(const vector<vector<triple_coordinate>>& tar_v);
void output_multpile_maze(const vector<vector<point>>& route_res, maze& tar_maze);
void output_meta_info(const maze& tar_maze);
void double_to_triple(vector<vector<triple_coordinate>>& tar_v, vector<vector<point>>& src_v);

void set_framing(int& width, int& length);
void output_menu(int& lower_flag, int& upper_flag);
void pre_operation(maze& src_maze);
void judge_flag(int& flag, int lower, int upper);

int main(void)
{
	cout << "Welcome to maze_solving program. Please decide your data source first\n";

	int wd, lg;
	set_framing(wd, lg);
	
	maze opt_maze(wd, lg);
	pre_operation(opt_maze);

	int lower_flag, upper_flag;
	cout << "Maze generation complete.\n";
	output_menu(lower_flag, upper_flag);
	
	int flag;
	cout << "Wait for input:\n";
	cout << ">>";
	while (cin >> flag)
	{
		judge_flag(flag, lower_flag, upper_flag);
		switch (flag)
		{		
		case 0:
			output_coordinate(res);
			break;
		case 1:
			output_multpile_maze(res, opt_maze);
			break;
		case 2:
			int new_w, new_l;
			set_framing(new_w, new_l);
			opt_maze.resize(new_w, new_l);
			pre_operation(opt_maze);
			cout << "Maze generation complete.\n";
			output_menu(lower_flag, upper_flag);
			break;
		case 3:
			output_meta_info(opt_maze);
			break;
		case 4:
			cout << "Raw maze is showed as below:";
			opt_maze.wipe_mark();
			opt_maze.show(cout);
			break;
		case 5:
			cout << "Triple coordinate is showed as below.\n";
			double_to_triple(tri_res, res);
			output_triple_coordinate(tri_res);
			break;
		case 6:
			output_menu(lower_flag, upper_flag);
			break;
		case 7:
			cout << "Thanks for your use. Bye!\n";
			system("pause");
			exit(EXIT_SUCCESS);
			break;
		}
		cout << "Wait for next flag input. Enter 6 to see the menu again.\n";
		cout << ">>";
	}
	cout << "Terminated by EOF. Bye!\n";
	system("pause");
	return 0;
}

void output_coordinate(const vector<vector<point>>& route_res)
{
	if (route_res.size() == 0)
	{
		cout << "No available route to end point.\n";
		return;
	}
	for (int i = 0; i < route_res.size(); i++)
	{
		cout << "Route " << i + 1 << ":\n";
		for (int j = 0; j < route_res[i].size(); j++)
		{
			cout << route_res[i][j];
			if ((j + 1) % 4 == 0)
			{
				cout << '\n';
			}
			else
			{
				cout << ' ';
			}
		}
		cout << '\n';
	}
	cout << '\n';
}

void output_multpile_maze(const vector<vector<point>>& route_res, maze& tar_maze)
{
	if (route_res.size() == 0)
	{
		cout << "No available route to end point.\n";
		return;
	}
	for (auto it = route_res.begin(); it < route_res.end(); it++)
	{
		cout << "Route " << it - route_res.begin() + 1 << ":";
		tar_maze.append_route(*it);
		tar_maze.show(cout);
		cout << '\n';
	}
}

void output_meta_info(const maze& tar_maze)
{
	cout << "Width: " << tar_maze.get_width() << endl;
	cout << "Length: " << tar_maze.get_length() << endl;
	cout << "Start Point: " << tar_maze.get_start() << endl;
	cout << "End Point: " << tar_maze.get_end() << endl;
}

void double_to_triple(vector<vector<triple_coordinate>>& tar_v, vector<vector<point>>& src_v)
{
	int RIGHT = 0;
	int LEFT = 1;
	int UP = 2;
	int DOWN = 3;
	tar_v.resize(src_v.size());
	for (int i = 0; i < src_v.size(); i++)
	{
		tar_v[i].resize(src_v[i].size());
	}
	for (int i = 0; i < src_v.size(); i++)
	{
		for (int j = 0; j < src_v[i].size(); j++)
		{
			triple_coordinate cur_tri;
			point pt1 = src_v[i][j];
			point pt2 = src_v[i][j + 1];
			cur_tri.y = pt1.y;
			cur_tri.x = pt1.x;
			if (pt1.y == pt2.y && pt1.x < pt2.x)
			{
				cur_tri.direction = RIGHT;
			}
			else if (pt1.y == pt2.y && pt1.x > pt2.x)
			{
				cur_tri.direction = LEFT;
			}
			else if (pt1.x == pt2.x && pt1.y > pt2.y)
			{
				cur_tri.direction = UP;
			}
			else
			{
				cur_tri.direction = DOWN;
			}
			tar_v[i][j] = cur_tri;
		}
	}
}

void output_triple_coordinate(const vector<vector<triple_coordinate>>& tar_v)
{
	if (tar_v.size() == 0)
	{
		cout << "No available route to end point.\n";
		return;
	}
	cout << "Direction flag:\n";
	cout << "0: RIGHT   1: LEFT\n";
	cout << "2: UP      3: DOWN\n";
	for (int i = 0; i < tar_v.size(); i++)
	{		
		cout << "Route " << i + 1 << ":\n";
		for (int j = 0; j < tar_v[i].size() - 1; j++)
		{
			cout << tar_v[i][j];
			if ((j + 1) % 4 == 0)
			{
				cout << '\n';
			}
			else
			{
				cout << ' ';
			}
		}
		cout << '\n';
	}
	cout << '\n';
}

void set_framing(int& width, int& length)
{
	cout << "Please enter width and length number sequentially.\n";
	cout << "Wait for input:\n";
	cout << ">>";
	cin >> width >> length;
	while (width <= 0 || length <= 0)
	{
		cout << "Width and length should bigger than 0. Try again.\n";
		cout << "Wait for input: ";
		cout << ">>";
		cin >> width >> length;
	}
}

void output_menu(int& lower_flag, int& upper_flag)
{
	cout << "Please enter number to switch functions\n";
	cout << "0: Show founded routes in coordinate\n";
	cout << "1: Show the maze and founded routes in picture output\n";
	cout << "2: Resize the maze\n";
	cout << "3: Output the meta info of the maze\n";
	cout << "4: Show maze itself\n";
	cout << "5: Show coordinate in triple format\n";
	cout << "6: Display the menu again\n";
	cout << "7: Quit\n";
	lower_flag = 0;
	upper_flag = 7;
}

void pre_operation(maze& src_maze)
{
	src_maze.manual_generation(cin, cout);
	vector<vector<int>> judger;
	judger.resize(src_maze.get_width() + 2);
	for (auto it = judger.begin(); it < judger.end(); it++)
	{
		(*it).resize(src_maze.get_length() + 2);
	}
	res.clear();
	board.clear();
	cout << "Want to use recursive method or non-recursive method to calculate routes?\n";
	cout << "0. Recursice\t1. Non-recursive\n";
	cout << "Currently Non-recursive method only supports to find one path.\n";
	cout << "Wait for input:\n";
	cout << ">>";
	
	int flag;
	cin >> flag;
	judge_flag(flag, 0, 1);
	switch (flag)
	{
	case 0:
		src_maze.find_all_path(res, board, judger, src_maze.get_start());
		break;
	case 1:
		src_maze.find_all_path(res, judger, src_maze.get_start(), stk);
		break;
	}	
}

void judge_flag(int& flag, int lower, int upper)
{
	while (flag < lower || flag > upper)
	{
		cout << "Invalid command input. Try again.\n";
		cout << "Wait for input:\n";
		cout << ">>";
		cin >> flag;
	}
}

/*
Test Case:
8 8
1 1
8 8
  1 1 1 1 1 1 1
1 0 0 0 0 0 0 1
1 1 1 1 0 0 0 1
1 0 0 1 1 0 0 1
1 0 0 0 1 0 0 1
1 0 0 0 1 0 0 1
1 0 0 0 1 0 0 1
1 1 1 1 1 1 1
*/

/*
Test Case:
4 4
1 1
4 4
  1 1 1
1 0 0 1
1 0 0 1
1 1 1 
*/

/*
Test Case:
8 8
1 1
8 8
  1 0 1 1 1 0 1
1 1 0 1 1 1 0 1
1 1 1 1 0 0 1 1
1 0 0 0 1 1 1 1
1 1 1 0 1 1 1 1
1 0 1 1 1 0 1 1
1 0 0 0 1 0 0 1
0 1 1 1 1 1 1 
*/
