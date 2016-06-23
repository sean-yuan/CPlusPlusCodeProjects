#ifndef HASHTABLE_H
#define HASHTABLE_H
#include <string>
#include <iostream>
#include <list>


class HashTable {
     public:
       HashTable ();

       ~HashTable ();

       void add (std::pair<std::string, int> new_item);
         /* adds new_item to the hashtable.  
            Conflicts should be resolved via chaining.
            You may use the STL list to accomplish this. 
            Throws an exception if the key is already 
            in the hashtable.*/

       const int& find(std::string key);
         /* returns the value with the associated key. 
            Throws an exception if the key is not in the
            hashtable. */

       void remove (std::string key);
         /* removes the element with the associated key. 
            Throws an exception if the key is not in the
            hashtable. */

       void update (std::pair<std::string, int> new_value);
         /* finds the item with the associated key, 
            and updates its value accordingly. 
            Throws an exception if the key is not in the
            hashtable. */

   private:
    std::list< std::pair<std::string, int> >** hashArray;
    bool needsResize();
    void resize();
    long long hashFunction(std::string str);
    unsigned int hashArraySize;
    unsigned int occupancy;


};

#endif
