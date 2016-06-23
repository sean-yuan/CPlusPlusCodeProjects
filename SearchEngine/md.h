#ifndef MD_H
#define MD_H

#include <string>
#include "pageparser.h"
#include "myset.h"
#include <fstream>
#include <iostream>
#include <set>
#include <map>
#include <sstream>
#include <vector>
#include <iterator>
#include <cassert>
#include <QApplication>
#include <QHBoxLayout>
#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>



class MD :  public PageParser {
public:
    ~MD() { }

    /**
     * Parses a file and returns all unique words according
     *  to some parser rules and all hyperlinks based
     *  on the format the parser is designed to implement
     */
    void parse(std::string filename,
               MySet<std::string>& allWords,
               MySet<std::string>& allLinks);
};

#endif
