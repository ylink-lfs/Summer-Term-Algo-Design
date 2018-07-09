//address_book.cpp
//实现了address_book类的部分函数
#include <iostream>
#include <cmath>
#include "address_book.h"

using std::cout;
using std::endl;
using std::sqrt;
using std::stoi;

//Public methods

address_book::address_book(int cpt)
{
	capacity = cpt;
	record_body = new personnel[capacity];
	tot_record = 0;
	load_factor = 1e-9;
	hash_prime = find_prime(capacity);
}

address_book::~address_book()
{
	delete[]record_body;
}

void address_book::add_record(const personnel& person)
{
	if (load_factor >= load_factor_line)
		rehashing();
	int insertion_index = find_insertion_place(person.tel_num, record_body);
	if (insertion_index < 0)
	{
		std::cerr << "Position search failed. Insertion terminated.\n";
	}
	else
	{
		cout << "Insertion successful.\n";
		record_body[insertion_index] = person;
		record_body[insertion_index].is_deleted = false;
		tot_record++;
		load_factor = double(tot_record) / capacity;
	}
}

void address_book::store_info(ofstream& os) const
{
	os << "Total Record:\n";
	os << "Name\tTel-Number\tAddress\n";
	for (int i = 0; i < capacity; i++)
	{
		if (record_body[i].is_deleted == false)
		{
			os << record_body[i] << std::endl;
		}		
	}
}

personnel* const address_book::search_telephone(const string& tel_num)
{
	int result_index = search_record(tel_num);
	if (result_index < 0)
	{
		return nullptr;
	}
	else
	{
		return &record_body[result_index];
	}
}

void address_book::show_record() const
{
	if (tot_record == 0)
	{
		std::cout << "Address book is currently empty.\n";
		return;
	}
	for (int i = 0; i < capacity; i++)
	{
		if (record_body[i].is_deleted == false)
		{
			cout << record_body[i] << std::endl;
		}
	}
}

bool address_book::delete_record(const string& tel_num)
{
	int result_index = search_record(tel_num);
	if (result_index < 0)
	{
		return false;
	}
	else
	{
		record_body[result_index].is_deleted = true;
		tot_record--;
		load_factor = double(tot_record) / capacity;
		return true;
	}
}

//Private methods

int address_book::find_insertion_place(const string& tel_num, const personnel* from_where) const
{
	int src_key = stoi(tel_num.substr(tel_num.size() - 4, 4));
	int mod_val = src_key % hash_prime;
	int adjust_val = 0;
	int final_val = 0;

	//《算法笔记》第109面的内容说明了这种算法的正确性
	do
	{
		final_val = (mod_val + adjust_val * adjust_val) % capacity;
		adjust_val++;
	} while (adjust_val < capacity && from_where[final_val].is_deleted == false);

	if (from_where[final_val].is_deleted == true)
	{
		return final_val;
	}
	else
	{
		return -1;
	}
}

void address_book::rehashing()
{
	int original_capacity = capacity;
	capacity = capacity * enlarge_times;

	hash_prime = find_prime(capacity);
	load_factor = double(tot_record) / capacity;

	personnel* new_record_body = new personnel[capacity];
	
	for (int i = 0; i < original_capacity; i++)
	{
		if (record_body[i].is_deleted == false)
		{
			new_record_body[find_insertion_place(record_body[i].tel_num, new_record_body)] = record_body[i];
		}
	}
	delete[]record_body;
	record_body = new_record_body;
}

bool address_book::judge_prime(int num)
{
	if (num <= 1)
		return false;
	else if (num == 2)
		return true;
	else
	{
		int judge_factor;
		for (judge_factor = 3; judge_factor <= num / 2; judge_factor += 2)
		{
			if (num % judge_factor == 0)
				return false;
		}
		return true;
	}
}

int address_book::find_prime(int upper)
{
	for (int i = upper; i >= 2; i--)
	{
		if (judge_prime(i))
			return i;
	}
	return -1;
}

void address_book::show_status() const
{
	cout << "Capaciity: " << capacity << endl;
	cout << "Total Record: " << tot_record << endl;
	cout << "Hash Prime: " << hash_prime << endl;
	cout << "Load factor: " << load_factor << endl;
}

int address_book::search_record(const string& tel_num)
{
	int src_key = stoi(tel_num.substr(tel_num.size() - 4, 4));
	int mod_val = src_key % hash_prime;
	int adjust_val = 0;
	int final_val = 0;
	do
	{
		final_val = (mod_val + adjust_val * adjust_val) % capacity;
		adjust_val++;
	} while (adjust_val < capacity && record_body[final_val].is_deleted == false && 
		record_body[final_val].tel_num != tel_num);

	if (record_body[final_val].tel_num == tel_num)
	{
		return final_val;
	}
	else
	{
		return -1;
	}
}