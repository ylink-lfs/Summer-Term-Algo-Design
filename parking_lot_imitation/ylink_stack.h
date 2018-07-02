#pragma once
//Sequential Stack

namespace ylink
{
	//Sequential stack, so add an n argument for stack size limitation
	//n stands for element numbers
	template <typename T, int n>
	class y_stack
	{
	private:
		//size stands for current elements in the stack, and capacity stands for maximum elements
		//the stack can contain
		int tot_elem;
		int capacity;
		int top_cursor;
		T stack_body[n];
	public:
		y_stack() : tot_elem(0), capacity(n), top_cursor(-1) {}

		//Prohibit meaningless operation
		y_stack(const y_stack<T, n>& src) = delete;
		y_stack<T, n>& operator=(const y_stack<T, n>& src) = delete;

		T top() { return stack_body[top_cursor]; }
		void pop() { top_cursor--; tot_elem--; }
		void push(const T src) { stack_body[++top_cursor] = src; tot_elem++; }
		int size() { return tot_elem; }
		bool empty() { return tot_elem == 0 ? true : false; }
		bool full() { return tot_elem < capacity ? false : true; }
		int front_index() { return top_cursor; }
	};
}