//duration.cpp
//duration类成员函数的实现文件
#include <cstdlib>
#include <ctime>
#include "duration.h"
#include "moment.h"

using std::srand;
using std::time;
using std::rand;

duration::duration(const moment& mt)
{
	hour = mt.get_hour();
	minute = mt.get_minute();
}

//Two duration's plus
duration duration::operator+(const duration& mt) const
{
	duration sum;
	sum.minute = minute + mt.minute;
	sum.hour = hour + mt.hour + sum.minute / 60;
	sum.minute %= 60;
	return sum;
}

duration duration::operator-(const duration& mt) const
{
	duration diff;
	int tot1, tot2;
	tot1 = mt.minute + 60 * mt.hour;
	tot2 = minute + 60 * hour;
	diff.minute = (tot2 - tot1) % 60;
	diff.hour = (tot2 - tot1) / 60;
	return diff;
}

bool duration::operator<(const duration& mt) const
{
	if (hour < mt.hour)
	{
		return true;
	}
	else if (hour > mt.hour)
	{
		return false;
	}
	//Two durations' hours are equal
	else
	{
		if (minute < mt.minute)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}

std::ostream& operator<<(std::ostream& os, const duration& mt)
{
	os.fill('0');
	os.width(2);
	os << mt.hour;
	os << ':';
	os.width(2);
	os << mt.minute;
	os.width(0);
	return os;
}

duration duration::ramdom_generation(const duration& max_interval)
{
	duration rd;
	rd.hour = rand() % (max_interval.hour + 1);
	rd.minute = rand() % max_interval.minute + 1;
	return rd;
}