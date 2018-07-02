#include <iostream>
#include <string>
#include <algorithm>
#include <cstdlib>
#include "ylink_stack.h"
#include "ylink_queue.h"
#include "parking_lot.h"

#define MAX_CAPACITY 10

using std::cin;
using std::cout;
using std::endl;
using std::string;
using ylink::y_queue;
using ylink::y_stack;

extern int days = 0;
extern int elapsed_minutes = 0;
extern const int minutes_cap = 60 * 24;
extern const int hours_per_day = 24;
extern const int minutes_per_hours = 60;

void show_basic_info();
void get_meta_src(int& opening_hour, double& fee_rate);
void show_command_instruction();

template <int n>
void command_split_execution(parking_area<n>& area, string& direction, string& car_id, string& opt_time);

int main(void)
{
	int opening_hour = 10;
	double rt = 3.0;
	show_basic_info();
	get_meta_src(opening_hour, rt);

	parking_area<MAX_CAPACITY> opt_parking_lot(opening_hour, rt);
	string direction;
	string car_id;
	string opt_time;

	show_command_instruction();
	cout << ">>";
	while (cin >> direction >> car_id >> opt_time)
	{
		command_split_execution(opt_parking_lot, direction, car_id, opt_time);
		cout << ">>";
	}
	cout << "Thanks for your use. Bye!\n";
	system("pause");
	return 0;
}

void show_basic_info()
{
	cout << "Welcome to parking lot imitation system.\nYou need to provide some basic information ";
	cout << "first to start this system.\n\n";

	cout << "Capacity is restrained to 10 by default. Redefine macro MAX_CAPACITY to ";
	cout << "any value you want to resize the capacity.\n\n";
}

void get_meta_src(int& opening_hour, double& fee_rate)
{
	cout << "Please enter the default opening hour.\n";
	cout << "Only accept rounded hour. (Exp: 10 is valid, 10:05 is invalud)\n";
	cout << "Wait for input: ";
	cin >> opening_hour;
	while (opening_hour < 0 || opening_hour > 23)
	{
		cout << "Time ranges from 0 to 23. Please retype the opening hour.\n";
		cout << "Wait for input: ";
		cin >> opening_hour;
	}
	elapsed_minutes = opening_hour * minutes_per_hours;

	cout << "\nPlease enter charging rate (Dollar per minute).\n";
	cout << "Wait for input: ";
	cin >> fee_rate;
	while (fee_rate + 1e-8 < 0)
	{
		cout << "Charging rate should be bigger than 0. Please retype the charging rate.\n";
		cout << "Wait for input: ";
		cin >> fee_rate;
	}
}

void show_command_instruction()
{
	cout << "\nParking lot is prepared for operation.\n";
	cout << "Commands' format are like [Direction] [Car_ID] [time].\n";
	cout << "[Direction]'s format is ""E"" (stands for \"enter\") or ""L"" (stands for \"leave\").\n";
	cout << "[Time]'s format is [Hour]:[Minute]\n";
	cout << "Enter EOF to terminate imitation.\n";
}

template <int n>
void command_split_execution(parking_area<n>& area, string& direction, string& car_id, string& opt_time)
{
	if (direction != "E" || direction != "L")
	{
		int colon_pos = 0;
		if ((colon_pos = opt_time.find(':', 0)) != string::npos)
		{
			parking_car opt_car(car_id);
			string str_h = opt_time.substr(0, colon_pos);
			string str_m = opt_time.substr(colon_pos + 1, opt_time.size() - 1 - colon_pos);

			int t_h = stoi(str_h);
			if (t_h < area.default_hour())
			{
				t_h += hours_per_day;
			}
			int t_m = stoi(str_m);			
			int t = ((t_h - area.default_hour()) * minutes_per_hours) + t_m;
			if (elapsed_minutes + t >= minutes_cap)
			{
				days++;
			}
			elapsed_minutes = (elapsed_minutes + t) % minutes_cap;

			if (direction == "E")
			{
				area.enter_parking_area(opt_car, t);
			}
			else
			{
				area.leave_parking_area(opt_car, t);
			}
		}
		else
		{
			cout << "Invalid time input. Please retype command again.\n";
		}
	}

	else
	{
		cout << "Invalid command. Please retype command again.\n";
	}
}


/*
Test case (Without time carry):
10
3.0
E A0000 10:01
E A1111 10:03
E A2222 10:05
E A3333 10:07
E A4444 10:11
E A5555 10:13
E A6666 10:15
E A7777 10:17
E A8888 10:19
E A9999 10:21
E B0000 10:23
E B2222 10:25
E B4444 10:27
D A4444 10:30
D A5555 10:32
D A7777 10:37
E B7777 10:39
*/

/*
Test case (Time carry considered):
10
3.0
E A1111 23:30
D A1111 0:30
E A2222 1:30
D A2222 3:30
*/
