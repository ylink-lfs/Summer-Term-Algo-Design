//use_address_book.cpp
//主程序
#include <iostream>
#include <cstdlib>
#include <cctype>
#include "address_book.h"

using namespace std;

void show_menu(int& lower_flag, int& upperr_flag);
void judge_flag(int& flag, const int lower_flag, const int upper_flag);
bool switch_flag(address_book& book, const int flag);
void judge_tel(string& str_tel);

int main(void)
{
	address_book opt_book;
	cout << "Welcome to use Animous staffs' address book.\n";
	cout << "Here are available operations.\n";

	int command_flag, upper_flag, lower_flag;
	show_menu(lower_flag, upper_flag);
	cout << "Wait for input:\n";
	cout << ">>";
	while (cin >> command_flag)
	{
		cin.get();
		judge_flag(command_flag, lower_flag, upper_flag);
		bool exit_sentinal = switch_flag(opt_book, command_flag);
		if (exit_sentinal)
			break;
		else
		{
			//Info for displaying towards teacher
			cout << endl;
			cout << "*********\n";
			opt_book.show_status();
			cout << "*********\n";
			cout << endl;

			cout << "Enter 6 to show menu again.\n";
			cout << "Wait for next input:\n";
			cout << ">>";
		}	
	}
	cout << "Program terminated. Bye!\n";
	system("pause");
	return 0;
}

void show_menu(int& lower_flag, int& upperr_flag)
{
	cout << "1: Show current record\n";
	cout << "2: Add one stuff record\n";
	cout << "3: Find and show record according to telephone\n";
	cout << "4: Store record in one file\n";
	cout << "5: Find and delete record according to telephone\n";
	cout << "6: Show the menu again\n";
	cout << "7: Exit\n";
	lower_flag = 1;
	upperr_flag = 7;
}

void judge_flag(int& flag, const int lower_flag, const int upper_flag)
{
	while (flag < lower_flag || flag > upper_flag)
	{
		cout << "Command digit should be bigger than " << lower_flag << " and smaller than " << upper_flag << ".\n";
		cout << "Please retype the command.\n";
		cout << "Wait for input:\n";
		cout << ">>";
		cin >> flag;
	}
}

bool switch_flag(address_book& book, const int flag)
{
	switch (flag)
	{
		case 1:
		{
			book.show_record();
			return false;
		}
		break;
		case 2:
		{
			cout << "Please enter the stuff's name in one line.\n";
			cout << "Wait for input:\n";
			cout << ">>";
			string nm;
			getline(cin, nm);

			cout << "Please enter the stuff's telephone number.\n";
			cout << "Wait for input:\n";
			cout << ">>";
			string tel;
			cin >> tel;
			cin.get();
			judge_tel(tel);

			cout << "Please enter the stuff's address.\n";
			cout << "Wait for input:\n";
			cout << ">>";
			string adr;
			getline(cin, adr);

			book.add_record(personnel(nm, tel, adr));
			return false;
		}
		break;
		case 3:
		{
			cout << "Please enter the target stuff's telephone number.\n";
			cout << "Wait for input:\n";
			cout << ">>";
			string tel;
			cin >> tel;
			judge_tel(tel);

			personnel* const tar_person = book.search_telephone(tel);
			if (tar_person)
			{
				cout << "Target person's info:\n";
				cout << "Name\tTel-Number\tAddress\n";
				cout << *tar_person << endl;
			}
			else
			{
				cout << "Record does not exist.\n";
			}
			return false;
		}
		break;
		case 4:
		{
			ofstream ost("Record.txt");
			book.store_info(ost);
			cout << "Store complete.\n";
			return false;
		}
		break;
		case 5:
		{
			cout << "Please enter the target stuff's telephone number.\n";
			cout << "Wait for input:\n";
			cout << ">>";
			string tel;
			cin >> tel;
			judge_tel(tel);

			bool delete_successful = book.delete_record(tel);
			if (delete_successful)
			{
				cout << "Successful deleted.\n";
			}
			else
			{
				cout << "Record does not exist.\n";
			}
			return false;
		}
		break;
		case 6:
		{
			int dummy1, dummy2;
			show_menu(dummy1, dummy2);
			return false;
		}
		break;
		case 7:
		{
			;
		}
		break;
	}
	return true;
}

void judge_tel(string& str_tel)
{
	bool alpha_sentinal = false;
	for (int i = 0; i < str_tel.size(); i++)
	{
		if (isalpha(str_tel[i]))
		{
			alpha_sentinal = true;
			break;
		}
	}
	while (alpha_sentinal || str_tel.size() < 11)
	{
		cout << "Invalid telephone input. Please use xxxxxxxxxxx or xxx-xxxx-xxxx format.\n";
		cout << "Wait for input:\n";
		cout << ">>";
		cin >> str_tel;
		cin.get();
		for (int i = 0; i < str_tel.size(); i++)
		{
			if (isalpha(str_tel[i]))
			{
				alpha_sentinal = true;
				break;
			}
		}
	}
}
