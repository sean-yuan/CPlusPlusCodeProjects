#ifndef MAPCOLORING_H
#define MAPCOLORING_H

#include <iostream>
#include <set>
#include <map>
#include <sstream>
#include <vector>
#include <string>
#include <fstream>
#include <iterator>

//template <class KeyType, class ValueType>
class Node {
public:
    char countryValue;
    int colorValue;
    std::vector<Node*> neighbors;
};

class MapColor {

public:
    MapColor(std::string arg) {
        openfile(arg);
    }

    void openfile(std::string g) {
        std::ifstream file (g.c_str());
        if ( !file.is_open() ) {
            std::cout<<"Could not open file\n";
            throw std::exception();
        }
        int num_countries;
        file >> num_countries;
        int num_row;
        file >> num_row;
        int num_col;
        file >> num_col;

        char **countries = new char*[num_row];

        for (int i = 0 ; i < num_row; i++) {
            countries[i] = new char[num_col];
        }

        for (int i = 0; i < num_row; i++) {
            for (int g=0; g < num_col; g++) {
                file >> countries[i][g];
            }
        }

        neighbor_build(countries, num_countries, num_row, num_col);
    }




    void neighbor_build(char ** countries, int numCountries, int num_row, int num_col) {

        char alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

        for(int i = 0; i < numCountries; i++) {
            Node* country = new Node();
            country->countryValue = alphabet[i];
            country->colorValue = 0;
            graph.insert(std::pair<char, Node*>(country->countryValue, country));
        }

        bool **visited = new bool*[num_row];
        for (int i = 0 ; i < num_row; i++) {
            visited[i] = new bool[num_col];
        }

        edges(0, 0, countries, visited, num_row, num_col);
    }


    void edges(int row, int col, char ** countries, bool ** visited, int num_row, int num_col) {
        char currentValue = countries[row][col];
        visited[row][col] = true;

        search(row+1, col, currentValue, countries, visited, num_row, num_col);
        search(row-1, col, currentValue, countries, visited, num_row, num_col);
        search(row, col+1, currentValue, countries, visited, num_row, num_col);
        search(row, col-1, currentValue, countries, visited, num_row, num_col);
    }

    void search(int row, int col, char currentValue, char ** countries, bool ** visited,int num_row, int num_col) {
        if(row < 0 || row == num_row || col < 0 || col == num_col) {
            return;
        }
        if(!visited[row][col]) {
            visited[row][col] = true;
            if(currentValue != countries[row][col]) {
                Node* orig = graph.find(currentValue)->second;
                std::vector<Node*> neighbors = orig->neighbors;
                bool existsInNeighbors = false;
                for(unsigned int i=0; i< neighbors.size(); i++) {
                    if(neighbors[i]->countryValue == countries[row][col]) {
                        existsInNeighbors = true;
                    }
                }
                if(!existsInNeighbors) {
                    Node* newNeighbor = graph.find(countries[row][col])->second;
                    orig->neighbors.push_back(newNeighbor);
                    newNeighbor->neighbors.push_back(orig);
                    edges(row, col, countries, visited, num_row, num_col);
                }
            }
            else {
                search(row+1, col, currentValue, countries, visited , num_row,  num_col);
                search(row-1, col, currentValue, countries, visited, num_row,  num_col);
                search(row, col+1, currentValue, countries, visited, num_row,  num_col);
                search(row, col-1, currentValue, countries, visited, num_row,  num_col);
            }
        }
    }

    std::map<char, Node*> graph;

    bool checker (int curr_count, std::map<char, Node*> map_graph, int color[], int c){
        char a[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        std::vector<Node*> neigh = (map_graph.find(a[curr_count])->second)->neighbors;
        for (unsigned int i = 0; i < neigh.size(); i++) {
            if ( c == neigh[i]->colorValue) {
                return false;
            }
        }
        return true;
    }

    bool color( std::map<char, Node*> map_graph, int size) {
        int *color = new int[size];
        for (int i = 0; i < size; i++) {
            color[i] = 0;
        }
        if (colorHelp(map_graph, size, color, 0) == false) {
            std::cout << "Not Possible" << std::endl;
            return false;
        }

        char a[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        for (int i = 0; i < size; i++) {
            std::cout << a[i] << " " << color[i] << std::endl;
        }
        return true;
    }

    bool colorHelp(std::map<char, Node*> map_graph, int size, int color[], int curr_count){
        char a[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        unsigned int g = curr_count;
        if (g == map_graph.size()) {
            return true;
        }

        for (int c = 1; c <= size; c++) {
            if (checker(curr_count, map_graph, color, c)) {
                color[curr_count] = c;
                (map_graph.find(a[curr_count])->second)->colorValue = c;

                if (colorHelp (map_graph, size, color, curr_count+1) == true) {
                    return true;
                }

                color[curr_count] = 0;
                (map_graph.find(a[curr_count])->second)->colorValue = 0;
            }
        }
        return false;
    }


};
#endif
