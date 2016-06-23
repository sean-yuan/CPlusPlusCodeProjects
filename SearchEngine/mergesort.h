#ifndef MERGESORT_H
#define MERGESORT_H
#include <vector>
#include <iostream>
#include <string>

using namespace std;

struct AlphaStrComp {
    bool operator()(const string& lhs, const string& rhs) {
        return lhs < rhs;
    }
};
template <typename T, typename Comparator>
class MergeSort {
public:
    void mergeSort(std::vector<T>* list, Comparator comp);
    void mergehelper(std::vector<T>& first, std::vector<T>& second, std::vector<T>* uni_, Comparator comp);
};


template <typename T, typename Comparator>
void MergeSort< T, Comparator>::mergeSort(std::vector<T>* list, Comparator comp) {
    if (list->size() < 2) {
        return;
    }
    std::vector<T> first, second;
    for (unsigned int i = 0; i < list->size() / 2; ++i) {
        first.push_back((*list)[i]);
    }
    for (unsigned int i = list->size() / 2; i < list->size(); ++i) {
        second.push_back((*list)[i]);
    }
    mergeSort(&first, comp);
    mergeSort(&second, comp);
    mergehelper(first, second, list, comp);
}

template <typename T, typename Comparator>
void MergeSort< T, Comparator>::mergehelper(std::vector<T>& first, std::vector<T>& second, std::vector<T>* uni_, Comparator comp) {
    uni_->clear();
    uni_->reserve(first.size() + second.size());
    unsigned int mo = 0, g = 0;
    while (mo < first.size() && g < second.size()) {
        if (comp(first[mo], second[g]) == 1) {
            uni_->push_back(first[mo]);
            ++mo;
        }
        else {
            uni_->push_back(second[g]);
            ++g;
        }
    }
    while (mo < first.size()) {
        uni_->push_back(first[mo]);
        ++mo;
    }
    while (g < second.size()) {
        uni_->push_back(second[g]);
        ++g;
    }
}
#endif
