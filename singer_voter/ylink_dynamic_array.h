#pragma once

namespace ylink
{
	template <typename T>
	class y_dynamic_array
	{
	private:
		T* arr_body;
		int tot_elem;
	public:
		y_dynamic_array() : arr_body(nullptr), tot_elem(0) {}
		y_dynamic_array(int original_size);
		y_dynamic_array(const y_dynamic_array<T>& src);
		y_dynamic_array<T>& operator=(const y_dynamic_array<T>& src);
		~y_dynamic_array() { delete[]arr_body; }
		
		void resize(int new_size);
		void push_back(const T& src);
		void pop_back();
		void erase(int pos);
		void insert(const T& src, int pos);

		T& operator[](int pos) { return arr_body[pos]; }
		const T& operator[](int pos) const { return arr_body[pos]; }
		const T& front() const { return arr_body[0]; }
		const T& back() const { return arr_body[tot_elem - 1]; }
		int size() const { return tot_elem; }
		void clear() { tot_elem = 0; delete[]arr_body; }
		bool empty() const { return tot_elem == 0; }
	};

	template <typename T>
	y_dynamic_array<T>::y_dynamic_array(int original_size)
	{
		arr_body = new T[original_size];
		tot_elem = original_size;
	}

	template <typename T>
	y_dynamic_array<T>::y_dynamic_array(const y_dynamic_array<T>& src)
	{
		arr_body = new T[src.size()];
		tot_elem = src.size();
		for (int i = 0; i < src.size(); i++)
		{
			arr_body[i] = src[i];
		}
	}

	template <typename T>
	y_dynamic_array<T>& y_dynamic_array<T>::operator=(const y_dynamic_array<T>& src)
	{
		if (this == &src)
			return *this;
		delete[]arr_body;
		arr_body = new T[src.size()];
		tot_elem = src.size();
		for (int i = 0; i < src.size(); i++)
		{
			arr_body[i] = src[i];
		}
		return *this;
	}

	template <typename T>
	void y_dynamic_array<T>::resize(int new_size)
	{
		T* new_arr_body = new T[new_size];
		for (int i = 0; i < tot_elem; i++)
		{
			new_arr_body[i] = arr_body[i];
		}
		delete[]arr_body;
		arr_body = new_arr_body;
		tot_elem = new_size;
	}

	template <typename T>
	void y_dynamic_array<T>::push_back(const T& src)
	{
		T* new_arr_body = new T[tot_elem + 1];
		for (int i = 0; i < tot_elem; i++)
		{
			new_arr_body[i] = arr_body[i];
		}
		new_arr_body[tot_elem] = src;
		delete[]arr_body;
		arr_body = new_arr_body;
		tot_elem++;
	}

	template <typename T>
	void y_dynamic_array<T>::pop_back()
	{
		T* new_arr_body = new T[tot_elem - 1];
		for (int i = 0; i < tot_elem - 1; i++)
		{
			new_arr_body[i] = arr_body[i];
		}
		delete[]arr_body;
		arr_body = new_arr_body;
		tot_elem--;
	}

	template <typename T>
	void y_dynamic_array<T>::erase(int pos)
	{
		T* new_arr_body = new T[tot_elem - 1];
		int i;
		for (i = 0; i < pos; i++)
		{
			new_arr_body[i] = arr_body[i];
		}
		for (i = pos + 1; i < tot_elem; i++)
		{
			new_arr_body[i - 1] = arr_body[i];
		}
		delete[]arr_body;
		arr_body = new_arr_body;
		tot_elem--;
	}

	template <typename T>
	void y_dynamic_array<T>::insert(const T& src, int pos)
	{
		T* new_arr_body = new T[tot_elem + 1];
		int i;
		for (i = 0; i < pos; i++)
		{
			new_arr_body[i] = arr_body[i];
		}
		new_arr_body[i] = src;
		for (i = pos; i < tot_elem; i++)
		{
			new_arr_body[i + 1] = arr_body[i];
		}
		delete[]arr_body;
		arr_body = new_arr_body;
		tot_elem++;
	}
}