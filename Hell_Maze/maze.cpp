#include <iostream>
#include <cstdlib>
#include <ctime>
#include "maze.h"

using std::ostream;
using std::rand;
using std::srand;
using std::time;

maze::maze(int src_width, int src_length)
{
	width = src_width;
	length = src_length;
	maze_body.resize(width + 2);
	for (auto it = maze_body.begin(); it < maze_body.end(); it++)
	{
		(*it).resize(length + 2);
	}
	for (int i = 0; i < width + 2; i++)
	{
		for (int j = 0; j < length + 2; j++)
		{
			if (i == 0 || j == 0 || i == width + 1 || j == length + 1)
			{
				maze_body[i][j] = maze_symbol.outer_wall;
			}
			else
			{
				maze_body[i][j] = maze_symbol.space;
			}
		}
	}
}

void maze::random_generation(ostream& os)
{
	srand(time(nullptr));
	int restrain_start = edge_switcher();
	int restrain_end = edge_switcher();
	point_generation(start, restrain_start);
	point_generation(end, restrain_end);
	if (start == end)
		point_generation(end, restrain_end);
	maze_body[start.y][start.x] = maze_symbol.start_point;
	maze_body[end.y][end.x] = maze_symbol.end_point;
	for (int i = 1; i <= width; i++)
	{
		for (int j = 1; j <= length; j++)
		{
			point current = point(i, j);
			if (current == start || current == end)
				continue;
			else
			{
				//If random result is 0, then generate wall in the position
				//Else, generate space in the position
				if (wal_g_switcher(2))
				{
					maze_body[i][j] = maze_symbol.space;
				}
				else
				{
					maze_body[i][j] = maze_symbol.inner_wall;
				}
			}
		}
	}
}

void maze::point_generation(point& src_point, int restrain_id)
{
	switch (restrain_id)
	{
	case 0:
		src_point.y = 1;
		src_point.x = rand() % length + 1;
		break;
	case 1:
		src_point.y = rand() % width + 1;
		src_point.x = 1;
		break;
	case 2:
		src_point.y = width;
		src_point.x = rand() % length + 1;
		break;
	case 3:
		src_point.y = rand() % width + 1;
		src_point.x = length;
		break;
	}
}

//Return val ranges from 0 to 3
//0: Generate following point like (1, [x])
//1: Generate following point like ([x], 1)
//2: Generate following point like (width, [x])
//3: Generate following point like ([x], length)
inline int maze::edge_switcher()
{
	return rand() % 4;
}

int maze::wal_g_switcher(int n)
{
	return rand() % n;
}

void maze::resize(int src_width, int src_length)
{
	width = src_width;
	length = src_length;
	maze_body.clear();
	maze_body.resize(width + 2);
	
	for (auto it = maze_body.begin(); it < maze_body.end(); it++)
	{
		(*it).resize(length + 2);
	}
	for (int i = 0; i < width + 2; i++)
	{
		for (int j = 0; j < length + 2; j++)
		{
			if (i == 0 || j == 0 || i == width + 1 || j == length + 1)
			{
				maze_body[i][j] = maze_symbol.outer_wall;
			}
			else
			{
				maze_body[i][j] = maze_symbol.space;
			}
		}
	}
}

void maze::manual_generation(istream& ist, ostream& os)
{
	os << "Maze's width is " << width << " and length is " << length << ".\n";
	os << "Please enter a start point coordinate in format [y] [x].\n";;
	os << "Start point must be positioned on edge.\n";
	os << "Wait for input:\n>>";
	ist >> start.y >> start.x;
	while (check_coor(start))
	{
		os << "Invalid coordinate. Try again.\n";
		os << "Wait for input:\n>>";
		ist >> start.y >> start.x;
	}
	os << "Please enter an end point coordinate in format [y] [x].\n";;
	os << "End point must be positioned on edge.\n";
	os << "Wait for input:\n>>";
	ist >> end.y >> end.x;
	while (check_coor(end))
	{
		os << "Invalid coordinate. Try again.\n";
		os << "Wait for input:\n>>";
		ist >> end.y >> end.x;
	}
	while (end == start)
	{
		os << "Two vital points have replicate coordinate. Please retype coordinate for end point.\n";
		os << "Wait for input:\n>>";
		ist >> end.y >> end.x;
		while (check_coor(end))
		{
			os << "Invalid coordinate. Try again.\n";
			os << "Wait for input:\n>>";
			ist >> end.y >> end.x;
		}
	}
	maze_body[start.y][start.x] = maze_symbol.start_point;
	maze_body[end.y][end.x] = maze_symbol.end_point;
	for (int i = 1; i <= width; i++)
	{
		for (int j = 1; j <= length; j++)
		{
			point current = point(i, j);
			if (current == start || current == end)
				continue;
			else
			{
				os << "Current position is maze[" << i << "][" << j << "].\n";
				os << "Wish this position has a wall or space? Wall for 0, space for 1.\n";
				os << "Wait for input:\n>>";
				int flag = 0;
				ist >> flag;
				while (flag < 0 || flag > 1)
				{
					os << "Invalid flag. Try again.\n";
					os << "Wait for input:\n>>";
					ist >> flag;
				}
				if (flag)
				{
					maze_body[i][j] = maze_symbol.space;
				}
				else
				{
					maze_body[i][j] = maze_symbol.inner_wall;
				}
				os << "The current maze is like below:";
				show(os);
				os << '\n';
			}
		}
	}
}

bool maze::check_coor(const point& check_point)
{
	if (check_point.y == 1)
	{
		if (check_point.x >= 1 && check_point.x <= length)
			return false;
		else
			return true;
	}
	else if (check_point.y == width)
	{
		if (check_point.x >= 1 && check_point.x <= length)
			return false;
		else
			return true;
	}
	else if (check_point.x == 1)
	{
		if (check_point.y >= 1 && check_point.y <= width)
			return false;
		else
			return true;
	}
	else if (check_point.x == length)
	{
		if (check_point.y >= 1 && check_point.y <= width)
			return false;
		else
			return true;
	}
	else
	{
		return true;
	}
}

void maze::show(ostream& os)
{
	os << '\n';
	for (int i = 0; i < width + 2; i++)
	{
		for(int j = 0; j < length + 2; j++)
		{
			os << maze_body[i][j];
		}
		os << '\n';
	}
}

void maze::wipe_mark()
{
	for (int i = 1; i <= width; i++)
	{
		for (int j = 1; j <= length; j++)
		{
			point current(i, j);
			if (current == start || current == end)
				continue;
			else
			{
				if (maze_body[i][j] != maze_symbol.inner_wall && maze_body[i][j] != maze_symbol.space)
				{
					maze_body[i][j] = maze_symbol.space;
				}
			}
		}
	}
}

void maze::find_all_path(vector<vector<point>>& res_v, vector<point>& board, 
	vector<vector<int>>& judger_board, point cur_p)
{
	if (maze_body[cur_p.y][cur_p.x] == maze_symbol.end_point)
	{
		board.push_back(cur_p);
		res_v.push_back(board);
		board.pop_back();
		return;
	}
	else if (is_unarrivable(cur_p, judger_board))
	{
		return;
	}
	else
	{
		board.push_back(cur_p);
		judger_board[cur_p.y][cur_p.x] = 1;

		find_all_path(res_v, board, judger_board, cur_p + valid_direction.up);
		find_all_path(res_v, board, judger_board, cur_p + valid_direction.down);
		find_all_path(res_v, board, judger_board, cur_p + valid_direction.left);
		find_all_path(res_v, board, judger_board, cur_p + valid_direction.right);	

		judger_board[cur_p.y][cur_p.x] = 0;
		board.pop_back();
	}
}

//After finish implementation with vector's push and pop, add stack operation inside
void maze::find_all_path(vector<vector<point>>& res_v, vector<vector<int>>& judger_board,
	point cur_p, y_stack<point>& stk)
{
	while (!stk.empty())
		stk.pop();
	point current = cur_p;
	vector<point> board;
	stk.push(current);
	judger_board[current.y][current.x] = 1;

	while (!stk.empty())
	{
		bool check = test_around_area(current, judger_board);
		if (current == end)
		{
			stk.push(current);
			y_stack<point> tmp;
			while (!stk.empty())
			{
				point t = stk.top();
				stk.pop();
				tmp.push(t);
			}
			while (!tmp.empty())
			{
				board.push_back(tmp.top());
				tmp.pop();
			}
			res_v.push_back(board);
			return;
		}
		
		else if (check)
		{
			stk.push(current);
			judger_board[current.y][current.x] = 1;
		}
		else
		{
			while (!stk.empty())
			{
				stk.pop();
				current = stk.top();
				bool flag = test_around_area(current, judger_board);
				if (flag)
				{
					stk.push(current);
					judger_board[current.y][current.x] = 1;
					break;
				}
				else
				{
					continue;
				}
			}
		}
	}
}


bool maze::test_around_area(point& src_point, vector<vector<int>>& judger_board)
{
	if (!is_unarrivable(src_point + valid_direction.up, judger_board))
	{
		src_point = src_point + valid_direction.up;
		return true;
	}
	else if (!is_unarrivable(src_point + valid_direction.down, judger_board))
	{
		src_point = src_point + valid_direction.down;
		return true;
	}
	else if (!is_unarrivable(src_point + valid_direction.left, judger_board))
	{
		src_point = src_point + valid_direction.left;
		return true;
	}
	else if (!is_unarrivable(src_point + valid_direction.right, judger_board))
	{
		src_point = src_point + valid_direction.right;
		return true;
	}
	else
		return false;
}

bool maze::is_unarrivable(const point& src_point, vector<vector<int>>& judger_board)
{
	if (src_point.x < 1 || src_point.x > length)
		return true;
	else if (src_point.y < 1 || src_point.y > length)
		return true;
	else if (maze_body[src_point.y][src_point.x] == maze_symbol.inner_wall)
		return true;
	else if (maze_body[src_point.y][src_point.x] == maze_symbol.outer_wall)
		return true;
	else if (maze_body[src_point.y][src_point.x] == maze_symbol.visited)
		return true;
	else if (judger_board[src_point.y][src_point.x] == 1)
		return true;
	else
		return false;
}

void maze::append_route(const vector<point>& src_v)
{
	wipe_mark();
	for (int i = 0; i < src_v.size() - 2; i++)
	{
		point pt1 = src_v[i];
		point pt2 = src_v[i + 1];
		if (pt1.y == pt2.y && pt1.x < pt2.x)
		{
			maze_body[pt2.y][pt2.x] = maze_symbol.right_cur;
		}
		else if (pt1.y == pt2.y && pt1.x > pt2.x)
		{
			maze_body[pt2.y][pt2.x] = maze_symbol.left_cur;
		}
		else if (pt1.x == pt2.x && pt1.y > pt2.y)
		{
			maze_body[pt2.y][pt2.x] = maze_symbol.up_cur;
		}
		else
		{
			maze_body[pt2.y][pt2.x] = maze_symbol.down_cur;
		}
	}
}