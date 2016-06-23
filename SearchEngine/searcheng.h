#ifndef SEARCHENG_H
#define SEARCHENG_H

#include <map>
#include <vector>
#include <string>
#include "webpage.h"
#include "myset.h"
#include "pageparser.h"

class SearchEng {
public:
    SearchEng();
    ~SearchEng();
    void add_parse_from_index_file(std::string index_file,
                                   PageParser* parser);
    void add_parse_page(std::string filename,
                        PageParser* parser);

    /**** Add other desired member functions here *****/

    MySet<WebPage*> find(std::string word);

    std::vector <WebPage*> allweb;
private:
    std::map<std::string, std::vector <WebPage*> > bag;
    /**** Add other desired data members here *****/


};

#endif
