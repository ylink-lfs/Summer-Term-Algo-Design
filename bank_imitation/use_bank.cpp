//use_bank.cpp
//使用银行模拟程序的主程序
#include <iostream>
#include <string>
#include <cstdlib>
#include "bank.h"

using std::string;
using std::cin;
using std::cout;
using std::endl;

const int infinity = 100;
int lower_flag, upper_flag;

void show_commands(int& lower, int& upper);
void judge_flag(int& flag, int lower, int upper);
void switch_flag(bank& src_bank, int flag);
string get_valid_time();
moment split_time_str(const string& st);

int main(void)
{
	cout << "Welcome to bank business imitation system. Please decide how many counters the bank have.\n";
	cout << "Wait for input:\n";
	cout << ">>";
	int ct_num;

	cin >> ct_num;
	judge_flag(ct_num, 1, infinity);

	bank opt_bank(ct_num);
	cout << "Please decide bank's opening time.\n";
	string st = get_valid_time();
	moment enter_mt = split_time_str(st);
	opt_bank.reset_opening_time(enter_mt);

	cout << "Please decide bank's closing time.\n";
	st = get_valid_time();
	moment close_mt = split_time_str(st);
	opt_bank.reset_closing_time(close_mt);

	cout << "Bank's default max event interval is 10 minutes. ";
	cout << "Do you want to reset bank's max event interval?\n";
	cout << "Enter an new interval to reset the interval or use 00:00 to use default setting.\n";
	st = get_valid_time();
	if (st != "00:00")
	{
		moment m_d = split_time_str(st);
		opt_bank.reset_max_interval(duration(m_d));
	}

	cout << "Bank opens for its business successfully.\n";

	show_commands(lower_flag, upper_flag);
	cout << "Wait for input:\n";
	cout << ">>";
	int command_flag;
	while (cin >> command_flag)
	{
		judge_flag(command_flag, lower_flag, upper_flag);
		switch_flag(opt_bank, command_flag);
		cout << "Wait for next command input. Input 3 to see the menu again.\n";
		cout << "Wait for input:\n";
		cout << ">>";
	}
	cout << "Program terminated by EOF. Bye!\n";
	system("pause");
	return 0;
}

void judge_flag(int& flag, int lower, int upper)
{
	while (flag < lower || flag > upper)
	{
		cout << "Input number should be bigger than " << lower << " and smaller than " << upper << ". Try again.\n";
		cout << "Wait for input:\n";
		cout << ">>";
		cin >> flag;
	}
}

void show_commands(int& lower, int& upper)
{
	cout << "Here are available commands:\n";
	cout << "0: Let one client get into the bank\n";
	cout << "1: Let one client leave the bank\n";
	cout << "2: Shut the bank\n";
	cout << "3: Show the menu again\n";
	cout << "4: Show the current counter status\n";
	cout << "5: Randomly generate events\n";
	cout << "6: Terminate the program\n";
	lower = 0;
	upper = 6;
}

void switch_flag(bank& src_bank, int flag)
{
	switch (flag)
	{
	case 0:
	{
		if (src_bank.is_shuted())
		{
			cout << "Bank is already shuted.\n";
		}
		else
		{
			string st = get_valid_time();
			moment enter_mt = split_time_str(st);
			int pos_id = src_bank.arrive_client(enter_mt);
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
		break;
	case 1:
	{
		if (src_bank.is_shuted())
		{
			cout << "Bank is already shuted.\n";
		}
		else
		{
			cout << "Please enter one counter ID for leaving:\n";
			cout << "Wait for input:\n";
			cout << ">>";
			int id;
			cin >> id;
			judge_flag(id, 0, src_bank.size() - 1);
			string st = get_valid_time();
			moment leave_mt = split_time_str(st);
			src_bank.leave_client(id, leave_mt);
		}		
	}
		break;
	case 2:
	{
		cout << "Bank successfully shuted.\n";
		cout << "The average staying time for each customer is ";
		cout.precision(2);
		cout.setf(std::ios_base::fixed);
		cout << src_bank.shut() << " minutes.\n";
	}
		break;
	case 3:
	{
		show_commands(lower_flag, upper_flag);
	}
		break;
	case 4:
	{
		src_bank.show_status();
	}
		break;
	case 5:
	{
		src_bank.random_imitation();
	}
		break;
	case 6:
	{
		cout << "Thanks for your use. Bye!\n";
		system("pause");
		exit(EXIT_SUCCESS);
	}
		break;
	}
}

string get_valid_time()
{
	string st;
	int colon_pos;
	cout << "Please enter a valid time in format x:y. Exp: 10:30\n";
	cout << "Wait for input:\n";
	cout << ">>";
	cin >> st;
	while ((colon_pos = st.find(':', 0)) == string::npos || colon_pos == 0 || colon_pos == st.size() - 1)
	{
		cout << "Invalid format. Try again.\n";
		cout << "Wait for input:\n";
		cout << ">>";
		cin >> st;
	}
	return st;
}

moment split_time_str(const string& st)
{
	int colon_pos = st.find(':', 0);
	string str_h = st.substr(0, colon_pos);
	string str_m = st.substr(colon_pos + 1, st.size() - colon_pos - 1);
	int hr = stoi(str_h);
	int mn = stoi(str_m);
	return moment(hr, mn);
}

