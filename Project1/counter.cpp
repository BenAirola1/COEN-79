/* Ben Airola
 * COEN 79
 * 07/12/2022
 * Project 1 */

/* This function returns the total number of Alpha-numeric characters, 
 * as well as the total number of non Alpha-numeric characters in an input string */


#include <string>
#include <iostream>

using namespace std;

#define EXIT_SUCCESS 0;

int main() {

	/* 
	 * Time Complexity: O(1)
	 * Description: Variable Declaration
	 */ 		
	int alpha = 0;
	int nonalpha = 0;
	int len;
	string input;

	/*
	 * Time Complexity: O(1)
	 * Description: Gathering user input.
	 */
	cout << "Please type something: " << endl;
	getline(cin, input);
	
	/*
	 * Time Complexity: O(n)
	 * Description: Counting alpha-numeric and non alpa-numeric characters.
	 */
	len = input.size();
	for(int i = 0; i < len; i++) {
		if(input[i] > 64 && input[i] < 91)
			alpha++;
		else if(input[i] > 96 && input[i] < 123)
			alpha++;
		else if(input[i] > 47 && input[i] < 58)
			alpha++;
		else if(input[i] != 32)
			nonalpha++;
	
	}

	/*
	 * Time Complexity: O(1)
	 * Description: Outputting results.
	 */
	cout << "\"" << input << "\"" << " has " << alpha
		 << " alphanumeric characters and " << nonalpha
			 << " non-alphanumeric characters." << endl;

	return EXIT_SUCCESS;
}
