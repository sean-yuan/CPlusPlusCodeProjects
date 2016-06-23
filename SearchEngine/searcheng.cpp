#include "searcheng.h"
#include <fstream>
#include <iostream>
#include <set>
#include <map>
#include <sstream>
#include <vector>
#include <string>
#include <iterator>
#include <cassert>


SearchEng::SearchEng() {

}
SearchEng::~SearchEng() {
    for(std::map<std::string, std::vector <WebPage*> >::iterator it = bag.begin();
            it != bag.end();
            ++it) {
        for (unsigned int i = 0; i < (it->second).size(); i++) {
            delete (it->second)[i];
        }
    }

}
void SearchEng::add_parse_from_index_file(std::string index_file, PageParser* parser) {
    //std::cout <<  index_file <<std::endl;
    std::ifstream file (index_file.c_str());
    if ( !file.is_open() ) {
        std::cout<<"Could not open file :(\n";
        throw std::exception();
    }
    std::string line;
    std::vector <std::string> storage;
    while ( getline (file,line) ) {
            storage.push_back(line);
    }

    for (unsigned int i = 0 ; i < storage.size(); i++) {
        MySet<std::string> allWords;
        MySet<std::string> allLinks;

        parser->parse(storage[i],allWords, allLinks);
        WebPage* web = new WebPage;
        web->filename(storage[i]);
        web->all_words(allWords);
        web->all_out(allLinks);


        allweb.push_back(web);

        std::set<std::string>::iterator it;
        for (it=allWords.begin(); it!=allWords.end(); ++it) {
            unsigned int g = bag.size();
            std::string tor = *it;
            std::vector <WebPage*> too;
            too.push_back(web);
            bag.insert(std::pair< std::string , std::vector <WebPage*> >(tor, too) );
            if(bag.size() == g) {
                ( (bag.find(*it))->second ).push_back(web);
            }
        }
    }
    WebPage* ww = new WebPage;
    for(unsigned int i=0; i < allweb.size(); i++) {
        MySet<std::string> outgoinglinks = allweb[i]->linker;//get all outgoing links of website[i]
        
        std::set<std::string>::iterator te;
        for (te=outgoinglinks.begin(); te!=outgoinglinks.end(); ++te) {
            for(unsigned int r = 0; r < (allweb).size(); r++) {
                if((*te) == (allweb)[r]->filename() ) {
                    ww = (allweb)[r];
                }
            }//find the page
            ww->add_incoming_link(allweb[i]);
        }
    }

    WebPage* mm = new WebPage;
    for(unsigned int i=0; i < allweb.size(); i++) {
        MySet<std::string> outgoinglinknames = allweb[i]->linker;//get all outgoing link names of website[i]
        std::set<std::string>::iterator me;
        for (me=outgoinglinknames.begin(); me!=outgoinglinknames.end(); ++me) {
            for(unsigned int r = 0; r < (allweb).size(); r++) {
                if((*me) == (allweb)[r]->filename() ) {
                    mm = (allweb)[r];
                }
            }//find the page
            allweb[i]->add_outgoing_link(mm);
            
        }
    }


}
void SearchEng::add_parse_page(std::string filename,
                               PageParser* parser) {
    MySet<std::string> allWords;
    MySet<std::string> allLinks;
    parser->parse(filename,allWords, allLinks);

}

MySet<WebPage*> SearchEng::find(std::string word) {
    //std::set<WebPage*> answer;
    MySet<WebPage*> answer;
    std::vector <WebPage*> tim;
    if ( bag.find(word) == bag.end() ) {
        return answer;
    }
    tim = ( bag.find(word) )->second;
    for (unsigned int i=0; i < tim.size(); i++) {
        answer.insert(tim[i]);
    }
    return answer;
}