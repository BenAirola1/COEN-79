// Benjamin Airola
// COEN 79
// Behnam Dezfouli
// Project 3
// 01/21/2022
// Implementation for sequence class

#include <cassert>
#include <stdio.h>
#include <cmath>
#include "sequence1.h"

using namespace std;
using namespace coen79_lab3;

namespace coen79_lab3 {
    //constructor for sequence class
    sequence::sequence() {
        used = 0;
        cur = 0;
    }

    //sets the current location within the sequence to the beginning
    void sequence::start() {
        cur = 0;
    }

    //sets the current location within the sequence to the last entry
    void sequence::end() {
        cur = used-1;
    }

    //sets the current location within the sequence to the end
    void sequence::last() {
        cur = CAPACITY-1;
        
    }

    //moves current location forward only if current location is filled 
    void sequence::advance() {
        assert(is_item());
        if(cur < used)
            cur++;
    }

    //moves current lcoation backwards only if there is room
    void sequence::retreat() {
        if(cur > 0) {
            cur--;
        }
    }

    //returns the number of entries within the sequence
    sequence::size_type sequence::size() const {
        return used;
    }

    //inserts a new entry to sequence in front of the current item 
    void sequence::insert(const value_type& entry) {
        assert(size() < CAPACITY);
        if(used == 0) {
            data[used] = entry;
            //cur = 0;
        }
        else {
            for (int i = used; i >= cur+1; --i) {
                data[i] = data[i-1];
             }
            data[cur] = entry;
        }
        used++;
    }

    //attaches a new sequence to the back of the current item
    void sequence::attach(const value_type& entry) {
        assert(size() < CAPACITY);
        if(!is_item()) {
            data[used] = entry;
        }
        else {
            for(int i = used; i > cur+1; --i) {
                data[i]=data[i-1];
            }
            data[cur+1] = entry;
            cur++;
        }
        used++;
    }

    //removes current item
    void sequence::remove_current() {
        assert(is_item());
        for(int i = cur+1; i < used; ++i){
            data[i-1]=data[i];
        }
        used--;
    }

    //inserts new item to the front of the sequence
    void sequence::insert_front(const value_type& entry) {
        assert(size() < CAPACITY);
        cur=0;
        insert(entry);
        used++;
    }

    //attaches new item to the back of the sequence
    void sequence::attach_back(const value_type& entry) {
        assert(size() < CAPACITY);
        data[used] = entry;
        used++;
    }

    //removes the first item of the sequence
    void sequence::remove_front() {
        assert(is_item()); 
        for(int i = 0; i < used-1; ++i)
            data[i]=data[i+1];
        used--;
    }

    //Adds one sequence to another
    void sequence::operator+= (const sequence& rhs){
        assert(used + rhs.used <= CAPACITY);
        for(int i = 0; i < rhs.used; i++) {
            attach_back(rhs[i]);
        }
    }

    //Returns true if the current location is filled with an item
    bool sequence::is_item() const {
        if(cur < used)
            return true;
        return false;
    }

    //Returns the item at the current location
    sequence::value_type sequence::current() const {
        assert(is_item());
        return data[cur];
    }

    //Returns the item at a specified index
    sequence::value_type sequence::operator[] (size_type index) const {
        assert(index < used);
        return data[index];
    }

    //Returns the mean of the sequence
    double sequence::mean() const {
        double sum=0.0;
        for(int i = 0; i < used; ++i) {
            sum += data[i];
        }
        return sum/used;
    }

    //Returns the standard deviation of the sequence
    double sequence::standardDeviation() const {    
        double stdev = 0.0;
        double mean = sequence::mean();
        for(int i = 0; i < used; ++i) {
            stdev += pow(data[i] - mean, 2);
        }
        return sqrt(stdev/used); 
    }

    //Returns a sequence filled with the components of lhs and rhs 
    sequence operator+(const sequence& lhs, const sequence& rhs){
        assert((lhs.size() + rhs.size()) <= sequence::CAPACITY);
        sequence(tmp);
        tmp += lhs;
        tmp += rhs;
        return tmp;
    }

    //returns the sum of a sequence
    sequence::value_type summation(const sequence& s) {
        double sum = 0.0;
        for(int i = 0; i < s.size(); ++i) {
            sum += s.data[i];
        }
        return sum;
    }   


}
