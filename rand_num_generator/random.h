//  Benjamin Airola
//  COEN 79
//  Lab 2
//  Random Number Generator
//  01-20-2022
//
//   This class is part of the namespace coen79_lab2
//
// CONSTRUCTOR for the rand_gen class:
//   rand_gen( );
//     The object has been initialized, and is ready to generate pseudorandom numbers.
//
// PUBLIC member functions for the rand_gen class:
//  void set_seed(int newSeed)
//    The number new_seed is the new seed.
//  int next()
//    The return value is the next random integer, and the return value is set as the new seed

#ifndef RAND_NUM_H
#define RAND_NUM_H

#include <stdio.h>

using namespace std;

namespace coen79_lab2 {
    
    class rand_gen {
        public:
            rand_gen(int seed, int multiplier, int increment, int modulus);
            void set_seed(int newSeed);
            int next();
	    void print_info() const;
        
        private:
            int seed;
            int multiplier;
            int increment;
            int modulus;
    };
}

#endif
