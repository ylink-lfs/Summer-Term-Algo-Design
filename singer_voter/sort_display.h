#pragma once
#include <algorithm>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include "ylink_dynamic_array.h"

using ylink::y_dynamic_array;
using std::swap;
using std::srand;
using std::time;
using std::rand;
using std::cout;
using std::endl;

template <typename T>
class sort_display
{
private:
	y_dynamic_array<T> src;
	bool show_mid_status;

	void merge_sort(T* sort_board, int left_bound, int right_bound);
	void merge(T* sort_board, int left_start, int left_end,
		int right_start, int right_end);

	void create_maxheap();
	void maxheap_up_adjust(int lower, int upper);
	void maxheap_down_adjust(int lower, int upper);

	void insertion_sort(int left_bound, int right_bound);

	void quick_sort(int left_bound, int right_bound);
	void create_pivot(int left_bound, int right_bound);

	void show_current_status();
public:
	sort_display() : show_mid_status(false) { srand(time(nullptr)); }
	sort_display(const y_dynamic_array<T>& data_input, bool show_or_not = false) : src(data_input), 
		show_mid_status(show_or_not) { srand(time(nullptr)); }
	sort_display(const T* data_input, int size, bool show_or_not = false) : src(data_input, size), 
		show_mid_status(show_or_not) { srand(time(nullptr)); }

	void bubble_sort();
	void merge_sort();
	void heap_sort();
	void selection_sort();
	void shell_sort();
	void insertion_sort();
	void quick_sort();

	void switch_show_status(bool show_or_not) { show_mid_status = show_or_not; }
	
	void reshuffle();
	void show_sequence();
	int size() const { return src.size(); }
	y_dynamic_array<T> get_sequence() const;
};

template <typename T>
void sort_display<T>::bubble_sort()
{
	for (int i = 0; i < src.size() - 1; i++)
	{
		for (int j = i + 1; j < src.size(); j++)
		{
			if (src[i] > src[j])
			{
				swap(src[i], src[j]);
			}
		}

		//show status of one pass
		if (show_mid_status)
			show_current_status();
	}
}

template <typename T>
void sort_display<T>::merge_sort()
{
	T* board = new T[src.size()];
	merge_sort(board, 0, src.size() - 1);
	delete[]board;
}
template <typename T>
void sort_display<T>::merge_sort(T* sort_board, int left_bound, int right_bound)
{
	if (left_bound >= right_bound)
	{
		return;
	}
	else
	{
		int division_point = left_bound + (right_bound - left_bound) / 2;
		merge_sort(sort_board, left_bound, division_point);
		merge_sort(sort_board, division_point + 1, right_bound);
		merge(sort_board, left_bound, division_point, division_point + 1, right_bound);
	}
}
template <typename T>
void sort_display<T>::merge(T* sort_board, int left_start, int left_end, int right_start, int right_end)
{
	int lower_index = left_start;
	int upper_index = right_start;
	int board_cur = left_start;
	while (lower_index <= left_end && upper_index <= right_end)
	{
		if (src[lower_index] < src[upper_index])
		{
			sort_board[board_cur++] = src[lower_index++];
		}
		else if (src[lower_index] > src[upper_index])
		{
			sort_board[board_cur++] = src[upper_index++];
		}
		else
		{
			sort_board[board_cur++] = src[lower_index++];
			sort_board[board_cur++] = src[upper_index++];
		}
	}
	while (lower_index <= left_end)
		sort_board[board_cur++] = src[lower_index++];
	while (upper_index <= right_end)
		sort_board[board_cur++] = src[upper_index++];
	for (int i = left_start; i <= right_end; i++)
	{
		src[i] = sort_board[i];
	}

	//show status of one pass
	if (show_mid_status)
		show_current_status();
}

template <typename T>
void sort_display<T>::heap_sort()
{
	int current_adjust = src.size() - 1;

	//Get a max heap first
	create_maxheap();
	while (current_adjust > 0)
	{
		//Exchange the known biggest element at head with the element at tail
		swap(src[0], src[current_adjust]);
		//One element is already in its right place
		current_adjust--;
		//Adjust heap so that in the next loop, the head element is 2nd biggest element
		maxheap_down_adjust(0, current_adjust);

		//show status of one pass
		if (show_mid_status)
			show_current_status();
	}
}
template <typename T>
void sort_display<T>::create_maxheap()
{
	for (int i = src.size() - 1; i >= 0; i--)
	{
		maxheap_down_adjust(i, src.size() - 1);
	}
}
template <typename T>
void sort_display<T>::maxheap_up_adjust(int lower, int upper)
{
	int father = upper % 2 == 0 ? (upper - 1) / 2 : upper / 2;
	while (upper >= lower && src[father] < src[upper])
	{
		swap(src[father], src[upper]);
		upper = father;
		father = upper % 2 == 0 ? (upper - 1) / 2 : upper / 2;
	}
}
template <typename T>
void sort_display<T>::maxheap_down_adjust(int lower, int upper)
{
	int cared_child = 2 * lower + 1;
	while (cared_child <= upper)
	{
		if (cared_child + 1 <= upper && src[cared_child] < src[cared_child + 1])
			cared_child++;
		if (src[lower] < src[cared_child])
		{
			swap(src[lower], src[cared_child]);
			lower = cared_child;
			cared_child = 2 * lower + 1;
		}
		else
		{
			break;
		}
	}
}

template <typename T>
void sort_display<T>::selection_sort()
{
	for (int i = 0; i < src.size() - 1; i++)
	{
		int min_index = i;
		for (int j = i + 1; j < src.size(); j++)
		{
			if (src[min_index] > src[j])
			{
				min_index = j;
			}
		}
		swap(src[min_index], src[i]);


		//show status of one pass
		if (show_mid_status)
			show_current_status();
	}
}

template <typename T>
void sort_display<T>::shell_sort()
{
	for (int step = src.size() / 2; step >= 1; step /= 2)
	{
		for (int i = 1; i < src.size(); i += step)
		{
			T tmp = src[i];
			int insertion_index;
			for (insertion_index = i - step; insertion_index >= 0 && src[insertion_index] > tmp; insertion_index -= step)
			{
				src[insertion_index + step] = src[insertion_index];
			}
			src[insertion_index + step] = tmp;

			//show status of one pass
			if (show_mid_status)
				show_current_status();
		}		
	}
}

template <typename T>
void sort_display<T>::insertion_sort()
{
	insertion_sort(0, src.size() - 1);
}
template <typename T>
void sort_display<T>::insertion_sort(int left_bound, int right_bound)
{
	for (int i = left_bound + 1; i <= right_bound; i++)
	{
		T tmp = src[i];
		int insertion_index;
		for (insertion_index = i - 1; insertion_index >= left_bound && src[insertion_index] > tmp; insertion_index--)
		{
			src[insertion_index + 1] = src[insertion_index];
		}
		src[insertion_index + 1] = tmp;

		//show status of one pass
		if (show_mid_status)
			show_current_status();
	}
}

template <typename T>
void sort_display<T>::quick_sort()
{
	quick_sort(0, src.size() - 1);
}
template <typename T>
void sort_display<T>::quick_sort(int left_bound, int right_bound)
{
	if (left_bound >= right_bound)
	{
		return;
	}
	//STL implementation use 15 as the lower element number to call actual quick sort algo
	else if (right_bound - left_bound + 1 <= 15)
	{
		insertion_sort(left_bound, right_bound);
	}
	else
	{
		create_pivot(left_bound, right_bound);
		int l = left_bound;
		int r = right_bound;
		T pivot = src[left_bound];
		while (l < r)
		{
			while (l < r && src[r] > pivot)
				r--;
			if (l < r)
				src[l++] = src[r];
			while (l < r && src[l] < pivot)
				l++;
			if (l < r)
				src[r--] = src[l];
		}
		src[l] = pivot;

		//show status of one pass
		if (show_mid_status)
			show_current_status();

		quick_sort(left_bound, l - 1);
		quick_sort(l + 1, right_bound);
	}
}
template <typename T>
void sort_display<T>::create_pivot(int left_bound, int right_bound)
{
	int mid_pos = left_bound + (right_bound - left_bound) / 2;
	if (src[left_bound] < src[mid_pos])
		swap(src[left_bound], src[mid_pos]);
	if (src[left_bound] > src[right_bound])
		swap(src[left_bound], src[right_bound]);
}

template <typename T>
void sort_display<T>::reshuffle()
{
	for (int i = 0; i < src.size() / 2; i++)
	{
		int switch_index1 = rand() % src.size();
		int switch_index2 = rand() % src.size();
		swap(src[switch_index1], src[switch_index2]);
	}
}

template <typename T>
void sort_display<T>::show_current_status()
{
	cout << "Current sequence status is:\n";
	for (int i = 0; i < src.size(); i++)
	{
		cout << src[i] << endl;
	}
	cout << endl;
}

template <typename T>
void sort_display<T>::show_sequence()
{
	for (int i = 0; i < src.size(); i++)
	{
		cout << src[i] << endl;
	}
	cout << endl;
}

template <typename T>
y_dynamic_array<T> sort_display<T>::get_sequence() const
{
	return src;
}