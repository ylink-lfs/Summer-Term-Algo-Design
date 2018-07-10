#include <iostream>
#include <cstdlib>
#include "ylink_dynamic_array.h"
#include "singer_voter.h"

using ylink::y_dynamic_array;
using std::cin;
using std::cout;
using std::endl;

void show_menu(int& lower, int& upper);
void judge_flag(int& flag, int lower, int upper);
bool switch_flag(singer_voter& src_vorer, const int flag);

int main(void)
{
	cout << "Welcome to vote for your like singers.\n";
	cout << "Please enter the expected singer number in total:\n";
	cout << "Wait for input:\n";
	cout << ">>";
	int tot_num;
	cin >> tot_num;
	cin.get();
	judge_flag(tot_num, 1, 10);

	y_dynamic_array<singer_participant> pre_data_board(tot_num);
	for (int i = 0; i < tot_num; i++)
	{
		cout << "Please enter the singer's name:\n";
		cout << "Wait for input:\n";
		cout << ">>";
		string nm;
		getline(cin, nm);
		pre_data_board[i] = singer_participant(nm, std::to_string(i + 1));
	}
	singer_voter opt_voter(pre_data_board);
	cout << "Preparation work complete.\n";
	cout << "Here are available options:\n";
	int lower_b, upper_b;
	show_menu(lower_b, upper_b);

	int command_flag;
	cout << "Wait for input:\n";
	cout << ">>";
	
	while (cin >> command_flag)
	{
		judge_flag(command_flag, lower_b, upper_b);
		bool exit_sentinal = switch_flag(opt_voter, command_flag);
		if (exit_sentinal)
			break;
		else
		{
			cout << "Next command please (Enter 4 to show menu again)\n";
			cout << "Wait for input:\n";
			cout << ">>";
		}
	}
	cout << "Program terminated. Bye!\n";
	system("pause");
	return 0;
}

void judge_flag(int& flag, int lower, int upper)
{
	while (flag < lower || flag > upper)
	{
		cout << "Input number should be less than " << lower << "or more than " << upper << ".\n";
		cout << "Try again.\n";
		cout << "Wait for input:\n";
		cout << ">>";
		cin >> flag;
	}
}

void show_menu(int& lower, int& upper)
{
	cout << "1: Vote for one singer\n";
	cout << "2: Show sort process\n";
	cout << "3: Show final result\n";
	cout << "4: Show menu again\n";
	cout << "5: Exit\n";
	lower = 1;
	upper = 5;
}

bool switch_flag(singer_voter& src_voter, const int flag)
{
	switch (flag)
	{
	case 1:
	{
		cout << "Please enter the singer you expected to vote:\n";
		int expected_id;
		cin >> expected_id;
		judge_flag(expected_id, 1, src_voter.get_current_member_num());
		src_voter.vote_one_singer(expected_id - 1);
		cout << "Vote operation successful.\n";
		return false;
	}
	break;
	case 2:
	{
		src_voter.multiple_sort();
		return false;
	}
	break;
	case 3:
	{
		y_dynamic_array<singer_participant> final_res = src_voter.get_sorted_result();
		
		cout << "The result is displayed as follow:\n";

		cout.width(15);
		cout.fill(' ');
		cout << "Name";
		cout.width(15);
		cout.fill(' ');
		cout << "ID";
		cout.width(15);
		cout.fill(' ');
		cout << "Like Num";
		cout.width(15);
		cout.fill(' ');
		cout << "Level";
		cout << endl;

		int level = 1;
		int same_member = 1;
		for (int i = final_res.size() - 1; i >= 0; i--)
		{
			cout << final_res[i];
			cout.width(15);
			cout.fill(' ');
			cout << level << endl;
			if (i > 0 && final_res[i].current_like != final_res[i - 1].current_like)
			{
				level += same_member;
				same_member = 1;
			}
			else
			{
				same_member++;
			}
		}
		return false;
	}
	break;
	case 4:
	{
		int dummy1, dummy2;
		show_menu(dummy1, dummy2);
		return false;
	}
	break;
	case 5:
	{
		return true;
	}
	break;
	}
	return true;
}
