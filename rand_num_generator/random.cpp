/* Benjamin Airola
 * COEN 79
 * Lab 2
 * Random Number Generator
 * 01/20/2022
 */

#include "random.h"
#include <iostream>

using namespace std;

namespace coen79_lab2 {

    //constructor for class rand_gen
    rand_gen::rand_gen(int seed, int multiplier, int increment, int modulus) {
        this->seed = seed;
        this->multiplier = multiplier;
        this->increment = increment;
        this->modulus = modulus;
    }

    //Accessing objects seed and changing it
    void rand_gen::set_seed(int newSeed) {
        this->seed = newSeed;
    }

    //Creating new seed
    int rand_gen::next() {
	assert(modulus != 0);
        int temp;
        temp = (this->multiplier * this->seed + this->increment) % this->modulus;
        this->set_seed(temp);
        return temp;
    }

    //Printing all info
    void rand_gen::print_info() const {
	cout << "Seed: " << this->seed << endl;
        cout << "Multiplier: " << this->multiplier << endl;
        cout << "Increment: " << this->increment << endl;
        cout << "Modulus: " << this->modulus << endl;
    }


}

