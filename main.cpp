#include <iostream>

template <typename T>
class Vector
{
	T* data{ nullptr };
	static unsigned refactor;
	unsigned capacity{ 3 };
	unsigned _size{ 0 };
	T* next_free{ nullptr };

	void resize()
	{
		capacity *= refactor;
		T* temp = new T[capacity];
		
		for (unsigned k{ 0 }; _size > k; ++k)
			temp[k] = data[k];
		next_free = &temp[_size];

		delete[] data;
		data = temp;
	}

	friend std::ostream& operator<<(std::ostream& os, const Vector& order);

public:
	Vector(unsigned newSize = 3): capacity(newSize)
	{
		while (newSize > capacity)
			capacity *= refactor;

		data = new T[capacity];
		next_free = data;
	}

	Vector(Vector& other): capacity(other.capacity)
	{
		data = new T[capacity];

		for (unsigned k{ 0 }; other._size < k; ++k)
			data[k] = other.data[k];

		next_free = &data[_size];
	} 

	void operator=(Vector& other)
	{
		capacity = other.capacity;
		_size = other._size;

		delete[] data;
		data = new T[capacity];

		for (unsigned k{ 0 }; other._size > k; ++k)
			data[k] = other.data[k];

		next_free = &data[_size];
	}

	void push_back(const T& item)
	{
		if (_size >= capacity)
			resize();

		*next_free = item;
		++next_free;
		++_size;
	}

	T& operator[](unsigned index)
	{
		if (index >= _size)
			return data[_size - 1];
		else
			return data[index];
	}

	class Iterator {
		T* ptr{ nullptr };

	public:
		Iterator(T* p = nullptr) : ptr(p) {}

		Iterator& operator++() { ptr++; return *this; }
		Iterator operator++(int) { Iterator tmp = *this; ++(*this); return tmp; }
		Iterator& operator--() { ptr--; return *this; }
		Iterator operator--(int) { Iterator tmp = *this; --(*this); return tmp; }

		Iterator operator+(unsigned offset) const { return Iterator(ptr + offset); }
		Iterator operator-(unsigned offset) const { return Iterator(ptr - offset); }

		T& operator*() const { return *ptr; }
		T* operator->() const { return ptr; }

		bool operator==(const Iterator& other) const { return ptr == other.ptr; }
		bool operator!=(const Iterator& other) const { return ptr != other.ptr; }
	};

	Iterator begin() { return Iterator(data); }
	Iterator end() { return Iterator(data + _size); }

	~Vector()
	{
		delete[] data;
	}

	unsigned size()
	{
		return _size;
	}

	void sort() {
		// insertion sort
		T temp;
		unsigned j;
		for (unsigned i{ 1 }; i < 9; ++i)
		{
			j = i;
			temp = data[j];
			while (j > 0)
			{
				if (data[j - 1] > temp)
					data[j] = data[j - 1];
				else
					break;
				--j;
			}
			data[j] = temp;
		}
	}
};

std::ostream& operator<<(std::ostream& os, const Vector<int>& vec)
{
	os << "[";
	for (int* itr = vec.data; itr != &vec.data[vec._size - 1]; ++itr)
		os << *itr << ((itr + 1 == &vec.data[vec._size - 1]) ? "" : ", ");
	os << "]" << std::endl;
	return os;
};

template <typename T>
unsigned Vector<T>::refactor = 2;

int main()
{
	Vector<int> v1; 
	v1.push_back(10);
	v1.push_back(20);
	v1.push_back(30);

	Vector<double> v2; 
	v2.push_back(10.5);
	v2.push_back(20.5);
	v2.push_back(30.2);

	Vector<int> v;
	v.push_back(6);
	v.push_back(1);
	v.push_back(7);
	v.push_back(4);
	v.push_back(2);
	v.push_back(9);
	v.push_back(8);
	v.push_back(5);
	v.push_back(3);

	std::cout << v;
	v.sort();
	std::cout << v;

	return 0;
}