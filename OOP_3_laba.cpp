#include <iostream>
#include <string>

using namespace std;

class A {
public:
	int a;
	string str;
	A() {
		a = rand();
		str = "elem: " + to_string(a);
	}
	int get_a() {
		return a;
	}
	string get_str() {
		return str;
	}
};
ostream& operator<<(ostream &os, const A &obj) {
	return os << obj.str;
}

template <typename T>
class Container {
	T* arr = NULL;
	int capacity;
	int size;

	void increase_capacity(int sz) {
		if (sz <= capacity) return;
		T* new_arr = new T[sz];
		capacity = sz;

		for (int i = 0; i < sz; i++) {
			new_arr[i] = arr[i];
		}

		delete[] arr;
		arr = new_arr;
	}

	void reduce_capacity() {
		capacity = size;
		T* new_arr = new T[capacity];

		for (int i = 0; i < size; i++) {
			new_arr[i] = arr[i];
		}
		delete[] arr;
		arr = new_arr;
	}
public: 
	Container() :capacity(1), size(0) {
		arr = new T[capacity];
	}
	Container(int capacity) : capacity(this->capacity), size(0), arr(new T[capacity]) {}
	~Container() {
		delete[]arr;
	}

	int get_size() const {
		return size;
	}

	void push_back(T val) {
		if (size >= capacity) increase_capacity(2 * capacity);
		arr[size] = val;
		++size;
	}

	void pop_back() {
		arr[size - 1] = 0;
		--size;
		reduce_capacity();
	}

	int search(T val) {
		for (int i = 0; i < size; i++) {
			if (arr[i] == val) {
				return i;
			}
		}
		return -1;
	}

	void remove(int index) {
		for (int i = index; i <= size; ++i) {
			arr[i] = arr[i + 1];
		}
		arr[size - 1] = 0;
		--size;
		if (size == (capacity / 2)) {
			reduce_capacity();
		}
	}

	void insertAt(int index, T val)
	{
		if (size >= capacity) increase_capacity(2 * capacity);

		for (int i = size - 1; i >= index; i--) {
			arr[i + 1] = arr[i];
		}
		arr[index] = val;
		++size;
	}

	 T set(int i, T val) {
		if (i < 0 || i >= size) return NULL;
		arr[i] = val;
	}

	T get(int i) const {
		if (i < 0 || i >= size) return NULL;
		return arr[i];
	}
};

int main() {
	Container<A*> arr;

	for (int i = 0; i < 15; ++i) {
		arr.push_back(new A());
	}

	for (int i = 1; i < arr.get_size(); ++i) {
		cout << *arr.get(i);
		cout << '\n';
	}

	arr.push_back(new A());
	arr.remove(10);
	arr.pop_back();
	arr.get(4);
	arr.set(4, new A());
	arr.search(new A());
	arr.insertAt(2, new A());

	for (int i = 1; i < arr.get_size(); ++i) {
		cout << *arr.get(i);
		cout << '\n';
	}
}