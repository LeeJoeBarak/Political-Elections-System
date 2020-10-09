//
// Created by ise on 17.1.2020.
//

#ifndef POLSYS_LEEJOE_POLITICALSYSDEFS_H
#define POLSYS_LEEJOE_POLITICALSYSDEFS_H
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <stdio.h>
#include <string.h>

using namespace std;


typedef pair<int, std::string> Key_biggest;
//typedef pair<int, int> Key_smallest;




class trimClass{
public:
	string trim(const std::string& str, const std::string& whitespace);
};


/** Sort Functor For PrintBiggestParty  */
class KeyComparator{
    /**
     * Input: std::pair<int, std::string>
     * where: 1. <int> is party->getSize()   2. <std::string> is party->name
     * */
public:
    bool operator()(std::pair<int, std::string> lhs, std::pair<int, std::string> rhs){
        if(lhs > rhs) return true;
        else{ return false ;}
    }
};



template <class T>
class mypair{
public:
    void replace_key(T &container, const typename T::key_type &oldKey, const typename T::key_type &newKey);
};


template <class T>
void mypair<T>::replace_key(T &container, const typename T::key_type &oldKey, const typename T::key_type &newKey) {
    if (!container.key_comp()(oldKey, newKey) && !container.key_comp()(newKey, oldKey)) {
        return;
    } //Thanks to Graham for this Fix
    typename T::iterator begin(container.find(oldKey));

    for (;;) {
        if (begin != container.end()) {
            container.insert(typename T::value_type(newKey, begin->second));
            container.erase(begin); // Thanks to Graham for this potential fix
            begin = container.find(oldKey);
        } else {
            return;
        }
    }
}


#endif //POLSYS_LEEJOE_POLITICALSYSDEFS_H
