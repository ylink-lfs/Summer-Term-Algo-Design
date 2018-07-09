//address_book.h
//ÉùÃ÷ÁËaddress_bookÀà
#pragma once
#include <fstream>
#include <string>

using std::ostream;
using std::ofstream;
using std::string;

struct personnel
{
	string name;
	string tel_num;
	string address;
	bool is_deleted;

	personnel() : name("Uninitialized"), tel_num("Uninitialized"), 
		address("Uninitialized"), is_deleted(true) {}
	personnel(const string& nm, const string& tel, const string& ads) : name(nm), tel_num(tel),
		address(ads), is_deleted(false) {}
	friend ostream& operator<<(ostream& os, const personnel& person) {
		return os << person.name << '\t' << person.tel_num << '\t' << person.address;
	}
};

class address_book
{
private:
	personnel* record_body;
	int capacity;
	int tot_record;
	int hash_prime;
	double load_factor;
	const int enlarge_times = 2;
	const double load_factor_line = 0.667;

	bool judge_prime(int num);
	int find_prime(int upper);
	int find_insertion_place(const string& tel_num, const personnel* from_where) const;
	int search_record(const string& tel_num);
	void rehashing();
public:
	address_book(int cpt = 20);
	~address_book();

	address_book(const address_book&) = delete;
	address_book& operator=(const address_book&) = delete;

	void add_record(const personnel& person);
	bool delete_record(const string& tel_num);
	void store_info(ofstream& os) const;
	int record_size() const { return tot_record; }
	void show_record() const;
	personnel* const search_telephone(const string& tel_num);

	//This method is for the convenience of inspection
	void show_status() const;
};