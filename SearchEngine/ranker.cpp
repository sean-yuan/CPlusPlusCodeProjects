#include "ranker.h"
#include <fstream>
#include <iostream>
#include <set>
#include <map>
#include <sstream>
#include <vector>
#include <string>
#include <iterator>
#include <cassert>
#include <cstdlib>
#include <ctime>
#include <algorithm>

void Ranker::ranker(MySet<WebPage*> candidates, std::string config_file) {
	std::map<std::string, std::string> keys = configer(config_file);
	std::string temp1 = keys.find("STEP_NUMBER")->second;
	std::string temp2 = keys.find("RESTART_PROBABILITY")->second;
	double stepn = atof(temp1.c_str());
    //std::cout << stepn << std::endl;
	double restartp = atof(temp2.c_str());
    //std::cout << restartp << std::endl;
	std::set<WebPage*>::iterator it;
    for (it=candidates.begin(); it!=candidates.end(); ++it) {
		(*it)->add_incoming_link(*it);
	}
	std::map<WebPage*, double> prev_pr;
	std::set<WebPage*>::iterator mo;
    for (mo=candidates.begin(); mo!=candidates.end(); ++mo) {
        prev_pr.insert (std::pair<WebPage*, double>((*mo), 1.0/candidates.size()) );
	}

	for(int i = 0; i < stepn; i++) {
        //std::cout<< "hi" << std::endl;
		std::map<WebPage*, double> temp_pr; //keeps track of page ranks for current iteration
		
		std::set<WebPage*>::iterator re;
    	for (re=candidates.begin(); re!=candidates.end(); ++re) {
            WebPage *we = new WebPage;
            we = (*re);
            //std::cout << "here" << std::endl;
            //std::cout << (*re)->filename() ;
			MySet<WebPage*> incomingLinks = (we)->incoming_links();
			double sumOfPageRanks = 0;

			std::set<WebPage*>::iterator te;
    		for (te=incomingLinks.begin(); te!=incomingLinks.end(); ++te) {
				double prevPageRank = prev_pr.find(*te)->second;
				prevPageRank = prevPageRank/((*te)->linker).size();
				sumOfPageRanks += prevPageRank;
			}
			double currentPageRank = (1 - restartp)*sumOfPageRanks+(restartp*candidates.size());
            temp_pr.insert (std::pair<WebPage*, double>( (*re) , currentPageRank) );
            //std::cout<< web->filename() << " " << currentPageRank << std::endl;
		}
		prev_pr = temp_pr;
	}
	std::map<WebPage*, double>::iterator po;
	for ( po = prev_pr.begin(); po != prev_pr.end(); po++ ){
		(po->first)->add_rank(po->second);
	}
}








std::string Ranker::parse_space(std::string s) {
    std::string newStr;
    for(unsigned int i = 0 ; i < s.length(); i++) {
        if(s[i] != ' ') {
            newStr += s[i];
        }
    }
    return newStr;
}

std::map<std::string, std::string> Ranker::configer(std::string file1){
    std::ifstream file (file1.c_str());
    if ( !file.is_open() ) {
        std::cout<<"Could not open file\n";
        throw std::exception();
    }
    std::map<std::string, std::string> baggy;
    std::string line;
    std::vector <std::string> storage;
    while ( getline (file,line) ) {
        if (line.find('=') != std::string::npos){
            int i=0;
            while(line[i] != '#'){
                i++;
            }
            line = line.substr(0, i);
            line = parse_space(line);
            int r=0;
            while(line[r] != '='){
                r++;
            }
            std::string key = line.substr(0, r);
            std::string value = line.substr(r+1,line.length());
            baggy.insert (std::pair<std::string, std::string>(key, value) );
        }
    }
    return baggy;
}
