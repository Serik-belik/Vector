#include <iostream>

class Vector
{
	int* data{ nullptr };
	static unsigned refactor;
	unsigned capacity{ 3 };
	unsigned size{ 0 };
	int* next_free{ nullptr };

	void resize()
	{
		capacity *= refactor;
		int* temp = new int[capacity];
		
		for (unsigned k{ 0 }; size > k; ++k)
			temp[k] = data[k];
		next_free = &temp[size];

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

		for (unsigned k{ 0 }; other.size < k; ++k)
			data[k] = other.data[k];

		next_free = &data[size];
	} 

	void operator=(Vector& other)
	{
		capacity = other.capacity;
		size = other.size;

		delete[] data;
		data = new int[capacity];

		for (unsigned k{ 0 }; other.size > k; ++k)
			data[k] = other.data[k];

		next_free = &data[size];
	}

	void push_back(const int& item)
	{
		if (size >= capacity)
			resize();

		*next_free = item;
		++next_free;
		++size;
	}

	int& operator[](unsigned index)
	{
		if (index >= size)
			return data[size - 1];
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
	Iterator end() { return Iterator(data + size); }

	~Vector()
	{
		delete[] data;
	}
};

std::ostream& operator<<(std::ostream& os, const Vector& vec)
{
	os << "[";
	for (int* itr = vec.data; itr != &vec.data[vec.size - 1]; ++itr)
		os << *itr << ((itr + 1 == &vec.data[vec.size - 1]) ? "" : ", ");
	os << "]" << std::endl;
	return os;
};

unsigned Vector::refactor = 2;

int main()
{
	Vector v1;
	v1.push_back(2);
	v1.push_back(4);
	v1.push_back(4);
	v1.push_back(4);
	v1.push_back(4);


	Vector v2;
	v2 = v1;
	v2.push_back(4);
	v2.push_back(4);

	for (auto it = v2.begin(); it != v2.end(); ++it)
		std::cout << *it << " ";

	return 0;
}