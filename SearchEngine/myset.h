#ifndef MYSET_H
#define MYSET_H

#include <iterator>
#include <iostream>
#include <set>


template <typename T>
class MySet : public std::set<T>{
public:
    MySet();
    MySet<T> set_intersection(const MySet<T>& other);
    MySet<T> set_union(const MySet<T>& other);
};

template <typename T>
MySet<T>::MySet() {

}

template <typename T>
MySet<T> MySet<T>::set_intersection(const MySet<T>& other) {
    MySet<T> newset;
    MySet<T> rhs = other;
    MySet<T> lhs = *this;

    typename std::set<T>::iterator it;
    for (it=rhs.begin(); it!=rhs.end(); ++it) {
        unsigned int size_old = lhs.size();
        lhs.insert(*it);
        if(lhs.size() == size_old) {
            newset.insert(*it);
        }
    }

    return newset;


}

template <typename T>
MySet<T> MySet<T>::set_union(const MySet<T>& other) {


    MySet<T> newset;

    typename std::set<T>::iterator it;
    for (it=other.begin(); it!=other.end(); ++it) {
        newset.insert(*it);
    }
    typename std::set<T>::iterator mo;
    for (mo=this->begin(); mo!=this->end(); ++mo) {
        newset.insert(*mo);
    }

    return newset;


}


#endif

