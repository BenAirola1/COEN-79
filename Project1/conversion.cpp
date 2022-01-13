/* Ben Airola
 * COEN 79
 * 01/07/2022
 * Project 1 */

/* This application reads from a file, and outputs all words longer than 10 characters, converted to capital letters. */

#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

bool is_alphabet(char c);

int main(int argc, char* argv[]) {
	
	/* 
	 * Time Complexity: O(1)
	 * Description: Asserting preconditions.
	 */	
	if (argc < 2) {
		cout << "USAGE ERROR." << endl;
		return 1;
	}		

	/* 
	 * Time Complexity: O(1)
	 * Description: Variable Declaraction.
	 */
	string input;
	vector<string> passing;
	string temp;
	
	/*
 	 * Time Complexity: O(n)
 	 * Description: Reads input, capitalizes letters, and pushes passing words to new vector.
 	 */
	ifstream file (argv[1]);
	while(file >> input) {
		temp = "";
		for(char c : input) {
			if(is_alphabet(c)) {
				temp += toupper(c);			
			}
		}	
		if(temp.length() > 9)
			passing.push_back(temp);
	}

	/* 
	 * Time Complexity: O(n)
	 * Description: Outputs words.
	 */
	for(string word : passing)
		cout << word << endl;


	return EXIT_SUCCESS;
}

/*
 * Time Complexity: O(1)
 * Description: Returns true if character input is a letter.
 */
bool is_alphabet(char c) {
	if(c > 64 && c < 91)
		return true;
	if(c > 96 && c < 123)
		return true;
	return false; 
}











