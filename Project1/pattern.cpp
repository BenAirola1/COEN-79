/* Benjamin Airola
 * COEN 79
 * 01/12/2022
 * Project 1 */

 /* Description: This application displays a specified pattern of digits on the standard output. */

#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

int main() {

	/* Defining strings to be displayed. */	
	string first = "0123456789";
    	string second = "9876543210";

	/* First line */
	cout << first << endl;        	

	/* Second line */
	cout << setw(11) << second;
    	cout << setw(22) << first << endl;

	/* Third line */
	cout << setw(13) << second;
    	cout << setw(24) << first << endl;

	/* Fourth line */
	cout << setw(15) << second;
    	cout << setw(26) << first << endl;

	/* Fifth line */
	cout << setw(17) << second;
    	cout << setw(28) << first << endl;

	/* Sixth line */
	cout << setw(19) << second << endl;

	return EXIT_SUCCESS;
}
