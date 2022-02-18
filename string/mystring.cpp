// BENJAMIN AIROLA
// COEN 79
// PROFESSOR BEHNAM DEZFOULI
// LAB 5 -- Implementing String Class
// February 4, 2022

#include "mystring.h"
#include <cctype>
#include <cassert>
#include <string.h>
#include <iostream>

using namespace std;
using namespace coen79_lab5;

namespace coen79_lab5{
  // constructor with character array input
  string::string(const char str[ ]){
    current_length = strlen(str);
    allocated = current_length + 1;
    characters = new char[allocated];
    strncpy(characters, str, strlen(str));
    characters[current_length] = '\0';
  }

  // constructor with character input
  string::string(char c){
    current_length = 1;
    allocated = 2;
    characters = new char[allocated];
    characters[0] = c;
    characters[1] = '\0';
  }

  // copy constructor
  string::string(const string& source){
    characters = new char[source.current_length + 1];
    strncpy(characters, source.characters, source.current_length);
    current_length = source.current_length;
    allocated = source.allocated;
    characters[current_length] = '\0';
  }

  // destructor for string class
  string::~string( ){
    delete [] characters;
    current_length = 0;
    allocated = 0;
  }

  // overloaded addition assignment
  void string::operator +=(const string& addend){
    size_t finalLength = current_length + addend.current_length;
    allocated = finalLength + 1;
    reserve(allocated);
    strncat(characters, addend.characters, addend.current_length);
    current_length = finalLength;
    return;
  }

  // overloaded addition assignment
  void string::operator +=(const char addend[ ]){
    size_t finalLength = current_length + strlen(addend);
    allocated = finalLength + 1;
    reserve(allocated);
    strncat(characters, addend, strlen(addend));
    current_length = finalLength;
    return;
  }

  // overloaded addition assignment
  void string::operator +=(char addend){
    size_t finalLength = current_length + 1;
    allocated = finalLength + 1;
    reserve(allocated);
    characters[current_length] = addend;
    current_length = finalLength;
    return;
  }

  // allocates more dynamic memory for array in string object
  void string::reserve(size_t n){
    if(n <= allocated)
      return;
    char* tmp = new char[n];
    if(characters != NULL){
      strncpy(tmp, characters, current_length);
      delete []characters;
    }
    characters = tmp;
    return;
  }

  // overloaded assignment
  string& string::operator =(const string& source){
    this->dlt(0, current_length);
    if(allocated != source.allocated){
      allocated = source.allocated;
      reserve(allocated);
    }
    strncpy(characters, source.characters, source.current_length);
    current_length = source.current_length;
    return *this;
  }

  // inserts string into position of current string
  void string::insert(const string& source, unsigned int position){
    assert(position <= length());
    char* tmp = new char[current_length + source.current_length + 1];
    if(position > 0){
      strncpy(tmp, characters, position);
    }
    char* second_hlf = new char[current_length - position];
    for(int i = position, j = 0; i <= current_length; i++, j++){
      second_hlf[j] = characters[i];
    }
    delete[] characters;
    strncat(tmp, source.characters, source.current_length);
    strncat(tmp, second_hlf, strlen(second_hlf));
    characters = tmp;
    current_length += source.current_length;
    allocated = current_length + 1;
    return;
  }

  // deletes num characters starting at position
  void string::dlt(unsigned int position, unsigned int num){
    assert((position + num) <= length());
    for(int i = position; i < length(); i++){
      characters[i] = characters[i + num];
    }
    current_length -= num;
    return;
  }

  // replaces character in current string at position with c
  void string::replace(char c, unsigned int position){
    assert(position < length());
    characters[position] = c;
    return;
  }

  // replaces string at position with source
  void string::replace(const string& source, unsigned int position){
    assert((position + source.current_length) <= current_length);
    int j = 0;
    for(int i = position; i < (position + source.length()); i++){
	*(characters + i) = source[j++];
    }
    return;
  }

  // overloaded [] operator
  char string::operator [ ](size_t position) const{
    assert(position < length());
    return characters[position];
  }

  // returns location of char c in current string
  int string::search(char c) const{
    for(int i = 0; i < length(); i++){
      if(c == characters[i])
	        return i;
    }
    return -1;
  }

  // returns location of substring in current string
  int string::search(const string& substring) const{
    int index = -1;
    char* tmp = strstr(characters, substring.characters);
    if(tmp != NULL){
      index = *tmp - *characters;
    }
    return index;
  }

  // returns the occurences of char c in current string
  unsigned int string::count(char c) const{
    unsigned int sum = 0;
    for(int i = 0; i < length(); i++){
      if(c == characters[i]){
	        sum++;
      }
    }
    return sum;
  }

  // prints string to ostream  
  std::ostream& operator <<(std::ostream& outs, const string& source){
    outs << source.characters;
    return outs;
  }

  // overloaded equality operator for class string
  bool operator ==(const string& s1, const string& s2){
    return (strcmp(s1.characters, s2.characters) == 0);
  }

  // overloaded non-equality operator for class string
  bool operator !=(const string& s1, const string& s2){
    return (strcmp(s1.characters, s2.characters) != 0);
  }
  
  // overloaded greater than operator for class string
  bool operator > (const string& s1, const string& s2){
    return (strcmp(s1.characters, s2.characters) > 0);
  }

  // overloaded less than operator for class string
  bool operator < (const string& s1, const string& s2){
    return (strcmp(s1.characters, s2.characters) < 0);
  }

  // overloaded greater than or equal to operator for class string
  bool operator >=(const string& s1, const string& s2){
    return ((s1 > s2) || (s1 == s2));
  }

  // overloaded less than or equal to operator for class string
  bool operator <=(const string& s1, const string& s2){
    return ((s1 < s2) || (s1 == s2));
  }

  // overloaded addition operator for class string
  string operator +(const string& s1, const string& s2){
    string temp;
    temp.reserve(s1.length() + s2.length() + 1);
    temp += s1;
    temp += s2;
    return temp;
  }

  // overloaded addition operator for class string
  string operator +(const string& s1, const char addend[ ]){
    string temp;
    temp.reserve(s1.length() + strlen(addend) + 1);
    temp += s1;
    temp += addend;
    return temp;
  }

  // instream overloaded operator for class string
  std::istream& operator >> (std::istream& ins, string& target){
    while(ins && isspace(ins.peek())){
      ins.ignore();
    }
    char* input = new char[500];
    ins >> input;
    target = string(input);
    return ins;
  }
}
