#include <iostream>
#include <string>
#include <ctime>

using namespace std;

class A {
public:
	int a;
	string str;
	A() {
		a = rand();
		str = to_string(a);
	}
};
ostream& operator<<(ostream &out, const A &elem) {
	return out << elem.str;
}

template <typename T>
class Container {
private:
	T* arr;
	int capacity;
	int size;

	void increase_capacity() {
		T* new_arr = new T[capacity * 2];

		for (int i = 0; i <= size; ++i) {
			new_arr[i] = arr[i];
		}

		delete[] arr;
		capacity *= 2;
		arr = new_arr;
	}

	void reduce_capacity() {
		capacity = size;
		T* new_arr = new T[capacity];

		for (int i = 0; i <= size; ++i) {
			new_arr[i] = arr[i];
			delete[] arr;
			arr = new_arr;
		}	
	}
public: 
	Container() : capacity(1), size(0), arr(new T[capacity]) {}
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
		++size;
	}

	void pop_back() {
		arr[size - 1] = 0;
		++size;
		if (size == (capacity / 2)) reduce_capacity();
	}

	int search(T val) {
		for (int i = 1; i <= size; ++i) {
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
};

int main() {
	setlocale(LC_ALL, "rus");
	Container<A*> arr;
	clock_t start = clock();
	int n = 10000;

	for (int i = 0; i < n; ++i) {
		arr.push_back(new A());
	}

	for (int i = 0; i < n; ++i) {
		switch (rand() % 7)
		{
		case 0:
			arr.push_back(new A());
			break;
		case 1:
			if (arr.get_size()) {
				arr.remove(rand() % arr.get_size());
			}
			break;
		case 2:
			if (arr.get_size()) {
				arr.pop_back();
			}
			break;
		case 3:
			arr.get(rand() % arr.get_size());
			break;
		case 4:
			arr.set(rand() % arr.get_size(), new A());
			break;
		case 5:
			arr.search(new A());
			break;
		case 6:
			arr.push(rand() % arr.get_size(), new A());
			break;
		}
	}
	clock_t end = clock();
	double seconds = (double)(end - start) / CLOCKS_PER_SEC;

	for (int i = 0; i < arr.get_size(); ++i) {
		cout << *arr.get(i);
		cout << '\n';
	}

	cout << "\n";
	cout << "Время работы - " << seconds << "секунд";
}