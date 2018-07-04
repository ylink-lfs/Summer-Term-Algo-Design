//bank.cpp
//bank类成员函数的实现文件
#include <algorithm>
#include <iostream>
#include <string>
#include "bank.h"

using std::find;
using std::cin;
using std::cout;
using std::endl;
using std::string;

bank::bank(int counter_num, duration max_interval)
{
	srand(time(nullptr));
	shuted = false;
	counter.resize(counter_num);
	for (int i = 0; i < counter_num; i++)
	{
		counter[i] = new queue<client*>;
	}
	tot_counter = counter_num;
	max_dur = max_interval;
}

bank::~bank()
{
	for (int i = 0; i < tot_counter; i++)
	{
		
		while(!(counter[i]->empty()))
		{
			client* tmp = counter[i]->front();
			counter[i]->pop();
			delete tmp;
		}
		delete counter[i];
	}
	for (int i = 0; i < left_client.size(); i++)
	{
		delete left_client[i];
	}
}

int bank::arrive_client(moment mt)
{
	if (sentinal_moment > mt || sentinal_moment == mt)
	{
		cout << "This operation will cause program to calculate time over 2 days. Are you sure to continue?\n";
		cout << "Enter \"YES\" to continue or other characters to terminate this process.\n";
		cout << "Wait for input:\n";
		cout << ">>";
		string ft;
		cin >> ft;
		if (ft != "YES")
		{
			return -1;
		}
	}
	sentinal_moment = mt;
	queue<client*>* best_counter = counter[0];
	for (auto it = counter.begin(); it < counter.end(); it++)
	{
		if ((*it)->size() < best_counter->size())
		{
			best_counter = *it;
		}
	}
	client* ct = new client(mt);
	best_counter->push(ct);
	auto it = find(counter.begin(), counter.end(), best_counter);
	return it - counter.begin();
}

bank::client* bank::leave_client(int id, moment mt)
{
	if (sentinal_moment > mt || sentinal_moment == mt)
	{
		cout << "This operation will cause program to calculate time over 2 days. Are you sure to continue?\n";
		cout << "Enter \"YES\" to continue or other characters to terminate this process.\n";
		cout << "Wait for input:\n";
		cout << ">>";
		string ft;
		cin >> ft;
		if (ft != "YES")
		{
			cout << "Operation canceled.\n";
			return nullptr;
		}
	}
	
	if (counter[id]->empty())
	{
		return nullptr;
	}
	else
	{
		client* left_one = counter[id]->front();
		counter[id]->pop();
		left_one->leave_time = mt;
		left_one->issue_duration = (left_one->leave_time - left_one->arrive_time) - left_one->wait_duration;
		left_client.push_back(left_one);
		if (!(counter[id]->empty()))
		{
			client* next_client = counter[id]->front();
			next_client->wait_duration = mt - next_client->arrive_time;
		}
		cout << "Leave operation finished.\n";
		return left_one;
	}
}

double bank::shut()
{
	shuted = true;
	int sum_min = 0;
	for (int i = 0; i < left_client.size(); i++)
	{
		moment cur_duration = left_client[i]->issue_duration + left_client[i]->wait_duration;
		int cur_min = cur_duration.minute_conversion();
		sum_min += cur_min;
	}
	if (sum_min == 0)
		return 0.0;
	else
		return double(sum_min) / left_client.size();
}

void bank::show_status()
{
	cout << "Current counter condition is listed below:\n";
	for (int i = 0; i < tot_counter; i++)
	{
		cout << "Counter " << i << " : ";
		if (counter[i]->size())
		{
			cout << counter[i]->size() << " people in queue.\n";
		}
		else
		{
			cout << "Empty\n";
		}
	}
	cout << '\n';
}

void bank::random_imitation()
{
	while (opening_time.add_duration(seed_dur) < closing_time)
	{
		//1 for come, 0 for leave
		int come_or_out = rand() % 2;
		if (come_or_out)
		{
			duration next_dur;
			next_dur = next_dur.ramdom_generation(max_dur);
			seed_dur = seed_dur + next_dur;
			if (opening_time.add_duration(seed_dur) < closing_time)
			{
				int pos_id = arrive_client(opening_time.add_duration(seed_dur));
				if (pos_id >= 0)
				{
					cout << "Customer successfully get into the bank. Currently at Counter " << pos_id << ".\n";
				}
				else
				{
					cout << "Operation canceled.\n";
				}
			}			
		}
		else
		{
			duration next_dur;
			next_dur = next_dur.ramdom_generation(max_dur);
			seed_dur = seed_dur + next_dur;
			if (opening_time.add_duration(seed_dur) < closing_time)
			{
				if (has_available_queue())
				{
					int id = rand() % counter.size();
					while (counter[id]->empty())
						id = rand() % counter.size();
					bank::client* left_person = leave_client(id, opening_time.add_duration(seed_dur));
					cout << "\nOne client leaved.\n";
					cout << "This client enter the bank at " << left_person->arrive_time << " and leave ";
					cout << "the bank at " << left_person->leave_time << ".\n";
					cout << "His waiting duration is " << left_person->wait_duration << " and issus duration is ";
					cout << left_person->issue_duration << ".\n\n";
					show_status();
				}
				else
				{
					cout << "No counter has customer. Regenerate another event.\n";
				}
			}
		}
		

	}
	cout << "Bank successfully shuted.\n";
	cout << "The average staying time for each customer is ";
	cout.precision(2);
	cout.setf(std::ios_base::fixed);
	cout << shut() << " minutes.\n";
}

bool bank::has_available_queue()
{
	for (int i = 0; i < counter.size(); i++)
	{
		if (counter[i]->size())
			return true;
	}
	return false;
}