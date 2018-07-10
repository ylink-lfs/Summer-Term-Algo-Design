#pragma once
#include <string>
#include <iostream>
#include "sort_display.h"

using std::ostream;
using std::string;

struct singer_participant
{
	string name;
	string id;
	int current_like;

	singer_participant(const string& nm = "Uninitialized", const string& identifier = "N/A", 
		const int like_num = 0) : name(nm), id(identifier), current_like(like_num) {}

	bool operator<(const singer_participant& pt) { return current_like < pt.current_like; }
	bool operator>(const singer_participant& pt) { return current_like > pt.current_like; }

	friend ostream& operator<<(ostream& os, const singer_participant& pt)
	{
		os.width(15);
		os.fill(' ');
		os << pt.name;
		os.width(15);
		os.fill(' ');
		os << pt.id;
		os.width(15);
		os.fill(' ');
		os << pt.current_like;
		return os;
	}
};

class singer_voter
{
private:
	sort_display<singer_participant> sort_res;
	y_dynamic_array<singer_participant> singer_info;
public:
	singer_voter() {}
	singer_voter(const y_dynamic_array<singer_participant>& src_data) : singer_info(src_data) {}
	void multiple_sort();
	void vote_one_singer(int id);
	y_dynamic_array<singer_participant> get_sorted_result() { return sort_res.get_sequence(); }
	void show_current_singer_info() const;
	int get_current_member_num() const { return singer_info.size(); }
};