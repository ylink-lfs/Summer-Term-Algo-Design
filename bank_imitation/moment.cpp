//moment.cpp
//moment类函数的实现文件
#include "moment.h"
#include "duration.h"

moment::moment(const duration& dt)
{
	hour = dt.get_hour();
	minute = dt.get_minute();
}

bool moment::operator<(const moment& mt) const
{
	if (hour < mt.hour)
	{
		return true;
	}
	else if (hour > mt.hour)
	{
		return false;
	}
	//Two moments' hours are equal
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

std::ostream& operator<<(std::ostream& os, const moment& mt)
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


moment moment::add_duration(const duration& dt) const
{
	moment sum;
	moment m_dt(dt);
	sum.minute = minute + m_dt.minute;
	sum.hour = (hour + m_dt.hour + sum.minute / 60) % 24;
	sum.minute %= 60;
	return sum;
}

moment moment::sub_duration(const duration& dt) const
{
	moment diff;
	moment m_dt(dt);
	m_dt.hour %= 24;
	m_dt.minute %= 60;
	diff.hour = hour;
	diff.minute = minute;
	if (diff.hour < m_dt.hour)
	{
		diff.hour += 24;
	}
	if (diff.minute < m_dt.minute)
	{
		diff.minute += 60;
		diff.hour -= 1;
	}
	diff.hour -= m_dt.hour;
	diff.minute -= m_dt.minute;
	return diff;
}

duration moment::operator-(const moment& mt) const
{
	moment diff;
	moment modify(hour, minute);
	if (modify < mt)
	{
		
		modify.hour += 24;
	}
	diff.hour = modify.hour - mt.hour;
	diff.minute = modify.minute - mt.minute;
	return diff;
}
