#include "crawler.h"
#include "webpage.h"
#include "myset.h"
#include "pageparser.h"
#include "md.h"
#include <fstream>
#include <iostream>
#include <set>
#include <map>
#include <sstream>
#include <vector>
#include <string>
#include <iterator>
#include <cassert>
#include <deque> 
#include <stack>

void Crawler::crawler(std::string config_file) {
	std::map<std::string, std::string> keys = configer(config_file);
	std::string index = keys.find("INDEX_FILE")->second;
	std::string out = keys.find("OUTPUT_FILE")->second;
	PageParser* pager = new MD;
	MySet<std::string> allWords;
	MySet<std::string> allLinks;

	std::stack<std::string> s;
	std::set<std::string> visitedWebPages;
	std::vector<std::string> outputs;
	s.push(index);
	while(!s.empty()) {
		std::string link = s.top();
		s.pop();
		if(visitedWebPages.find(link) == visitedWebPages.end() ) {
			visitedWebPages.insert(link);
			outputs.push_back(link);
			pager->parse(link, allWords, allLinks);
			std::set<std::string>::iterator it;
    		for (it=allLinks.begin(); it!=allLinks.end(); ++it) {
				if(visitedWebPages.find(*it) == visitedWebPages.end() ) {
					s.push(*it);
				}
			}
		}
	}
    //std::cout << outputs.size() << std::endl;
	std::ofstream outputFile;
    outputFile.open (out.c_str());
    for (unsigned int x=0; x < outputs.size(); x++){
        //std::cout << outputs[x] << std::endl;
    	outputFile << outputs[x] << std::endl;
    }
}



std::string Crawler::parse_space(std::string s) {
    std::string newStr;
    for(unsigned int i = 0 ; i < s.length(); i++) {
        if(s[i] != ' ') {
            newStr += s[i];
        }
    }
    return newStr;
}

std::map<std::string, std::string> Crawler::configer(std::string file1){
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
