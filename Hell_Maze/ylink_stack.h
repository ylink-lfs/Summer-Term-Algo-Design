#pragma once
#include "ylink_forward_list.h"

namespace ylink
{
	template <typename T>
	class y_stack
	{
	private:
		int tot_elem;
		y_forward_list<T> stack_body;
	public:
		y_stack() : stack_body() {}
		~y_stack() {}  //Drived class's destructor automatically calls base class's destructor

		y_stack(const y_stack<T>& src) = delete;
		y_stack<T>& operator=(const y_stack<T>& src) = delete;  //Forbid to execute assign operation

		T top();
		void push(const T src);  //Push from backside
		void pop();  //Pop from head
		int size() { return tot_elem; }
		bool empty() { return stack_body.size() == 0 ? true : false; }
		int rear_index() { return tot_elem - 1; }
	};

	template <typename T>
	T y_stack<T>::top()
	{
		stack_body.reset_cur(y_forward_list<T>::HEAD);
		return stack_body.current->data;
	}

	template <typename T>
	void y_stack<T>::push(const T src)
	{
		stack_body.head_insertion(src);
		tot_elem++;
	}

	template <typename T>
	void y_stack<T>::pop()
	{
		stack_body.head_deletion();
		tot_elem--;
	}
}