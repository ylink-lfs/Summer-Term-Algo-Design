//duration.h
//duration类的声明文件
#pragma once
#include <iostream>

class moment;

class duration
{
private:
	int hour;
	int minute;
public:
	duration() : hour(0), minute(0) {}
	duration(int h, int min) : hour(h), minute(min) {}
	duration(const moment& mt);

	duration operator+(const duration& dt) const;
	duration operator-(const duration& dt) const;
	bool operator==(const duration& dt) const { return (hour == dt.hour && minute == dt.minute); }
	bool operator!=(const duration& dt) const { return !((*this) == dt); }
	bool operator<(const duration& dt) const;
	bool operator>(const duration& dt) const { return !((*this) < dt); }

	int get_hour() const { return hour; }
	int get_minute() const { return minute; }
	void reset(int h = 0, int min = 0) { hour = h; minute = min; }
	int minute_conversion() const { return hour * 60 + minute; }
	duration ramdom_generation(const duration& max_interval);

	friend std::ostream& operator<<(std::ostream& os, const duration& mt);
};