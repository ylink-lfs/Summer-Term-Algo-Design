//ylink_forward_list.h
//自己定义的单向链表模板
#pragma once
#include <vector>

using std::vector;

namespace ylink
{
	//Precondition: T& operator=(const T&) and T(const T&) for datatype T is already defined
	template <typename T>
	class y_forward_list
	{
		struct node
		{
			T data;
			node* next_ptr;
			node(const T& src, node* next = nullptr) : data(src), next_ptr(next) {}
		};
	private:
		node* head;
		node* rear;
		int tot_node;
	public:
		enum switch_mode { HEAD, REAR };
		node* current;
		y_forward_list() : head(nullptr), rear(nullptr), current(nullptr), tot_node(0) {}
		y_forward_list(const T* src_ptr, const int n);
		y_forward_list(const vector<T>& src_v);

		y_forward_list(const y_forward_list<T>& src);
		y_forward_list<T>& operator=(const y_forward_list<T>& src);
		~y_forward_list();

		void head_insertion(const T& src);
		void tail_insertion(const T& src);
		void head_deletion() { random_deletion(0); }
		void tail_deletion() { random_deletion(tot_node - 1); }

		void traverse(void(*pfun)(T& src));
		void reset_cur(switch_mode switcher) { switcher == HEAD ? current = head : current = rear; }

		int size() { return tot_node; }
		void clear();
		void preface_clear() { head = rear = nullptr; tot_node = 0; }

		void merge(y_forward_list<T>& sub_list);
		y_forward_list<T> split(const int pos);

		void random_insertion(const T& src, const int pos);
		void random_deletion(const int pos);		
	};

	template <typename T>
	y_forward_list<T>::y_forward_list(const T* src_ptr, const int n)
	{
		for (int i = 0; i < n; i++)
		{
			node* pnew = new node(src_ptr[i]);
			if (i == 0)
			{
				head = rear = current = pnew;
			}
			else
			{
				rear->next_ptr = pnew;
				rear = rear->next_ptr;
			}
		}
		tot_node = n;
	}

	template <typename T>
	y_forward_list<T>::y_forward_list(const vector<T>& src_v)
	{
		for (auto it = src_v.begin(); it < src_v.end(); it++)
		{
			node* pnew = new node(*it);
			if (it == src_v.begin())
			{
				head = rear = current = pnew;
			}
			else
			{
				rear->next_ptr = pnew;
				rear = rear->next_ptr;
			}
		}
		tot_node = src_v.size();
	}

	template <typename T>
	y_forward_list<T>::~y_forward_list()
	{
		node* pre = nullptr;
		current = head;
		while (current)
		{
			pre = current;
			current = current->next_ptr;
			delete pre;
		}
	}

	//Copy a list. Guarantee that the ptr current points to the same elemnet as the source list's does
	template <typename T>
	y_forward_list<T>::y_forward_list(const y_forward_list<T>& src)
	{
		const node* copy_it = src.head;
		tot_node = 0;
		while (copy_it)
		{
			node* pnew = new node(copy_it->data);
			if (copy_it == src.head)
			{
				head = rear = current = pnew;
			}
			else
			{
				rear->next_ptr = pnew;
				rear = rear->next_ptr;
				if (copy_it == src.current)
				{
					current = rear;
				}
			}
			tot_node++;
			copy_it = copy_it->next_ptr;
		}
	}

	//Copy a list. Guarantee that the ptr current points to the same elemnet as the source list's does
	template <typename T>
	y_forward_list<T>& y_forward_list<T>::operator=(const y_forward_list<T>& src)
	{
		if (&src == this)
			return *this;
		clear();
		const node* copy_it = src.head;
		while (copy_it)
		{
			node* pnew = new node(copy_it->data);
			if (tot_node == 0)
			{
				head = rear = current = pnew;
			}
			else
			{
				rear->next_ptr = pnew;
				rear = rear->next_ptr;
				if (copy_it == src.current)
				{
					current = rear;
				}
			}
			tot_node++;
			copy_it = copy_it->next_ptr;
		}
		return *this;
	}

	//Insert an element before the head node
	template <typename T>
	void y_forward_list<T>::head_insertion(const T& src)
	{
		node* pnew = new node(src);
		if (!tot_node)
		{
			head = rear = current = pnew;
		}
		else
		{
			pnew->next_ptr = head;
			head = pnew;
		}
		tot_node++;
	}

	//Insert an element after the rear node
	template <typename T>
	void y_forward_list<T>::tail_insertion(const T& src)
	{
		node* pnew = new node(src);
		if (!tot_node)
		{
			head = rear = current = pnew;
		}
		else
		{
			rear->next_ptr = pnew;
			rear = rear->next_ptr;
		}
		tot_node++;
	}

	//Pass a function whose prototype is [void pfun(T& src)] to execute the operation
	//defined in the function to all nodes in the list
	template <typename T>
	void y_forward_list<T>::traverse(void(*pfun)(T& src))
	{
		for (reset_cur(HEAD); current; current = current->next_ptr)
		{
			pfun(current->data);
		}
	}
	
	//Reset the list to an empty list
	template <typename T>
	void y_forward_list<T>::clear()
	{
		node* pre = nullptr;
		current = head;
		while (current)
		{
			pre = current;
			current = current->next_ptr;
			delete pre;
		}
		head = rear = current = nullptr;
		tot_node = 0;
	}

	//Merge a sub list after the original list
	//After this operation, sub list is an empty list,
	//while the original list's ptr current is at head position
	template <typename T>
	void y_forward_list<T>::merge(y_forward_list<T>& sub_list)
	{
		if (rear)
		{
			rear->next_ptr = sub_list.head;
			rear = sub_list.rear;
			tot_node += sub_list.tot_node;
			sub_list.preface_clear();
		}
		else
		{			
			*this = sub_list;
			sub_list.preface_clear();
		}

	}

	//Split the part after pos position from the original list (pos count from 0)
	//After operation, the ptr current of original list is at rear position
	template <typename T>
	y_forward_list<T> y_forward_list<T>::split(const int pos)
	{		
		y_forward_list<T> res_list;
		if (pos < 0)
		{
			return *this;
		}
		else if (pos < tot_node - 1 && pos > 0)
		{
			reset_cur(HEAD);
			for (int i = 0; i < pos; i++)
			{
				current = current->next_ptr;
			}
			res_list.head = current->next_ptr;
			res_list.rear = rear;
			res_list.tot_node = tot_node - pos - 1;
			current->next_ptr = nullptr;
			rear = current;
			tot_node -= res_list.tot_node;
		}
		return res_list;
	}

	//Insert an element after the node specified by pos position
	//pos is calcuated from 0
	//After insertion, ptr current is before the new node
	template <typename T>
	void y_forward_list<T>::random_insertion(const T& src, const int pos)
	{
		if (pos >= 0 && pos < tot_node - 1)
		{
			current = head;
			for (int i = 0; i < pos; i++)
			{
				current = current->next_ptr;
			}
			node* pnew = new node(src);
			pnew->next_ptr = current->next_ptr;
			current->next_ptr = pnew;
			tot_node++;
		}
		else if (pos == tot_node - 1)
		{
			tail_insertion(src);
		}
		return;
	}

	//Delete a node in the pos position
	//pos calculates from 0
	//If head is deleted, then ptr current points to the new head.
	//Otherwise, ptr current points to the node before the deleted one
	template <typename T>
	void y_forward_list<T>::random_deletion(const int pos)
	{
		if (tot_node == 0)
			return;
		else if (pos == 0)
		{
			node* temp = head;
			head = current = head->next_ptr;
			delete temp;
			tot_node--;
		}
		else if (pos <= tot_node - 1)
		{
			reset_cur(HEAD);
			for (int i = 0; i < pos - 1; i++)
			{
				current = current->next_ptr;
			}
			node* temp = current->next_ptr;
			current->next_ptr = temp->next_ptr;
			delete temp;
			tot_node--;
		}
		return;
	}
}