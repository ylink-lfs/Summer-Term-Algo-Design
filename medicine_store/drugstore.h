//drugstore.h
//drugstoreµÄÀàÉùÃ÷
#pragma once
#include <vector>
#include <string>
#include <iostream>

using std::string;
using std::vector;
using std::ostream;

struct medicine
{
	string name;
	string id;
	double unit_price;
	int current_selling_quantity;
	double current_selling_value;
	medicine() : name("Uninitialized"), id("Uninitialized"), unit_price(0.0), current_selling_quantity(0), current_selling_value(0.0) {}
 	medicine(const string& ID, const string& nm, const double uprice, const int quantity, const double sval) :
		id(ID), name(nm), unit_price(uprice), current_selling_quantity(quantity), current_selling_value(sval) {}
	friend ostream& operator<<(ostream& os, const medicine& md)
	{
		os.precision(2);
		os.setf(std::ios_base::fixed);
		
		os.width(4);
		os.fill(' ');
		os << md.id;
		os.width(25);
		os.fill(' ');
		os << md.name;
		os.width(25);
		os.fill(' ');
		os << md.unit_price;
		os.width(25);
		os.fill(' ');
		os << md.current_selling_quantity;
		os.width(25);
		os.fill(' ');
		os << md.current_selling_value;
		return os;
	}
};

class drugstore
{
private:
	vector<medicine> medicine_selling_info;

	void med_bubble_sort();

	void med_quick_sort();
	void quick_sort(int left_bound, int right_bound);
	void create_pivot(int left_bound, int right_bound);
	void insertion_sort(int left_bound, int right_bound);

	void med_heap_sort();
	void create_maxheap();
	void maxheap_up_adjust(int lower, int upper);
	void maxheap_down_adjust(int lower, int upper);


	void med_merge_sort();
	void merge_sort(medicine* sort_board, int left_bound, int right_bound);
	void merge(medicine* sort_board, int left_start, int left_end,
		int right_start, int right_end);

	void med_radix_sort();

	void reshuffle();
public:
	//unit price for bubble sort, selling quantity for quick sort
	//selling value for heap sort, name for merge sort, ID for radix sort(least significant digit first)
	enum sort_switcher{UNIT_PRICE, SELLING_QUANTITY, SELLING_VALUE, NAME, ID};
	drugstore() {}
	drugstore(const vector<medicine>& src) : medicine_selling_info(src) {}
	drugstore(const medicine* src, const int tot_elem);

	void medicine_sort(const enum sort_switcher sort_method);
	void show_result() const;
};