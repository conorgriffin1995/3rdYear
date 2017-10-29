// X00120179 Lee Healy 
// X00111602 Conor Griffin

// Google style guide rules followed
// 1). Scoping - Namespaces, Local Variables(Initialisation)
// 2). Naming - Variable Names, Function Names, Struct Data Names
// 3). Comments - comment style, class/function comments
// 4). Formatting - Spaces Vs Tabs
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "dirent.h"

// Conor Griffin X00111602
// Struct to hold flow control counts
typedef struct {
	std::string file_Name = " ";
	int iterative_Count = 0;
	int selection_Count = 0;
}ScanResults;

// ***FUNCTIONS***
// Conor Griffin X00111602
// Function that scans files and returns structs full of flow control counts
ScanResults ScanCpp(std::string file_path);

// Lee Healy X00120179
// Function that compares the counts in the files
bool CompareFiles(ScanResults file1, ScanResults file2);



int main(void)
{
	// 1). User passes in an input dir 
	// 2). Dir is scanned for any files
	// 3). Each file is scanned for any flow control statements
	// 4). Print the list of files

	// Lee Healy X00120179
	// Conor Griffin X00111602
	char control = ' '; //Controls whether you run the program again or not

	while (control != 'N') {

		std::vector<ScanResults>file_Results;


		// Open directory - CODE USED FROM LINK PROVIDED ON ADS MOODLE PAGE
		/*
		*    Usage: <USED>
		*    Title: <Accessing Directories In C/C++ Part II >
		*    Author: <Gabe>
		*    Date: <30/October/2016>
		*    Availability: <http://www.dreamincode.net/forums/topic/60036-accessing-directories-in-cc-part-ii/> 
		*/

		DIR *pdir = NULL;
		struct dirent *pent = NULL;

		std::string path;
		std::cout << "Please enter the dirctory: ";
		std::cin >> path;

		pdir = opendir(path.c_str());

		if (pdir != NULL)
		{
			while (pent = readdir(pdir)) 
			{
				// Lee Healy X00120179
				std::string file_Name = pent->d_name; // Saves us typing pent->d_name each time
				
				std::cout << "SCANNING FILE: " << file_Name << std::endl;

					// Path is re-attached to the file name because d_name only returns the name and not the location of the file
					ScanResults scan_results = ScanCpp(path + "\\" + file_Name);

					scan_results.file_Name = file_Name;
					std::cout << "\nSelection Statements:\t" << scan_results.selection_Count << std::endl;
					std::cout << "Iterative Statements:\t" << scan_results.iterative_Count << " \n" << std::endl;

					file_Results.push_back(scan_results);
			}// End While
			closedir(pdir);


			// Lee Healy X00120179
			// ***PLAGARISM CHECK***
			// This loop will go through each file 1 by 1
			for (unsigned int i = 0; i < file_Results.size(); i++) {
				ScanResults file1 = file_Results.at(i);
				// This loop will then compare it with every other file in the vector for match
				for (unsigned int j = 0; j < file_Results.size(); j++) {
				
					// If files are different compare them (File[i] will not compare with itself as itself at File[j])
					if (i != j) {
						ScanResults file2 = file_Results.at(j);
						bool is_Plagarised = CompareFiles(file1, file2);

						if (is_Plagarised == 1) {
							std::cout << "Plagarism detected in: " << file1.file_Name << " and " << file2.file_Name << std::endl;
						}// End Inner If
					}// End Outer If
				}// End Inner For
			}// End Outer For
		}
		else {
			std::cout << "Sorry, couldn't open that directory!" << std::endl;
		}


		std::cout << "Would you like to compare another directory? (Y/N): ";
		std::cin >> control;
		if (control == 'N' || control == 'n') {
			return 0;
		}

		std::cout << "\n"; // Spacing

	}// End Control/Repeat While
	
	system("pause");
	return 0;
}


// Lee Healy X00120179
bool CompareFiles(ScanResults file1, ScanResults file2) {
	// Compares two files for plagarism

	// Stops comparing files where both counts are 0
	if ((file1.selection_Count != 0 && file2.selection_Count != 0) && (file1.iterative_Count != 0 && file2.iterative_Count != 0)) {
		bool select_Same = file1.selection_Count == file2.selection_Count;
		bool iter_Same = file1.iterative_Count == file2.iterative_Count;
		return select_Same && iter_Same; // Returns 1
	}
	// If one count is zero and the other count isn't zero STILL compare them but if BOTH are zero then don't compare...
	else if ((file1.selection_Count == 0 && file2.selection_Count == 0) && (file1.iterative_Count != 0 && file2.iterative_Count != 0)) {
		bool select_Same = file1.selection_Count == file2.selection_Count;
		bool iter_Same = file1.iterative_Count == file2.iterative_Count;
		return select_Same && iter_Same; // Returns 1
	}
	else if ((file1.selection_Count != 0 && file2.selection_Count != 0) && (file1.iterative_Count == 0 && file2.iterative_Count == 0)) {
		bool select_Same = file1.selection_Count == file2.selection_Count;
		bool iter_Same = file1.iterative_Count == file2.iterative_Count;
		return select_Same && iter_Same; // Returns 1
	}
	
}

// Conor Griffin X00111602
ScanResults ScanCpp(std::string file_path) {
	// Reads in any given file from file_path, then scans the code for certain words and counts them

	const int SIZE = 7;
	std::string word[SIZE] = {"while", "do", "for", "if", "else", "switch", "case"};

	std::string current_line;
	ScanResults results; //creating struct called results of type struct ScanResults
	size_t position;

	std::ifstream file_in; 
	file_in.open(file_path); 

		while (getline(file_in, current_line)) {
			// std::cout << current_line << std::endl; // Prints out each line in the given file (if needed for checking, debugging etc...)

			// Checking if current line contains any flow control statements
			for (int i = 0; i < SIZE; i++) {
				position = current_line.find(word[i]);
				 
				/*
				*    Usage: <USED/MODIFIED>
				*    Title: <std::string::find>
				*    Author: <cplusplus.com>
				*    Date: <2/November/2016>
				*    Availability: <http://www.cplusplus.com/reference/string/string/find/>
				*/
	
				if (position != std::string::npos) { // npos value, when used as the value for a length/size parameter in a string's member functions, means "until the end of the string".

					// Checking for Iterative words and incrementing the iterativeCount if they are found
					if (word[i] == "while") {
						results.iterative_Count++;
					}
					else if (word[i] == "do") {
						results.iterative_Count++;
					}
					else if (word[i] == "for") {
						results.iterative_Count++;
					}

					// Checking for Selection words and incrementing the selectionCount if they are found
					else if (word[i] == "if") {
						results.selection_Count++;
					}
					else if (word[i] == "else") {
						results.selection_Count++;
					}
					else if (word[i] == "switch") {
						results.selection_Count++;
					}
					else if (word[i] == "case") {
						results.selection_Count++;
					}// End Inner If
				}// End Outer If
			}// End For Loop
		}// End While Loop
	
	// We're done, close the file.
	file_in.close();
	return results; // Return type struct
}