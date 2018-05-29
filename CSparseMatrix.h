#pragma once
#include <string>
#include <iostream>
#include "constants.h"

const std::string S_BASIC_MATRIX_NAME = "Matrix";
const std::string S_OBJECT_COPY = "_copy";
const std::string S_CONSTRUCTOR_MESSAGE = "create: ";
const std::string S_DESTRUCTOR_MESSAGE = "destroy: ";

const int I_BASIC_TABLE_LENGTH = 10;
const int I_DOUBLE_TABLE = 2;

const int I_LOWER_ELEMENT = -100;
const int I_HIGHER_ELEMENT = 100;


template <class T> T* cCopyTable(T *pcTable, int iNumberofElements);
void vFillTable(int *piValues, int iTableLength);

class CSparseMatrix;
class CSparseCell
{
friend class CSparseMatrix;
public:
	CSparseCell();
	~CSparseCell();
	CSparseCell(int iValue, int *piCords, int iDimensions);
	CSparseCell(CSparseCell &pcCell);

private:
	//methods
	bool CSparseCell::b_cords_equal(int *piCords);
	int i_cords_compare(int *piCords);
	//pool
	int i_value;
	int *pi_cords;
	int i_dimensions;
};
class CSparseMatrix 
{
public:
	CSparseMatrix();
	~CSparseMatrix();
	CSparseMatrix(std::string sObjectName);
	CSparseMatrix(CSparseMatrix &pcMatrix);

	void vSetBasicValue(int iBasicValue) { i_basic_value = iBasicValue; };
	void vSetDimensions(int iNumberOfDimensions, int *piDimensionRanges) { i_number_of_dimensions = iNumberOfDimensions; pi_ranges_in_dimensions = piDimensionRanges; };
	void vSetName(std::string sName) { s_object_name = sName; };

	int iGetNumberOfDimensions() { return i_number_of_dimensions; }
	std::string sGetName() { return s_object_name; }
	std::string sGetDimRange() { return s_ranges_to_string(); }

	int iInitialize(int iBasicValue, int iNumberOfDimensions, int *piDimensionRanges);
	int iGetValue(int *piCords, int iElements, int &iResult);
	int iAddValue(int *piCords, int iValue);
	std::string sToString();
	/*CSparseMatrix* pcClone(CSparseMatrix &pcOther);*/
private:
	std::string s_object_name;
	int i_basic_value;
	int i_number_of_elements;
	int i_values_table_length;
	int *pi_ranges_in_dimensions;
	int i_number_of_dimensions;
	CSparseCell **pc_values;

	void v_copy(CSparseMatrix &pcCell);
	void v_constructor_message();
	void v_copy_table_values(CSparseMatrix &pcMatrix);
	bool b_check_cords(int *piCords);
	int i_contains(int *piCords);
	void v_change_table_length(bool flag);
	void v_add_sorted(int *piCords, int iValue);
	void v_add(int *piCords, int iValue, int iIndex);
	void v_delete_val(int *piCords,int iIndex);
	int i_get_value(int *piCords);
	std::string s_string_init();
	std::string s_attach_to_string(int *piActual);
	std::string s_ranges_to_string();
	bool b_normalize(int *piActual, int iGuard);
};


