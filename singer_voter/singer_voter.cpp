#include "singer_voter.h"

void singer_voter::multiple_sort()
{
	sort_display<singer_participant> tmp(singer_info);
	sort_res = tmp;
	
	sort_res.switch_show_status(false);
	cout << "***************************\n";
	cout << "Bubble sort:\n";
	sort_res.bubble_sort();
	cout << "\nThe final result is:\n";
	sort_res.show_sequence();
	sort_res.reshuffle();
	cout << "***************************\n\n";

	cout << "***************************\n";
	cout << "Heap sort:\n";
	sort_res.heap_sort();
	cout << "\nThe final result is:\n";
	sort_res.show_sequence();
	sort_res.reshuffle();
	cout << "***************************\n\n";

	cout << "***************************\n";
	cout << "Insertion sort:\n";
	sort_res.insertion_sort();
	cout << "\nThe final result is:\n";
	sort_res.show_sequence();
	sort_res.reshuffle();
	cout << "***************************\n\n";

	cout << "***************************\n";
	cout << "Merge sort:\n";
	sort_res.merge_sort();
	cout << "\nThe final result is:\n";
	sort_res.show_sequence();
	sort_res.reshuffle();
	cout << "***************************\n\n";

	cout << "***************************\n";
	cout << "Quick sort:\n";
	sort_res.quick_sort();
	cout << "\nThe final result is:\n";
	sort_res.show_sequence();
	sort_res.reshuffle();
	cout << "***************************\n\n";

	cout << "***************************\n";
	cout << "Selection sort:\n";
	sort_res.selection_sort();
	cout << "\nThe final result is:\n";
	sort_res.show_sequence();
	sort_res.reshuffle();
	cout << "***************************\n\n";

	cout << "***************************\n";
	cout << "Shell sort:\n";
	sort_res.shell_sort();
	cout << "\nThe final result is:\n";
	sort_res.show_sequence();
	cout << "***************************\n\n";
}

void singer_voter::vote_one_singer(int id)
{
	singer_info[id].current_like++;
}

void singer_voter::show_current_singer_info() const
{
	cout << "Singer info:\n";
	for (int i = 0; i < singer_info.size(); i++)
	{
		cout << singer_info[i] << endl;
	}
}