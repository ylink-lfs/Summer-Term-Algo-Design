//drugstore.cpp
//drugstore类的实现文件
#include <algorithm>
#include "ylink_forward_list.h"
#include "drugstore.h"

using std::cout;
using std::swap;
using ylink::y_forward_list;

//Public methods

drugstore::drugstore(const medicine* src, const int tot_elem)
{
	for (int i = 0; i < tot_elem; i++)
	{
		medicine_selling_info.push_back(src[i]);
	}
}

void drugstore::medicine_sort(const enum sort_switcher sort_method)
{
	reshuffle();
	switch (sort_method)
	{
	case UNIT_PRICE:
	{
		med_bubble_sort();
	}
	break;
	case SELLING_QUANTITY:
	{
		med_quick_sort();
	}
	break;
	case SELLING_VALUE:
	{
		med_heap_sort();
	}
	break;
	case NAME:
	{
		med_merge_sort();
	}
	break;
	case ID:
	{
		med_radix_sort();
	}
	break;
	}
}

void drugstore::show_result() const
{
	cout.width(4);
	cout.fill(' ');
	cout << "ID";
	cout.width(25);
	cout.fill(' ');
	cout << "Name";
	cout.width(25);
	cout.fill(' ');
	cout << "Per Price";
	cout.width(25);
	cout.fill(' ');
	cout << "Quantity";
	cout.width(25);
	cout.fill(' ');
	cout << "Total Value";
	cout << std::endl;
	for (int i = 0; i < medicine_selling_info.size(); i++)
	{
		cout << medicine_selling_info[i] << std::endl;
	}
}

//Private methods

void drugstore::reshuffle()
{
	for (int i = 0; i < medicine_selling_info.size() / 2; i++)
	{
		int switch_index1 = rand() % medicine_selling_info.size();
		int switch_index2 = rand() % medicine_selling_info.size();
		swap(medicine_selling_info[switch_index1], medicine_selling_info[switch_index2]);
	}
}

void drugstore::med_bubble_sort()
{
	for (int i = 0; i < medicine_selling_info.size() - 1; i++)
	{
		for (int j = i + 1; j < medicine_selling_info.size(); j++)
		{
			if (medicine_selling_info[i].unit_price > medicine_selling_info[j].unit_price)
			{
				swap(medicine_selling_info[i], medicine_selling_info[j]);
			}
		}
	}
}

void drugstore::med_quick_sort()
{
	quick_sort(0, medicine_selling_info.size() - 1);
}
void drugstore::quick_sort(int left_bound, int right_bound)
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
		medicine pivot = medicine_selling_info[left_bound];
		while (l < r)
		{
			while (l < r && medicine_selling_info[r].current_selling_quantity > pivot.current_selling_quantity)
				r--;
			if (l < r)
				medicine_selling_info[l++] = medicine_selling_info[r];
			while (l < r && medicine_selling_info[l].current_selling_quantity < pivot.current_selling_quantity)
				l++;
			if (l < r)
				medicine_selling_info[r--] = medicine_selling_info[l];
		}
		medicine_selling_info[l] = pivot;


		quick_sort(left_bound, l - 1);
		quick_sort(l + 1, right_bound);
	}
}
void drugstore::create_pivot(int left_bound, int right_bound)
{
	int mid_pos = left_bound + (right_bound - left_bound) / 2;
	if (medicine_selling_info[left_bound].current_selling_quantity < medicine_selling_info[mid_pos].current_selling_quantity)
		swap(medicine_selling_info[left_bound], medicine_selling_info[mid_pos]);
	if (medicine_selling_info[left_bound].current_selling_quantity > medicine_selling_info[right_bound].current_selling_quantity)
		swap(medicine_selling_info[left_bound], medicine_selling_info[right_bound]);
}
void drugstore::insertion_sort(int left_bound, int right_bound)
{
	for (int i = left_bound + 1; i <= right_bound; i++)
	{
		medicine tmp = medicine_selling_info[i];
		int insertion_index;
		for (insertion_index = i - 1; insertion_index >= left_bound && 
			medicine_selling_info[insertion_index].current_selling_quantity > tmp.current_selling_quantity; insertion_index--)
		{
			medicine_selling_info[insertion_index + 1] = medicine_selling_info[insertion_index];
		}
		medicine_selling_info[insertion_index + 1] = tmp;
	}
}

void drugstore::med_heap_sort()
{
	int current_adjust = medicine_selling_info.size() - 1;

	//Get a max heap first
	create_maxheap();
	while (current_adjust > 0)
	{
		//Exchange the known biggest element at head with the element at tail
		swap(medicine_selling_info[0], medicine_selling_info[current_adjust]);
		//One element is already in its right place
		current_adjust--;
		//Adjust heap so that in the next loop, the head element is 2nd biggest element
		maxheap_down_adjust(0, current_adjust);
	}
}
void drugstore::create_maxheap()
{
	for (int i = medicine_selling_info.size() - 1; i >= 0; i--)
	{
		maxheap_down_adjust(i, medicine_selling_info.size() - 1);
	}
}
void drugstore::maxheap_up_adjust(int lower, int upper)
{
	int father = upper % 2 == 0 ? (upper - 1) / 2 : upper / 2;
	while (upper >= lower && 
		medicine_selling_info[father].current_selling_value < medicine_selling_info[upper].current_selling_value)
	{
		swap(medicine_selling_info[father], medicine_selling_info[upper]);
		upper = father;
		father = upper % 2 == 0 ? (upper - 1) / 2 : upper / 2;
	}
}
void drugstore::maxheap_down_adjust(int lower, int upper)
{
	int cared_child = 2 * lower + 1;
	while (cared_child <= upper)
	{
		if (cared_child + 1 <= upper &&
			medicine_selling_info[cared_child].current_selling_value < medicine_selling_info[cared_child + 1].current_selling_value)
			cared_child++;
		if (medicine_selling_info[lower].current_selling_value < medicine_selling_info[cared_child].current_selling_value)
		{
			swap(medicine_selling_info[lower], medicine_selling_info[cared_child]);
			lower = cared_child;
			cared_child = 2 * lower + 1;
		}
		else
		{
			break;
		}
	}
}


void drugstore::med_merge_sort()
{
	medicine* board = new medicine[medicine_selling_info.size()];
	merge_sort(board, 0, medicine_selling_info.size() - 1);
	delete[]board;
}
void drugstore::merge_sort(medicine* sort_board, int left_bound, int right_bound)
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
void drugstore::merge(medicine* sort_board, int left_start, int left_end, int right_start, int right_end)
{
	int lower_index = left_start;
	int upper_index = right_start;
	int board_cur = left_start;
	while (lower_index <= left_end && upper_index <= right_end)
	{
		if (medicine_selling_info[lower_index].name < medicine_selling_info[upper_index].name)
		{
			sort_board[board_cur++] = medicine_selling_info[lower_index++];
		}
		else if (medicine_selling_info[lower_index].name > medicine_selling_info[upper_index].name)
		{
			sort_board[board_cur++] = medicine_selling_info[upper_index++];
		}
		else
		{
			sort_board[board_cur++] = medicine_selling_info[lower_index++];
			sort_board[board_cur++] = medicine_selling_info[upper_index++];
		}
	}
	while (lower_index <= left_end)
		sort_board[board_cur++] = medicine_selling_info[lower_index++];
	while (upper_index <= right_end)
		sort_board[board_cur++] = medicine_selling_info[upper_index++];
	for (int i = left_start; i <= right_end; i++)
	{
		medicine_selling_info[i] = sort_board[i];
	}
}

void drugstore::med_radix_sort()
{
	vector<y_forward_list<medicine>> tot_bucket;
	tot_bucket.resize(10);
	for (auto it = medicine_selling_info.begin(); it < medicine_selling_info.end(); it++)
	{
		int target_index = stoi(it->id.substr(3, 1));
		tot_bucket[target_index].tail_insertion(*it);
	}

	y_forward_list<medicine> one_pass;
	for (int i = 0; i < tot_bucket.size(); i++)
	{
		if (tot_bucket[i].size() != 0)
		{
			one_pass.merge(tot_bucket[i]);
		}
	}

	tot_bucket.clear();
	tot_bucket.resize(10);

	for (one_pass.reset_cur(y_forward_list<medicine>::HEAD); one_pass.current; one_pass.current = one_pass.current->next_ptr)
	{
		int target_index = stoi(one_pass.current->data.id.substr(2, 1));
		tot_bucket[target_index].tail_insertion(one_pass.current->data);
	}
	y_forward_list<medicine> second_pass;
	for (int i = 0; i < tot_bucket.size(); i++)
	{
		if (tot_bucket[i].size() != 0)
		{
			second_pass.merge(tot_bucket[i]);
		}
	}

	tot_bucket.clear();
	tot_bucket.resize(10);
	for (second_pass.reset_cur(y_forward_list<medicine>::HEAD); second_pass.current; second_pass.current = second_pass.current->next_ptr)
	{
		int target_index = stoi(second_pass.current->data.id.substr(1, 1));
		tot_bucket[target_index].tail_insertion(second_pass.current->data);
	}
	y_forward_list<medicine> third_pass;
	for (int i = 0; i < tot_bucket.size(); i++)
	{
		if (tot_bucket[i].size() != 0)
		{
			third_pass.merge(tot_bucket[i]);
		}
	}

	tot_bucket.clear();
	tot_bucket.resize(26);
	for (third_pass.reset_cur(y_forward_list<medicine>::HEAD); third_pass.current; third_pass.current = third_pass.current->next_ptr)
	{
		int target_index = (third_pass.current->data.id[0]) - 'A';
		tot_bucket[target_index].tail_insertion(third_pass.current->data);
	}
	y_forward_list<medicine> final_pass;
	for (int i = 0; i < tot_bucket.size(); i++)
	{
		if (tot_bucket[i].size() != 0)
		{
			final_pass.merge(tot_bucket[i]);
		}
	}


	medicine_selling_info.clear();
	for (final_pass.reset_cur(y_forward_list<medicine>::HEAD); final_pass.current; final_pass.current = final_pass.current->next_ptr)
	{
		medicine_selling_info.push_back(final_pass.current->data);
	}
}