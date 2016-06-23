#include "minheap.h"
//#include "hash.h"
#include <assert.h>
#include <queue>
#include <iostream>
#include <stdexcept>

MinHeap::MinHeap(int d) {
	numberOfChildren = d;
}

MinHeap::~MinHeap() {

}

bool MinHeap::isEmpty() {
	return queue.empty();
}

const std::string& MinHeap::peek () const {
	return queue[0].first;
}

void MinHeap::add (std::string item, int priority) {
	std::pair< std::string, int > keyValue(item, priority);
	queue.push_back(keyValue);
	int lastIndex = queue.size() - 1;
	int parent = (lastIndex-1)/numberOfChildren;
	cascadeUp(lastIndex, parent);
}

void MinHeap::cascadeUp(int childPos, int parentPos) {
	if (queue[parentPos].second > queue[childPos].second){
		std::pair<std::string, int>  temp = queue[parentPos];
		queue[parentPos] = queue [childPos];
		queue[childPos] = temp;

		int newParentPos = (parentPos-1/numberOfChildren);
		if(parentPos >= 0) {
			cascadeUp(parentPos, newParentPos);
		}
	}
	else{
		std::pair< std::string, int > key(queue[childPos].first, childPos);
		table.add(key);
		return;
	}
}

/* removes the element with smallest priority.  If
            multiple items have the smallest priority, it removes
            the string which comes first alphabetically.
            Throws an exception if the heap is empty. */
void MinHeap::remove (){
	if(queue.empty()){
		throw std::invalid_argument( "not found" );
	}
	std::pair < std:: string, int > lastItem = queue[queue.size()-1];
	queue[0] = lastItem;
	queue.pop_back();
	trickleDown(0);
    
}

void MinHeap::trickleDown(int index) {
	//2*i+1, 2*i+2 => binary
	//d*i+1 thru d*i+d => d-ary
	
	int smallestChildIndex = findSmallestChild(index);
	if(smallestChildIndex == -1) {
		//error
	}
	std::pair<std::string, int> smallestChild = queue[smallestChildIndex];
	if(smallestChild.second < queue[index].second) {
		queue[smallestChildIndex] = queue[index];
		queue[index] = smallestChild;
		trickleDown(smallestChildIndex);
	}
	std::pair<std::string, int> nodeupdate(queue[smallestChildIndex].first, smallestChildIndex);
	table.update(nodeupdate);

}

int MinHeap::findSmallestChild(int index) {
	int runningMinimum = 10000000;
	int posOfChild = -1;
	int count = 1;
	while(count < numberOfChildren) {
		unsigned int childIndex = numberOfChildren*index+count; //d*i+1
		if(childIndex > queue.size()) {
			std::pair<std::string, int> child = queue[childIndex];
			if(child.second < runningMinimum) {
				runningMinimum = child.second;
				posOfChild = childIndex;
			}
		}
		count++;
	}
	return posOfChild;
}

 /* updates the priority for the specified element.
            You may want this function to do nothing if the new 
            priority is higher than the old one.
            Throws an exception if the item is not in the heap. */
void MinHeap::update (std::string item, int priority){
	int value_pos = table.find(item);
	if (queue[value_pos].second < priority ){
		return;
	}
	queue[value_pos].second = priority;
	int parent = (value_pos-1)/numberOfChildren;
	cascadeUp(value_pos, parent);
}

void MinHeap::cascader(int childPos, int parentPos) {
	if (queue[parentPos].second > queue[childPos].second){
		std::pair<std::string, int>  temp = queue[parentPos];
		queue[parentPos] = queue [childPos];
		queue[childPos] = temp;

		int newParentPos = (parentPos-1/numberOfChildren);
		if(parentPos >= 0) {
			cascadeUp(parentPos, newParentPos);
		}
	}
	else{
		std::pair<std::string, int> nodeupdate(queue[childPos].first, childPos);
		table.update(nodeupdate);
		return;
	}
}
        