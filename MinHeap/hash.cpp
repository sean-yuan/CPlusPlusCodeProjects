#include "hash.h"
#include <algorithm>
#include <math.h>
#include <iostream>
#include <list>
#include <set>
#include <map>
#include <sstream>
#include <vector>
#include <string>
#include <iterator>
#include <cassert>
#include <stdexcept>


HashTable::HashTable() {
    hashArraySize = 31;
    occupancy = 0;
    hashArray = new std::list< std::pair<std::string, int> >*[hashArraySize];

    for(unsigned int i = 0; i < hashArraySize; i++) {
        hashArray[i] = new std::list< std::pair<std::string, int> >;
    }
    //std::cout << hashArray[28]->empty() << std::endl;
}

HashTable::~HashTable() {
    //TO DO
}

bool HashTable::needsResize() {
    if(occupancy/hashArraySize >= 1){
        return true;
    }
    else{
        return false;
    }
}

long long HashTable::hashFunction(std::string str) {
    long long total = 0;
    for (unsigned int i = 0; i < str.length(); i ++){
        total += (pow(29, str.length()-i-1) * (str[i]-65));
    }
    return total % hashArraySize;
}

void HashTable::add (std::pair<std::string, int> new_item) {
    //generate the index via hashFunction and put it in at that index
    long long index = hashFunction(new_item.first);
    std::list< std::pair<std::string, int> >* listAtIndex = hashArray[index];
    //std::cout << "Didn't segfault at access list" << index << std::endl;
    if(listAtIndex->empty()) {
        //std::cout << "In empty";
        occupancy++;
        if(needsResize()) {
            resize();
        }
        index = hashFunction(new_item.first);
    }
    //cout << index << endl;
    hashArray[index]->push_back(new_item);
}

void HashTable::resize() {
    int tempSize = hashArraySize;
    hashArraySize = 2*hashArraySize+1;
    std::list< std::pair<std::string, int> >** temp = new std::list< std::pair<std::string, int> >*[hashArraySize];
    for(unsigned int i = 0; i < hashArraySize; i++) {
        temp[i] = new std::list< std::pair<std::string, int> >;
    }

    for(int i = 0; i < tempSize; i++) {
        std::list< std::pair<std::string, int> >* listAtIndex = hashArray[i];
        for (std::list< std::pair<std::string, int> >::iterator it = listAtIndex->begin(); it != listAtIndex->end(); ++it){
            temp[i] ->push_back( *it );
        }
    }

    delete hashArray; //delete everything in hashArray too
    hashArray = temp;
}

 const int& HashTable::find(std::string key){
    //generate index value for passed in string
    //get list in hashtable at that index
    //iterate through list and look for the matching key in pair
    //return that value in pair
    //throw exception if not found
    long long index = hashFunction(key);
    std::list< std::pair<std::string, int> >* listAtIndex = hashArray[index];
    for (std::list< std::pair<std::string, int> >::iterator it = listAtIndex->begin(); it != listAtIndex->end(); ++it){
        if ((*it).first == key){
            return (*it).second;
        }
    }
   throw std::invalid_argument( "not found" );
 }

void HashTable::remove (std::string key) {
    //get index for key
    //iterate through list at index
    //if value is found in list, remove it
    //else through exception
    long long index = hashFunction(key);
    bool foundInList = false;
    std::list< std::pair<std::string, int> >* listAtIndex = hashArray[index];
    for (std::list< std::pair<std::string, int> >::iterator it = listAtIndex->begin(); it != listAtIndex->end(); ++it){
        if ((*it).first == key){
            listAtIndex->erase(it);
            foundInList = true;
        }
    }
    if(!foundInList) {
        throw std::invalid_argument( "not found" );
    }
     if(listAtIndex->empty()) {
        occupancy--;
    }
}

void HashTable::update(std::pair<std::string, int> new_value) {
    long long index = hashFunction(new_value.first);
    std::list< std::pair<std::string, int> >* listAtIndex = hashArray[index];
    for (std::list< std::pair<std::string, int> >::iterator it = listAtIndex->begin(); it != listAtIndex->end(); ++it){
        if((*it).first == new_value.first){
            *it = new_value; //look up later
        }
    }
}