//use_drugstore.cpp
//主程序
#include <fstream>
#include <iostream>
#include <vector>
#include <cstdlib>
#include "drugstore.h"

using std::cin;
using std::ifstream;
using std::cout;
using std::endl;
using std::vector;

void judge_flag(int& flag, const int lower, const int upper);
bool switch_flag(drugstore& store, const int flag);
void show_menu(int& lower, int& upper);
void read_data(vector<medicine>& source_data);

int main(void)
{
	cout << "Welcome to drugstore selling analysis program.\n";
	cout << "Reading data from srcdata.txt...\n";
	
	vector<medicine> source_data;
	read_data(source_data);
	cout << "Resource acquisitioin complete.\n";
	cout << "Here is your available options:\n";
	int lower_flag, upper_flag;
	show_menu(lower_flag, upper_flag);
	cout << "Wait for input:\n";
	cout << ">>";

	drugstore opt_dstore(source_data);
	int command_flag;
	while (cin >> command_flag)
	{
		judge_flag(command_flag, lower_flag, upper_flag);
		bool exit_sentinal = switch_flag(opt_dstore, command_flag);
		if (exit_sentinal)
			break;
		else
		{
			cout << "Next command input please (Enter 7 to show menu again)\n";
			cout << "Wait for input:\n";
			cout << ">>";
		}
	}
	cout << "Program terminated. Bye!\n";
	system("pause");
	return 0;
}

void read_data(vector<medicine>& source_data)
{
	ifstream ist("srcdata.txt", std::ios_base::in);
	string ID;
	string Name;
	double UnitPrice;
	int SellingQuantity;
	double SellingVal;
	while (ist >> ID)
	{
		ist.get();
		getline(ist, Name);
		ist >> UnitPrice;
		ist >> SellingQuantity;
		ist >> SellingVal;
		source_data.push_back(medicine(ID, Name, UnitPrice, SellingQuantity, SellingVal));
	}
	ist.close();
}

void judge_flag(int& flag, const int lower, const int upper)
{
	while (flag < lower || flag > upper)
	{
		cout << "The input command number should be bigger than " << lower << " and smaller than " << upper << ".\n";
		cout << "Please retype your command.\n";
		cout << "Wait for input:\n";
		cout << ">>";
		cin >> flag;
	}
}

void show_menu(int& lower, int& upper)
{
	cout << "1: Show bubble sort for unit price\n";
	cout << "2: Show quick sort for selling quantity\n";
	cout << "3: Show heap sort for selling value\n";
	cout << "4: Show merge sort for medicine name\n";
	cout << "5: Show radix sort(LSF) for medicine ID\n";
	cout << "6: Show current result\n";
	cout << "7: Show menu again\n";
	cout << "8: Exit\n";
	lower = 1;
	upper = 8;
}

bool switch_flag(drugstore& store, const int flag)
{
	
	switch (flag)
	{
	case 1:
	{
		cout << "Bubble sort begin.\n";
		store.medicine_sort(drugstore::sort_switcher::UNIT_PRICE);
		cout << "Bubble sort complete.\n";
		return false;
	}
	break;
	case 2:
	{
		cout << "Quick sort begin.\n";
		store.medicine_sort(drugstore::sort_switcher::SELLING_QUANTITY);
		cout << "Quick sort complete.\n";
		return false;
	}
	break;
	case 3:
	{
		cout << "Heap sort begin.\n";
		store.medicine_sort(drugstore::sort_switcher::SELLING_VALUE);
		cout << "Heap sort complete.\n";
		return false;
	}
	break;
	case 4:
	{
		cout << "Merge sort begin.\n";
		store.medicine_sort(drugstore::sort_switcher::NAME);
		cout << "Merge sort complete.\n";
		return false;
	}
	break;
	case 5:
	{
		cout << "Radix sort begin.\n";
		store.medicine_sort(drugstore::sort_switcher::ID);
		cout << "Radix sort complete.\n";
		return false;
	}
	break;
	case 6:
	{
		store.show_result();
		return false;
	}
	break;
	case 7:
	{
		int dummy1, dummy2;
		show_menu(dummy1, dummy2);
		return false;
	}
	break;
	case 8:
	{
		;
	}
	break;
	}
	return true;
}
