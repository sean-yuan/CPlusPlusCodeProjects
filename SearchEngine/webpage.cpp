#include "webpage.h"
#include <fstream>
#include <iostream>
#include <set>
#include <map>
#include <sstream>
#include <vector>
#include <string>
#include <iterator>
#include <cassert>


WebPage::WebPage() {
    std::string name_ = " ";

}

WebPage::WebPage(std::string filename) {
    name_ = filename;

}

WebPage::~WebPage() {

}

/**
 * Sets the filename/URL of this webpage
 */
void WebPage::filename(std::string fname) {

    name_ = fname;

}

/**
 * Returns the filename/URL of this webpage
 */
std::string WebPage::filename() const {
    //std::cout << "man" << std::endl;
    return name_;

}

void WebPage::add_rank(double r){
    rank = r;

}

/**
 * Updates the set containing all unique words in the text
 *  with the contents of the input parameter words
 */
void WebPage::all_words(const MySet<std::string>& words) {
    stringer = stringer.set_union(words);

}

void WebPage::all_out(const MySet<std::string>& links) {
    linker = linker.set_union(links);
}

/**
 * Returns all the unique, tokenized words in this webpage
 */
MySet<std::string> WebPage::all_words() const {
    return stringer;

}

/**
 * Adds a webpage that links to this page
 */
void WebPage::add_incoming_link(WebPage* wp) {
    webber_in.insert(wp);

}

/**
 * Returns all webpages that link to this page
 */
MySet<WebPage*> WebPage::incoming_links() const {
    return webber_in;

}

/**
 * Adds a webpage that this page links to
 */
void WebPage::add_outgoing_link(WebPage* wp) {
    webber_out.insert(wp);

}

/**
 * Returns all webpages this page links to
 */
MySet<WebPage*> WebPage::outgoing_links() const {
    return webber_out;

}

/**
 * Displays the webpage text to the screen
 */
std::ostream & operator<< (std::ostream & os, const WebPage & page) {
    std::string filename = page.filename();
    std::ifstream file ( filename.c_str() );
    std::string line;
    std::vector <std::string> storage;
    while ( getline (file,line) ) {
        storage.push_back(line);
    }
    std::string theLine = storage[0];
    for (size_t g = 0; g < theLine.length(); g++) {
        if (theLine[g-1] == ']' && theLine[g] == '(') {
            int m = g;
            int found = g;
            while (theLine[m]!= ')') {
                theLine[m]=' ';
                m++;
            }
            theLine[m]= ' ';
            g= m;
            theLine = theLine.substr(0, found) + theLine.substr(m+1, theLine.length()-m-1);
        }
    }
    storage[0]= theLine;


    file.close();
    for (unsigned int i=0; i < storage.size(); i++) {
        os << storage[i] << " ";


    }
    return os;
}

std::string WebPage::texter() {
    std::string filename = this->filename();
    std::ifstream file ( filename.c_str() );
    std::string line;
    std::vector <std::string> storage;
    while ( getline (file,line) ) {
        storage.push_back(line);
    }
    std::string theLine = storage[0];
    for (size_t g = 0; g < theLine.length(); g++) {
        if (theLine[g-1] == ']' && theLine[g] == '(') {
            int m = g;
            int found = g;
            while (theLine[m]!= ')') {
                theLine[m]=' ';
                m++;
            }
            theLine[m]= ' ';
            g= m;
            theLine = theLine.substr(0, found) + theLine.substr(m+1, theLine.length()-m-1);
        }
    }
    storage[0]= theLine;


    file.close();
    return storage[0];
}





