#ifndef RANKER_H
#define RANKER_H

#include <map>
#include <vector>
#include <string>
#include "webpage.h"
#include "myset.h"
#include "pageparser.h"

class Ranker {
public:
	void ranker(MySet<WebPage*> candidates, std::string config_file);
	std::map<std::string, std::string> configer(std::string file1);
	std::string parse_space(std::string s) ;
   
private:
    


};

#endif