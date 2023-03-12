#include <iostream>
#include <string>

using namespace std;

class A {
public:
	int a;
	string str;
	A() {
		a = rand();
		str = to_string(a);
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

	void increase_capacity() {
		T* new_arr = new T[capacity * 2];

		for (int i = 0; i < size; i++) {
			new_arr[i] = arr[i];
		}

		delete[] arr;
		capacity *= 2;
		arr = new_arr;
	}

	void reduce_capacity() {
		capacity = size;
		T* new_arr = new T[capacity];

		for (int i = 0; i < size; i++) {
			new_arr[i] = arr[i];
			delete[] arr;
			arr = new_arr;
		}	
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
		if (size == capacity) increase_capacity();
		arr[size] = val;
		size++;
	}

	void pop_back() {
		arr[size - 1] = 0;
		size--;
		if (size == (capacity / 2)) reduce_capacity();
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
		if (size == (capacity / 2)) reduce_capacity();
	}

	void push(int index, T val)
	{
		if (size >= capacity) increase_capacity();

		if (index == capacity) push_back(val);
		else {
			for (int i = size - 1; i >= index; i--) {
				arr[i + 1] = arr[i];
			}

			arr[index] = val;
			++size;
		}
		
	}

	 void set(int index, T val) {
		 if (index <= size && index >= 0) 
			 arr[index] = val;	 
	}

	T get(int index) const {
		if (index <= size && index >= 0) 
			return arr[index];
	}

	void print() {
		for (int i = 1; i < size; ++i) {
			cout << *arr[i];
			cout << '\n';
		}
	}
};

int main() {
	Container<A*> arr;

	for (int i = 0; i < 150; ++i) {
		arr.push_back(new A());
	}

	for (int i = 1; i < arr.get_size(); ++i) {
		cout << *arr.get(i);
		cout << '\n';
	}

	arr.push_back(new A());
	cout << "\n\n";
	arr.print();

	arr.remove(1);

	cout << "\n\n";
	arr.print();

	arr.pop_back();

	cout << "\n\n";
	arr.print();

	arr.get(4);

	cout << "\n\n";
	arr.print();

	arr.set(4, new A());

	cout << "\n\n";
	arr.print();

	arr.search(new A());

	cout << "\n\n";
	arr.print();

	arr.push(2, new A());

	cout << "\n\n";
	arr.print();
}