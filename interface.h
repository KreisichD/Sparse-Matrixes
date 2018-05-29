#pragma once
#include <iostream>
#include <string>
#include "constants.h"


using namespace std;

class CInterface
{
public:
	//CInterface();
	//~CInterface();
	int iGetInstruction(int & iInstrCode);  // returns code of instraction for line
	int iGetArguments(int iNumber, int * piArguments);		// returns iNumber arguments in piAgruments
	string sGetString();	// returns first substring
	void vReadNext();	// reset 
	void vPrint(string s_text);	// print s_text
	void vPrintError(int i_error_code);	// print error message

private:
	string s_line;
	unsigned int ui_iterator;

	string s_get_substring();
	bool b_is_number(string s_line);
	int i_parse_to_int(string s_number);
};

