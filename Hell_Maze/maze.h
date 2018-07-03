#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "ylink_stack.h"

using std::string;
using std::vector;
using std::istream;
using std::ostream;
using ylink::y_stack;

struct point
{
	int y, x;
	point() : x(0), y(0) {}
	point(int sy, int sx) : y(sy), x(sx) {}
	bool operator==(const point& src_point) { return x == src_point.x && y == src_point.y; }
	const point operator+(const point& src_point) { return point(y + src_point.y, x + src_point.x); }

	friend ostream& operator<<(ostream& os, const point& src_point) {
		return os << '(' << src_point.y << ", " << src_point.x << ')';
	}
};

//Notice that one extended ASCII char takes two original ASCII chars' space
class maze
{
private:
	int width;
	int length;

	struct
	{
		string outer_wall = "¨€";
		string inner_wall = "¡õ";
		string space = "  ";
		string left_cur = "¡û";			
		string right_cur = "¡ú";
		string up_cur = "¡ü";
		string down_cur = "¡ý";
		string start_point = "ST";
		string end_point = "ED";
		string visited = "¨è";
	} maze_symbol;
	vector<vector<string>> maze_body;

	struct
	{
		point up = point(-1, 0);
		point down = point(1, 0);
		point left = point(0, -1);
		point right = point(0, 1);
	} valid_direction;

	point start;
	point end;
	int edge_switcher();
	int wal_g_switcher(int n);
	void point_generation(point& src_point, int restrain_id);
	bool check_coor(const point& check_point);
	bool is_unarrivable(const point& src_point, vector<vector<int>>& judger_board);
	bool test_around_area(point& src_point, vector<vector<int>>& judger_board);
public:
	maze() { width = length = 0; }
	maze(int width, int length);

	void resize(int width, int length);

	void random_generation(ostream& os);
	void manual_generation(istream& ist, ostream& os);
	void show(ostream& os);

	void wipe_mark();
	void find_all_path(vector<vector<point>>& res_v, vector<point>& board, 
		vector<vector<int>>& judger_board, point cur_p);
	void find_all_path(vector<vector<point>>& res_v, vector<vector<int>>& judger_board, 
		point cur_p, y_stack<point>& stk);
	point get_start() const { return start; }
	point get_end() const { return end; }
	int get_width() const { return width; }
	int get_length() const { return length; }
	void append_route(const vector<point>& src_v);
};