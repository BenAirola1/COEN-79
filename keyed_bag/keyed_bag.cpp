//Benjamin Airola
//COEN 79
//Professor Behnam Dezfouli
//Implementation of keyed_bag class

#include "keyed_bag.h"
#include <cstdlib>
#include <cassert>
#include <cmath>

using namespace std;
using namespace coen79_lab4;

namespace coen79_lab4 {
    // CONSTRUCTOR FOR CLASS
    keyed_bag::keyed_bag() {
        erase();    
    }

    // EMPTIES KEYED_BAG OBJECT
    void keyed_bag::erase() {
        for(int i = 0; i < CAPACITY; i++) {             
            keys[i] = '\0';                         
            data[i] = NULL;                         
        }
        used = 0;                                   
    }

    // ERASES SPECIFIC VALUE WITH KEY_TYPE KEY
    bool keyed_bag::erase(const key_type& key) {                          
        for(int i = 0; i < used; i++) {             
            if(keys[i] == key) {                    
                for(int j = i; j < used-1 ; j++) {  
                    keys[j] = keys[j+1];            
                    data[j] = data[j+1];            
                }
                used--;
                return true;                        
            }
        }
        return false;                               
    }

    // INSERTS NEW VALUE INTO KEYED BAG
    void keyed_bag::insert(const value_type& entry, const key_type& key) {
        assert((used < CAPACITY) && (has_key(key) == false));     
        keys[used] = key;                           
        data[used] = entry;                         
        used++;
    }

    // OVERLOADED ADDITION ASSIGNMENT OPERATOR
    void keyed_bag::operator+=(const keyed_bag& addend) {
        assert(used + addend.size() <= CAPACITY); 
        for(int i = 0; i < addend.used; i++) {      
            if( !has_key(addend.keys[i]) ) {        
                keys[used] = addend.keys[i];      
                data[used] = addend.data[i];         
                used++;
            }
        }
    }

    // RETURNS TRUE IF KEY ALREADY EXISTS IN KEYED BAG OBJECT
    bool keyed_bag::has_key(const key_type& key) const {
        for(int i = 0; i < used; i++) {             
            if(keys[i] == key) {                    
                return true;                        
            }
        }
        return false;
    }

    // RETURNS VALUE_TYPE ITEM IN KEYED_BAG WITH SPECIFIED KEY
    keyed_bag::value_type keyed_bag::get(const key_type& key) const {
        assert(has_key(key));                       
        for(int i = 0; i < used; i++) {               
            if(keys[i] == key) {                    
                return data[i];                     
            }
        }                             
    }

    // RETURNS SIZE OF KEYED_BAG OBJECT
    keyed_bag::size_type keyed_bag::size() const {
        return used;
    }

    // RETURNS NUMBER OF OCCURENCES OF TARGET IN KEYED_BAG OBJECT
    keyed_bag::size_type keyed_bag::count(const value_type& target) const {
        size_type count = 0;                        
        for(int i = 0; i < used; i++) {             
            if(data[i] == target) {                 
                count++;                            
            }
        }
        return count;
    }

    // CHECKS WHETHER TWO KEYED_BAGS HAVE SHARED KEYS
    bool keyed_bag::hasDuplicateKey(const keyed_bag& otherBag) const {
        for(int i = 0; i < otherBag.used; ++i) {    
            if( has_key(otherBag.keys[i]) ) {       
                return true;                        
            }
        }
        return false;
    }

    // OVERLOADED ADDITION OPERATOR FOR KEYED_BAG OBJECTS
    keyed_bag operator+(const keyed_bag& b1, const keyed_bag& b2) {
        assert(((b1.size()+b2.size()) <= keyed_bag::CAPACITY) && !b1.hasDuplicateKey(b2));
        keyed_bag temp;
        temp += b1;
        temp += b2;
        return temp;
    }
}
