#pragma once
#include <string>

//errors ID
const int I_ERROR_CORDS = -2;
const int I_ERROR_DIM = -1;
const int I_NO_ERROR = 0;
const int I_WRONG_INSTRUCTION = 1;
const int I_WRONG_ARGUMETS = 2;
const int I_ERROR_RANGE = 3;
const int I_NO_SUCH_MATRIX = 4;
// errors messages
const std::string S_OUT_OF_BOUNDS_MESSAGE = "out of bounds\n";
const std::string S_MATRIX_NOT_INITIALIZED_MESSAGE = "no such matrix\n";
const std::string S_NEGATIVE_DIM_NUMBER_MESSAGE = "negative dimensions number\n";
const std::string S_NEGATIVE_RANGE_MESSAGE = "negative values in ranges\n";
const std::string S_WRONG_INSTRUCTION_MESSAGE = "wrong instruction\n";
const std::string S_WRONG_ARGUMENTS_MESSAGE = "wrong arguments\n";

// ASCII
const int ASCII_FIRST_DIGIT = 48;
const int ASCII_LAST_DIGIT = 57;
const int ASCII_MINUS = 45;

const int DECIMAL_SYSTEM_BASE = 10;

// interface
const char SPACE = ' ';

//printconsts
const std::string S_SIZE = "size: ";
const std::string S_VALUES = " values: ";
const std::string S_LBRACKET = "[";
const std::string S_RBRACKET = "]";
const std::string S_COMA = ",";
const std::string S_DOUBLEDOT = ":";
const std::string S_SEMICOLON = ";";
const std::string S_MATRICES = " matrices:\n" ;
const std::string S_EMPTY = "";
const std::string S_HYPHEN = " - ";
const std::string S_END_LINE = "\n";

// instructions
const std::string S_ADDMAT = "addmat";
const std::string S_LIST = "list";
const std::string S_DEL = "del";
const std::string S_DELALL = "delall";
const std::string S_DEF = "def";
const std::string S_PRINT = "print";
const std::string S_CLONE = "clone";
const std::string S_RENAME = "rename";
const std::string S_QUIT = "quit";
const std::string S_SET_SIZE = "setsize";

// instructions codes
const int I_ADDMAT = 11;
const int I_LIST = 12;
const int I_DEL = 13;
const int I_DELALL = 14;
const int I_DEF = 15;
const int I_PRINT = 16;
const int I_CLONE = 17;
const int I_RENAME = 18;
const int I_QUIT = 19;
const int I_SET_SIZE = 20;