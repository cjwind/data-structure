#include <vector>

class MaxHeap {
public:
	MaxHeap();

	void push(unsigned int value);
	int pop();

	void dump();

private:
	void swap(int i, int j);

private:
	std::vector<unsigned int> heap;
};
