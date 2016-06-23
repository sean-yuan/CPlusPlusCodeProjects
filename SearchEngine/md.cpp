#include "md.h"
#include "pageparser.h"
#include "myset.h"
#include <fstream>
#include <iostream>
#include <set>
#include <map>
#include <sstream>
#include <vector>
#include <string>
#include <iterator>
#include <cassert>

PageParser::~PageParser() {

}


void MD::parse(std::string filename, MySet<std::string>& allWords, MySet<std::string>& allLinks) {
    std::ifstream file ( filename.c_str() );
    std::string line;
    std::vector <std::string> storage;

//import lines
    while ( getline (file,line) ) {
        std::string m = line;
        int i = 0;
        //char c;
        while (m[i]) {
            m[i] = tolower(m[i]);
            i++;
        }

        storage.push_back(m);
    }
    file.close();
//main parser
    for (unsigned int i=0; i < storage.size(); i++) {
        std::string liner = storage[i];
        size_t start_ = 0;
        for (size_t g = 0; g < liner.length(); g++) {
            if (isalpha(liner[g])) {
                ;
            }
            else if (liner[g-1] == ']' && liner[g] == '(') {
                int m = g;
                while (liner[m]!= ')') {
                    m++;
                }
                //std::cout << "links" << liner.substr(g+1, m-g-1) << std::endl;
                allLinks.insert( liner.substr(g+1, m-g-1) );
                start_ = m;
                g= m-1;
            }
            else {
                int word_length = g - start_;
                if(word_length > 0) {
                    //std::cout << liner.substr(start_, word_length) << std::endl; // show the word
                    allWords.insert( liner.substr(start_, word_length) );
                }
                start_ = g + 1;
            }
        }
    }

}