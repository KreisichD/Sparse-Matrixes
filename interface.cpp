#include "interface.h"


using namespace std;

int CInterface::iGetInstruction(int & iInstrCode)
{
	string s_instruction = s_get_substring();  // take first word from s_line

	if (s_instruction == S_ADDMAT)		// and tries to match it witch available instructions
		iInstrCode = I_ADDMAT;
	else if (s_instruction == S_LIST)
		iInstrCode = I_LIST;
	else if (s_instruction == S_DEL)
		iInstrCode = I_DEL;
	else if (s_instruction == S_DELALL)
		iInstrCode = I_DELALL;
	else if (s_instruction == S_DEF)
		iInstrCode = I_DEF;
	else if (s_instruction == S_PRINT)
		iInstrCode = I_PRINT;
	else if (s_instruction == S_CLONE)
		iInstrCode = I_CLONE;
	else if (s_instruction == S_RENAME)
		iInstrCode = I_RENAME;
	else if (s_instruction == S_QUIT)
		iInstrCode = I_QUIT;
	else if (s_instruction == S_SET_SIZE)
		iInstrCode = I_SET_SIZE;
	else return I_WRONG_INSTRUCTION;

	return I_NO_ERROR;
}


int CInterface::iGetArguments(int iNumber, int * piArguments)
{
	while (ui_iterator < s_line.length() && iNumber > 0)
	{
		string s_part = s_get_substring();	// read part of instruction
		if (s_part.length() > 0 && b_is_number(s_part))		// if it is a number then add it to table
		{
			*piArguments++ = i_parse_to_int(s_part);
			iNumber--;
		}
	}

	return iNumber > 0 ? I_WRONG_ARGUMETS : I_NO_ERROR;		// chceck if there was at least iNumber arguments read
}

string CInterface::sGetString()
{
	return s_get_substring();
}

void CInterface::vReadNext()
{
	getline(cin, s_line);
	ui_iterator = 0;
}

void CInterface::vPrint(string s_text)
{
	cout << s_text;
}

void CInterface::vPrintError(int i_error_code)
{
	switch (i_error_code)
	{
	case I_ERROR_CORDS:
		cout << S_OUT_OF_BOUNDS_MESSAGE;
		break;
	case I_NO_SUCH_MATRIX:
		cout << S_MATRIX_NOT_INITIALIZED_MESSAGE;
		break;
	case I_ERROR_DIM:
		cout << S_NEGATIVE_DIM_NUMBER_MESSAGE;
		break;
	case I_ERROR_RANGE:
		cout << S_NEGATIVE_RANGE_MESSAGE;
		break;
	case I_WRONG_INSTRUCTION:
		cout << S_WRONG_INSTRUCTION_MESSAGE;
		break;
	case I_WRONG_ARGUMETS:
		cout << S_WRONG_ARGUMENTS_MESSAGE;
		break;
	default:
		break;
	}
}

string CInterface::s_get_substring()
{
	string s_result;

	while (ui_iterator < s_line.length() && s_line.at(ui_iterator) == SPACE)
		ui_iterator++;

	while (ui_iterator < s_line.length() && s_line.at(ui_iterator) != SPACE)
		s_result += s_line.at(ui_iterator++);

	return s_result;
}

bool CInterface::b_is_number(string s_line)
{
	bool b_is_number = s_line.length() != 0;

	for (unsigned int ii = s_line.at(0) == ASCII_MINUS ? 1 : 0; ii < s_line.length() && b_is_number; ii++) {
		char c_sign = s_line.at(ii);
		if ((int)c_sign < ASCII_FIRST_DIGIT || (int)c_sign > ASCII_LAST_DIGIT)
			b_is_number = false;
	}

	return b_is_number;
}

int CInterface::i_parse_to_int(string s_number)
{
	int i_result = 0;

	for (unsigned int ii = s_number.at(0) == ASCII_MINUS ? 1 : 0; ii < s_number.length(); ii++) {
		i_result *= DECIMAL_SYSTEM_BASE;
		i_result += (int)s_number.at(ii) - ASCII_FIRST_DIGIT;
	}

	return s_number.at(0) == ASCII_MINUS ? i_result*(-1) : i_result;
}
