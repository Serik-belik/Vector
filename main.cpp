#include <iostream>

class Vector
{
	int* data{ nullptr };
	static unsigned refactor;
	unsigned capacity{ 3 };
	unsigned _size{ 0 };
	int* next_free{ nullptr };

	void resize()
	{
		capacity *= refactor;
		int* temp = new int[capacity];
		
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

		data = new int[capacity];
		next_free = data;
	}

	Vector(Vector& other): capacity(other.capacity)
	{
		data = new int[capacity];

		for (unsigned k{ 0 }; other._size < k; ++k)
			data[k] = other.data[k];

		next_free = &data[_size];
	} 

	void operator=(Vector& other)
	{
		capacity = other.capacity;
		_size = other._size;

		delete[] data;
		data = new int[capacity];

		for (unsigned k{ 0 }; other._size > k; ++k)
			data[k] = other.data[k];

		next_free = &data[_size];
	}

	void push_back(const int& item)
	{
		if (_size >= capacity)
			resize();

		*next_free = item;
		++next_free;
		++_size;
	}

	int& operator[](unsigned index)
	{
		if (index >= _size)
			return data[_size - 1];
		else
			return data[index];
	}

	class Iterator {
		int* ptr{ nullptr };

	public:
		Iterator(int* p = nullptr) : ptr(p) {}

		Iterator& operator++() { ptr++; return *this; }
		Iterator operator++(int) { Iterator tmp = *this; ++(*this); return tmp; }
		Iterator& operator--() { ptr--; return *this; }
		Iterator operator--(int) { Iterator tmp = *this; --(*this); return tmp; }

		Iterator operator+(unsigned offset) const { return Iterator(ptr + offset); }
		Iterator operator-(unsigned offset) const { return Iterator(ptr - offset); }

		int& operator*() const { return *ptr; }
		int* operator->() const { return ptr; }

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
		int temp;
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

std::ostream& operator<<(std::ostream& os, const Vector& vec)
{
	os << "[";
	for (int* itr = vec.data; itr != &vec.data[vec._size - 1]; ++itr)
		os << *itr << ((itr + 1 == &vec.data[vec._size - 1]) ? "" : ", ");
	os << "]" << std::endl;
	return os;
};

unsigned Vector::refactor = 2;

int main()
{
	Vector v1;
	v1.push_back(6);
	v1.push_back(1);
	v1.push_back(7);
	v1.push_back(4);
	v1.push_back(2);
	v1.push_back(9);
	v1.push_back(8);
	v1.push_back(5);
	v1.push_back(3);

	std::cout << v1;
	v1.sort();
	std::cout << v1;

	return 0;
}