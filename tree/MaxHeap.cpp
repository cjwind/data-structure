#include "MaxHeap.h"
#include <iostream>

using namespace std;

MaxHeap::MaxHeap() {
	heap.push_back(0);		// don't use index = 0 to store node
}

void MaxHeap::push(unsigned int value) {
	heap.push_back(value);

	int nodeIdx = heap.size() - 1;
	int parentIdx = nodeIdx / 2;

	while (parentIdx >= 1 && heap[parentIdx] < value) {
		int tmp = heap[parentIdx];
		heap[parentIdx] = heap[nodeIdx];
		heap[nodeIdx] = tmp;

		nodeIdx = parentIdx;
		parentIdx = nodeIdx / 2;
	}
}

int MaxHeap::pop() {
	if (heap.size() <= 1) {
		return -1;
	}

	unsigned int root = heap[1];
	unsigned int lastNode = heap.back();

	heap.pop_back();
	heap[1] = lastNode;

	int currIdx = 1;
	int leftChildIdx = (heap.size() > currIdx * 2) ? currIdx * 2 : 0;
	int rightChildIdx = (heap.size() > currIdx * 2 + 1) ? currIdx * 2 + 1 : 0;

	while (lastNode < heap[leftChildIdx] || lastNode < heap[rightChildIdx]) {
		if (heap[leftChildIdx] > heap[rightChildIdx] && heap[leftChildIdx] > lastNode) {
			swap(currIdx, leftChildIdx);
			currIdx = leftChildIdx;
		}
		else if (heap[rightChildIdx] > heap[leftChildIdx] && heap[rightChildIdx] > lastNode) {
			swap(currIdx, rightChildIdx);
			currIdx = rightChildIdx;
		}

		leftChildIdx = (heap.size() > currIdx * 2) ? currIdx * 2 : 0;
		rightChildIdx = (heap.size() > currIdx * 2 + 1) ? currIdx * 2 + 1 : 0;
	}

	return root;
}

void MaxHeap::swap(int i, int j) {
	int tmp = heap[i];
	heap[i] = heap[j];
	heap[j] = tmp;
}

void MaxHeap::dump() {
	for (vector<unsigned int>::iterator iter = heap.begin() + 1; iter != heap.end(); iter++) {
		cout << *iter << " ";
	}
	cout << endl;
}

int main() {
	MaxHeap maxHeap;
	int elements[] = {2, 7, 4, 10, 8, 6};
	int length = sizeof(elements) / sizeof(int);

	for (int i = 0; i < length; i++) {
		maxHeap.push(elements[i]);
	}
	maxHeap.dump();

	maxHeap.push(21);
	maxHeap.dump();
	maxHeap.push(50);
	maxHeap.dump();

	cout << "pop: " << maxHeap.pop() << endl;
	maxHeap.dump();
	cout << "pop: " << maxHeap.pop() << endl;
	maxHeap.dump();

	return 0;
}
