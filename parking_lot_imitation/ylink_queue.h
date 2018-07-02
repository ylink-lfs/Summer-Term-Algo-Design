#pragma once
//Linked Queue
#include "ylink_forward_list.h"

namespace ylink
{
	template <typename T>
	class y_queue
	{
	private:
		int tot_elem;
		y_forward_list<T> queue_body;
	public:
		y_queue() : queue_body() {}
		~y_queue() {}  //Drived class's destructor automatically calls base class's destructor

		y_queue(const y_queue<T>& src) = delete;
		y_queue<T>& operator=(const y_queue<T>& src) = delete;  //Forbid to execute assign operation

		T front();
		T back();
		void push(const T src);  //Push from backside
		void pop();  //Pop from head
		int size() { return tot_elem; }
		bool empty() { return queue_body.size() == 0 ? true : false; }
		int rear_index() { return tot_elem - 1; }
	};

	template <typename T>
	T y_queue<T>::front()
	{
		queue_body.reset_cur(y_forward_list<T>::HEAD);
		return queue_body.current->data;
	}

	template <typename T>
	T y_queue<T>::back()
	{
		return queue_body.rear->data;
	}

	template <typename T>
	void y_queue<T>::push(const T src)
	{
		queue_body.tail_insertion(src);
		tot_elem++;
	}

	template <typename T>
	void y_queue<T>::pop()
	{
		queue_body.head_deletion();
		tot_elem--;
	}
}