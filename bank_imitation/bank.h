//bank.h
//bank类的声明文件
#pragma once
#include <queue>
#include <vector>
#include <ctime>
#include "moment.h"
#include "duration.h"

using std::vector;
using std::priority_queue;
using std::queue;
using std::srand;
using std::time;

class bank
{
private:
	struct client
	{
		moment arrive_time;
		duration wait_duration;
		duration issue_duration;
		moment leave_time;
		client(moment arrive_t) : arrive_time(arrive_t) {}
		int total_duration() { return (wait_duration + issue_duration).minute_conversion(); }
	};
	int tot_counter;
	bool shuted;
	moment sentinal_moment;
	vector<client*> left_client;
	vector<queue<client*>*> counter;

	//Newly added info
	duration seed_dur;
	duration max_dur;
	moment opening_time;
	moment closing_time;

	bool has_available_queue();
public:
	bank() : tot_counter(0), shuted(false) { srand(time(nullptr)); }
	bank(int counter_num, duration max_interval = duration(0, 10));
	~bank();

	bank(const bank&) = delete;
	bank& operator=(const bank&) = delete;

	int arrive_client(moment mt);
	client* leave_client(int id, moment mt);
	double shut();
	int size() { return tot_counter; }
	bool is_shuted() { return shuted; }
	void show_status();

	//Newly added function
	void random_imitation();
	void reset_opening_time(moment mt) { opening_time = mt; }
	void reset_closing_time(moment mt) { closing_time = mt; }
	void reset_max_interval(duration dt) { max_dur = dt; }
};