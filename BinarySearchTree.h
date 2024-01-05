/*
	Copyright (C) 2023 Marzan Ivan
 	Binary Search Tree program header
	GNU GENERAL PUBLIC LICENSE v3.0
*/

#pragma once

#include <cstdlib>

template <class Ttype>
struct BinarySearchTree {
	Ttype* array;
	size_t size;

	BinarySearchTree() {
		array = nullptr;
		size = 0;
	}
	
	BinarySearchTree(int* array, size_t size) {
		this->size = size;
		this->array = array;
		for (int i = (size >> 1) - 1; i >= 0; i--) {
			heapify(i, this->size - 1);
		}
	}

	~BinarySearchTree() {
		
	}

	void heapify(int index, size_t size);
	
	int* sort();
};

template <class Ttype>
inline void BinarySearchTree<Ttype>::heapify(int index, size_t size) {
	int LeftNodeIndex = (index << 1) + 1;
	int RightNodeIndex = (index << 1) + 2;
	int MaxNodeIndex = index;
	if (LeftNodeIndex <= size && array[LeftNodeIndex] > array[MaxNodeIndex]) {
		MaxNodeIndex = LeftNodeIndex;
	}
	if (RightNodeIndex <= size && array[RightNodeIndex] > array[MaxNodeIndex]) {
		MaxNodeIndex = RightNodeIndex;
	}
	if (MaxNodeIndex != index) {
		auto temp = array[MaxNodeIndex];
		array[MaxNodeIndex] = array[index];
		array[index] = temp;
		heapify(MaxNodeIndex, size);
	}
}

template<class Ttype>
inline int* BinarySearchTree<Ttype>::sort() {
	for (int i = this->size - 1; i > 0;) {
		auto max = array[0];
		array[0] = array[i];
		array[i] = max;
		heapify(0, --i);
	}
	return this->array;
}

