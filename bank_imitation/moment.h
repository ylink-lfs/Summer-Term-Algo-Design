//moment.h
//moment类的声明文件
#pragma once
#include <iostream>

class duration;

class moment
{
private:
	int hour;
	int minute;
public:
	moment() : hour(0), minute(0) {}
	moment(int h, int min) : hour(h), minute(min) {}
	moment(const duration& dt);

	bool operator==(const moment& mt) const { return (hour == mt.hour && minute == mt.minute); }
	bool operator!=(const moment& mt) const { return !((*this) == mt); }	
	bool operator>(const moment& mt) const { return !((*this) < mt); }
	bool operator<(const moment& mt) const;
	duration operator-(const moment& mt) const;
	
	moment add_duration(const duration& dt) const;
	moment sub_duration(const duration& dt) const;

	void reset(int h = 0, int min = 0) { hour = h; minute = min; }
	int minute_conversion() const { return hour * 60 + minute; }

	int get_hour() const { return hour; }
	int get_minute() const { return minute; }

	friend std::ostream& operator<<(std::ostream& os, const moment& mt);
};