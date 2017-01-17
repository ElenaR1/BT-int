#include <iostream>
#include <vector>
using namespace std;


template <typename T>
class BinaryHeap {
private:
	vector<T> arr;
	void heapify()
	{
		if (arr.size() == 1)
			return;

		for (int i = (arr.size() - 2) / 2; i >= 0; --i) {
			heapDown(i);
		}

	}
	void heapUp(int index)
	{
		while (index != 0 && arr[index] < arr[parent(index)]) {
			swap(arr[index], arr[parent(index)]);
			index = parent(index);
		}
	}
	void heapDown(int index)
	{
		int child;
		while (index < arr.size())
		{
			child = left(index);//namirame lqvoto dete
			if (child >= arr.size()) {
				break;
			}

			if (child + 1 < arr.size() && arr[child] > arr[child + 1])//proverqvame dali dqsnoto dete ako ima tkaova e po malko ot lqvoto
			{
				child = child + 1;//v sluchai che dqsnoto e po-malko vzimame nego zashtoto to ni trqbva
			}
			if (arr[index]>arr[child])//proverqvame dali roditelq e po-golqm ot deteto
			{
				swap(arr[index], arr[child]);//v sluchai che roditelq e po-golqm gi swap-vame t.k taka se pravi minheap-a
			}
			index = child;
		}
	}

	int parent(int index)
	{
		return (index - 1) / 2;
	}
	int left(int index)
	{
		return 2 * index + 1;
	}
	int right(int index)
	{
		return 2 * index + 2;
	}

	int findElem(T value)
	{
		int index = 0;
		while (index < arr.size())
		{
			if (arr[index] == value)
				return index;
			index++;
		}

		return -1;
	}
public:
	BinaryHeap() {}; // good exercise: contructor which takes iterator and turns iterable into heap

	bool isEmpty() const
	{
		return !arr.size();
	}
	T getMin() const
	{
		return arr.front();
	}
	T extractMin()
	{
	
		if (this->isEmpty()) {
			throw length_error("No elements in heap.");
		}

		T data;
		if (arr.size() == 1)
		{
			data = arr.front();
			arr.pop_back();
			return data;
		}
		
		data = arr.front();
		arr.front() = arr.back();
		arr.pop_back();
		heapify();

		return data;
	}

	int getSize() const
	{
		return arr.size();
	}

	void insertElem(T value)
	{
		if (this->isEmpty())
		{
			arr.push_back(value);
			return;
		}

		arr.push_back(value);
		heapUp(arr.size() - 1);
	}
	void deleteElem(T value)
	{
		if (this->isEmpty())
		{
			throw logic_error("No elements in heap.");
		}

		if (arr.size() == 1) {
			arr.pop_back();
		}

		int index = findElem(value);
		if (index == -1) {
			throw logic_error("Heap does not contain this element.");
		}

		arr[index] = arr.back();
		arr.pop_back();
		heapDown(index);
	}

};
int main()
{
	BinaryHeap<int> minHeap;

	minHeap.insertElem(15);
	minHeap.insertElem(23);
	minHeap.insertElem(4);
	minHeap.insertElem(5);
	minHeap.insertElem(2);
	minHeap.insertElem(0);
	minHeap.insertElem(-1);

	cout << minHeap.isEmpty() << endl; // 0

	cout << minHeap.getMin() << endl; // -1



	while (!minHeap.isEmpty()) {
		cout << minHeap.extractMin() << " ";
	} // -1 0 2 4 5 15 23
	cout << endl;

	

	return 0;
}
