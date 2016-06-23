#include <iostream>
#include <cstdio>
#include <algorithm>
#include <assert.h>
#include <cstring>
#include <string>
#include <stack>
#include <queue>
#include <vector>
#include <map>
#include <sstream>
#include <fstream>
#include "minheap.h"
 
 
bool checkDub(std::string first, std::string next){
    int diff=0;
    for (unsigned int i=0; i< first.length(); i++){
        if (first[i] != next[i] && ++diff > 1){
            return false; 
        } 
    }
    return true;  
}

std::map<std::string, std::vector<std::string> > collection;
void createDoublet(std::vector<std::string> index){
    for (unsigned int i=0; i<index.size(); i++){
        for (unsigned int j=i+1; j<index.size(); j++){
            std::vector<std::string> neighbor2;
            collection.insert(std::pair<std::string, std::vector<std::string> > (index[j], neighbor2));
            std::vector<std::string> neighbor;
            collection.insert(std::pair<std::string, std::vector<std::string> > (index[i], neighbor));
        }            
    }



    for (unsigned int i=0; i<index.size(); i++){
        for (unsigned int j=i+1; j<index.size(); j++){
            if (checkDub(index[i],index[j])){
                ( *(collection.find(index[j])) ).second.push_back(index[i]);
                ( *(collection.find(index[i])) ).second.push_back(index[j]);
            } 
        }            
    }
}
 
struct Node{
    std::string word; 
    Node * Parent;
};
 
 
std::vector<std::string> shortestPath(std::string src, std::string dest){
    std::map<std::string, std::string> ParentOf;
    std::queue<std::string> ToVisit;
    ToVisit.push(src);
 
    ParentOf[src] = "";
    bool found=false;
    while(!ToVisit.empty()){
        std::string v = ToVisit.front();
        ToVisit.pop();
        std::vector<std::string> curr = collection.find(v)->second;
        for (unsigned int i=0; i< curr.size(); i++){
            if (ParentOf.find(curr[i]) == ParentOf.end()){
                ToVisit.push(curr[i]);
                ParentOf[curr[i]] = v;
                if (curr[i] == dest){
                    found = true;
                    break;
                }
            }
        }
        if (found) break;
    }
 
    std::vector<std::string> result;
 
    if (!found){
        result.push_back("No solution.");
        return result;
    }
 
    std::string next = dest;
    do
    {
        result.push_back(next);
        next = ParentOf[next];
    }while(result.back() != src);
 
 
    return result;
}
int main(int argc, char* argv[]){
    if(argc < 4) {
        std::cout << "Missing one of the following:" << std::endl;
        std::cout << "./doublet [word1] [word2] [dictionary]" << std::endl;
        return 0;
    }   
    bool CmptedAdjMat[50] = {false};
    std::vector<std::string> words;
    std::ifstream file (argv[3]);
    if ( !file.is_open() ) {
        std::cout<<"Could not open file\n";
        throw std::exception();
    }
    std::string line;
    int num_words;
    file >> num_words;
    MinHeap heap(num_words);
    int g = 1;
    while ( getline (file,line) ) {
        std::string newStr;
        for(unsigned int i = 0 ; i < line.length(); i++) {
            if(line[i] != ' ') {
                newStr += line[i];
            }
        }
        std::transform(newStr.begin(), newStr.end(), newStr.begin(), ::tolower);
        //const char * c = newStr.c_str();
        if(g == 1){
            newStr = "g" + newStr;
        }
        heap.add(newStr, g);
        //std::cout << newStr << g << std::endl;
        words.push_back(newStr) ;
        g++;
    }
    assert(!words.empty());
    words.erase(words.begin());

    std::string start = argv[1];
    std::string end = argv[2];
    if (!CmptedAdjMat[start.length()]){
        CmptedAdjMat[start.length()] = true;
        createDoublet(words);
    }
    std::vector<std::string> results = shortestPath(start,end);
    for (int i=results.size()-1; i>=0; i--){
        std::cout << results[i] << " ";
    }
    std::cout << std::endl;
 
 
    return 0;
}