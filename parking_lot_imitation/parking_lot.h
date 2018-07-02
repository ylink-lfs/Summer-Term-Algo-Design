#pragma once
//This header contains operations to the Parking Lot project
#include <string>
#include "ylink_stack.h"
#include "ylink_queue.h"
#include "parking_lot.h"

using std::string;
using ylink::y_stack;
using ylink::y_queue;

extern int days;
extern const int minutes_cap;

struct parking_car
{
	//Initialize val to -1 to show problem in potential output
	int parking_time;
	string ID;
	parking_car(const string& id = "Uninitialized", int t = -1) : parking_time(t), ID(id) {}
};

template <int n>
class parking_area
{
private:
	//Assume that there won't be more than 10 cars simutaneously in one parking_lot
	y_stack<parking_car, n> parking_lot;
	y_queue<parking_car> pavement;
	y_stack<parking_car, n> temp_parking_lot;
	double fee_rate;
	int default_opening_hour;
public:
	parking_area() : default_opening_hour(10), fee_rate(1.0), 
		parking_lot(), pavement(), temp_parking_lot() { }
	parking_area(int opening_hour, double fee) : default_opening_hour(opening_hour), fee_rate(fee), 
		parking_lot(), pavement(), temp_parking_lot() { }
	void enter_parking_area(const parking_car& car, const int enter_time);
	void leave_parking_area(const parking_car& car, const int leave_time);
	void reset_fee(double fee) { fee_rate = fee; }
	int default_hour() { return default_opening_hour; }
};

template <int n>
void parking_area<n>::enter_parking_area(const parking_car& car, const int enter_time)
{
	while (!parking_lot.empty() && (car.ID != parking_lot.top().ID))
	{
		parking_car temp = parking_lot.top();
		temp_parking_lot.push(temp);
		parking_lot.pop();
	}
	if (parking_lot.empty())
	{
		while (!temp_parking_lot.empty())
		{
			parking_car temp = temp_parking_lot.top();
			parking_lot.push(temp);
			temp_parking_lot.pop();
		}
		int tot_hour = enter_time / 60;
		int rest_min = enter_time % 60;

		parking_car temp = car;
		if (parking_lot.full() == true)
		{
			pavement.push(temp);
			cout << "Parking lot is full. Temporarily store car " << car.ID << " at pavement.\n";
			cout << "Position ID is " << pavement.rear_index() << ".\n";
		}
		else
		{
			temp.parking_time = enter_time;
			parking_lot.push(temp);
			cout << "Car " << car.ID << " successfully parked in parking lot.\nPosition ID is ";
			cout << parking_lot.front_index() << ".\n";
		}
		cout << "Parking time is ";
		cout.width(2);
		cout.fill('0');
		cout << (default_opening_hour + tot_hour) % 24;
		cout << ":";
		cout.width(2);
		cout.fill('0');
		cout << rest_min;
		cout << ".\n";
	}
	else
	{
		cout << "Replicate car is already in the parking lot. Operation terminated.\n";
	}
	
	
}

template <int n>
void parking_area<n>::leave_parking_area(const parking_car& car, const int leave_time)
{
	while (!parking_lot.empty() && (car.ID != parking_lot.top().ID))
	{
		parking_car temp = parking_lot.top();
		temp_parking_lot.push(temp);
		parking_lot.pop();
	}
	if (parking_lot.empty() == true)
	{
		cout << "Provided Car ID does not exist in the parking lot.\n";
		while (!temp_parking_lot.empty())
		{
			parking_car temp = temp_parking_lot.top();
			parking_lot.push(temp);
			temp_parking_lot.pop();
		}
	}
	else
	{
		parking_car leaving_car = parking_lot.top();
		parking_lot.pop();

		int tot_time = leave_time - leaving_car.parking_time;
		if (tot_time <= 0)
			tot_time += (days - 1) * minutes_cap;
		int tot_hour = tot_time / 60;
		int rest_min = tot_time % 60;

		double charged = tot_time * fee_rate;
		cout << "Car " << car.ID << " successfully left the parking lot.\n";

		cout << "Leaving time is ";
		cout.width(2);
		cout.fill('0');
		cout << (default_opening_hour + tot_hour + leaving_car.parking_time / 60) % 24;
		cout << ":";
		cout.width(2);
		cout.fill('0');
		cout << leaving_car.parking_time % 60 + rest_min;
		cout << ".\n";

		cout << "The parking duration is " << tot_time << " mintues.\n";
		cout << "Total fee is $";
		cout.setf(std::ios_base::fixed);
		cout.precision(2);
		cout << charged << ".\n";

		while (!temp_parking_lot.empty())
		{
			parking_car temp = temp_parking_lot.top();
			parking_lot.push(temp);
			temp_parking_lot.pop();
		}

		if (!pavement.empty())
		{
			parking_car entering_car = pavement.front();
			pavement.pop();
			enter_parking_area(entering_car, leave_time);
		}
	}
}