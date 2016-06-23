#include <iostream>
#include <set>
#include <map>
#include <sstream>
#include <vector>
#include <string>
#include <fstream>
#include <iterator>
//#include "bst.h"
//#include "rbbst.h"
#include "mapcoloring.h"

int main(int argc, char* argv[]){
	if(argc < 2) {
    	std::cout << "Error: please include input file" << std::endl;
    	return 0;    
    }
    std::string arg(argv[1]);
   	MapColor map_color(arg);
   	std::map<char, Node*> map_graph = map_color.graph;
   	std::cout << "got the map" << std::endl;
   	int size = map_graph.size();
   	int *color = new int[size];
    for (int i = 0; i < size; i++) {
        color[i] = 0;
    }
    if (map_color.colorHelp(map_graph, size, color, 0) == false) {
        std::cout << "Not Possible" << std::endl;
    }

    char a[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    for (int i = 0; i < size; i++) {
        std::cout << a[i] << " " << color[i] << std::endl;
    }
}

