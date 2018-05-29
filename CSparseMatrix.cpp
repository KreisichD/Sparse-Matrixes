#include "CSparseMatrix.h"

using namespace std;

template <class T> T* cCopyTable(T *pcTable, int iNumberofElements)		//copies tab of any type
{
	T *pc_tab = new T[iNumberofElements];
	for (int i=0; i < iNumberofElements; i++)
	{
		pc_tab[i] = pcTable[i];
	}
	return pc_tab;
}
void vFillTable(int *piValues, int iTableLength)						//fills any tab with zero's
{
	for (int i = 0; i < iTableLength; i++)
	{
		piValues[i] = 0;
	}
}
CSparseCell::CSparseCell()
{}
CSparseCell::CSparseCell(int iValue,int *piCords, int iDimensions)
{
	i_value = iValue;
	pi_cords = piCords;
	i_dimensions = iDimensions;
}
CSparseCell::CSparseCell(CSparseCell &pcCell)
{
	i_value = pcCell.i_value;
	i_dimensions = pcCell.i_dimensions;
	pi_cords = cCopyTable(pcCell.pi_cords, i_dimensions);
}
CSparseCell::~CSparseCell()
{
	delete [] pi_cords;
}
bool CSparseCell::b_cords_equal(int *piCords)
{
	/*bool result = true;
	for (int i = 0; i < i_dimensions && result; i++)
	{
		if (piCords[i] != pi_cords[i])
		{
			result = false;
		}
	}*/
	return i_cords_compare(piCords)==0;
}
int CSparseCell::i_cords_compare(int *piCords)
{
	int i_result = 0;
	for (int i = 0;i_result == 0 && i < i_dimensions; i++)
	{
		if (pi_cords[i] > piCords[i])
		{
			i_result = I_HIGHER_ELEMENT;
		}
		else if (pi_cords[i] < piCords[i])
		{
			i_result = I_LOWER_ELEMENT;
		}
	}
	return i_result;
}
CSparseMatrix::CSparseMatrix()
{
	s_object_name = S_BASIC_MATRIX_NAME;
	v_constructor_message();
	pc_values = NULL;
	pi_ranges_in_dimensions = NULL;
}
CSparseMatrix::CSparseMatrix(string sObjectName)
{
	s_object_name = sObjectName;
	v_constructor_message();
}
CSparseMatrix::CSparseMatrix(CSparseMatrix &pcMatrix)
{
	v_copy(pcMatrix);
	v_constructor_message();
}
CSparseMatrix::~CSparseMatrix()
{
	delete[] pi_ranges_in_dimensions;
	for (int i = 0; i < i_number_of_elements; i++)
	{
		delete pc_values[i];
	}
	delete pc_values;
	cout << S_DESTRUCTOR_MESSAGE << s_object_name << endl;
}
void CSparseMatrix::v_copy_table_values(CSparseMatrix &pcMatrix)
{
	for (int i = 0; i < i_number_of_elements; i++)
	{
		pc_values[i] = new CSparseCell(*(pcMatrix.pc_values[i]));
	}
	pi_ranges_in_dimensions = cCopyTable(pcMatrix.pi_ranges_in_dimensions, i_number_of_dimensions);
}
bool CSparseMatrix::b_check_cords(int *piCords)
{
	bool b_result = true;
	for (int i = 0; i < i_number_of_dimensions && b_result; i++)
	{
		if (piCords[i] >= pi_ranges_in_dimensions[i])
		{
			b_result = false;
		}
	}
	return b_result;
}
void CSparseMatrix::v_constructor_message()
{
	cout << S_CONSTRUCTOR_MESSAGE << s_object_name << endl;
}
void CSparseMatrix::v_copy(CSparseMatrix &pcMatrix)
{
	s_object_name = pcMatrix.s_object_name + S_OBJECT_COPY;
	i_basic_value = pcMatrix.i_basic_value;
	i_number_of_dimensions = pcMatrix.i_number_of_dimensions;
	i_number_of_elements = pcMatrix.i_number_of_elements;
	i_values_table_length = pcMatrix.i_values_table_length;
	pc_values = new CSparseCell*[i_values_table_length];
	pi_ranges_in_dimensions = new int[i_number_of_dimensions];
	v_copy_table_values(pcMatrix);
}
int CSparseMatrix::iInitialize(int iBasicValue, int iNumberOfDimensions, int *piDimensionRanges)
{
	if (iNumberOfDimensions > 0)
	{
		pi_ranges_in_dimensions = piDimensionRanges;
		i_basic_value = iBasicValue;
		i_number_of_dimensions = iNumberOfDimensions;
		i_number_of_elements = 0;
		i_values_table_length = I_BASIC_TABLE_LENGTH;
		pc_values = new CSparseCell*[i_values_table_length];
		return I_NO_ERROR;
	}
	else
	{
		return I_ERROR_RANGE;
	}
}
int CSparseMatrix::iGetValue(int *piCords, int iElements, int &iResult)
{
	if (b_check_cords(piCords))
	{
		return I_ERROR_CORDS;
	}
	else
	{
		iResult = i_get_value(piCords);
		return I_NO_ERROR;
	}
}
int CSparseMatrix::iAddValue(int *piCords, int iValue)
{
	int i_err = I_NO_ERROR;
	int i_index = i_contains(piCords);
	if (b_check_cords(piCords))
	{
		if (iValue != i_basic_value)
		{
			if (i_index >= 0)
			{
				pc_values[i_index]->i_value = iValue;
			}
			else
			{
				v_add_sorted(piCords, iValue);
			}
		}
		else
		{
			if (i_index >= 0)
			{
				v_delete_val(piCords, i_index);
			}
			//else do nothing!!
		}
	}
	else
	{
		i_err = I_ERROR_CORDS;
	}
	return i_err;
}
string CSparseMatrix::sToString()
{
	string s_result = s_string_init();
	int i_guard = i_number_of_dimensions - 1;
	int *pi_actual = new int[i_number_of_dimensions];
	vFillTable(pi_actual, i_number_of_dimensions);
	bool b_end_of_iteration = false;

	while (b_normalize(pi_actual, i_guard))
	{
		s_result += s_attach_to_string(pi_actual);
		pi_actual[i_guard]++;
	}
	return s_result;
}
//CSparseMatrix* CSparseMatrix::pcClone(CSparseMatrix &pcOther)
//{
//	CSparseMatrix *pc_new = new CSparseMatrix(pcOther);
//}
int CSparseMatrix::i_contains(int *piCords)
{
	bool b_found = false;
	int i_count = 0;
	for (int i = 0; i < i_number_of_elements && !b_found; i++)
	{
		if (pc_values[i]->b_cords_equal(piCords))
		{
			b_found = true;
			i_count = i;
		}
	}
	if (b_found)
	{
		return i_count;
	}
	else
	{
		return I_ERROR_CORDS;
	}
}
void CSparseMatrix::v_change_table_length(bool flag)
{
	if (flag)	//true -> widen  // false -> narrow
	{
		i_values_table_length *= I_DOUBLE_TABLE;
	}
	else
	{
		i_values_table_length /= I_DOUBLE_TABLE;
	}
	CSparseCell **pc_helper = new CSparseCell*[i_values_table_length];
	for (int i = 0; i < i_number_of_elements; i++)
	{
		pc_helper[i] = pc_values[i];
	}
	delete [] pc_values;
	pc_values = pc_helper;
}
void CSparseMatrix::v_add_sorted(int *piCords, int iValue)
{
	int i_iterate = 0;
	if (i_values_table_length-1 == i_number_of_elements)
	{
		cout << "longer" << endl;
		v_change_table_length(true);
	}
	while (i_iterate < i_number_of_elements && pc_values[i_iterate] -> i_cords_compare(piCords) < 0)
	{
		i_iterate++;
	}
	v_add(piCords, iValue, i_iterate);
}
void CSparseMatrix::v_add(int *piCords, int iValue, int iIndex)
{
	CSparseCell *pc_new_cell = new CSparseCell(iValue, piCords, i_number_of_dimensions);
	i_number_of_elements++;
	for (int i = i_number_of_elements; i > iIndex; i--)
	{
		pc_values[i] = pc_values[i-1];
	}
	pc_values[iIndex] = pc_new_cell;
}
void CSparseMatrix::v_delete_val(int *piCords,int iIndex)
{
	int iNextElement = 0;
	delete pc_values[iIndex];
	i_number_of_elements--;
	for (int i = iIndex; i<i_number_of_elements; i++)
	{
		pc_values[i] = pc_values[i+1];
	}
	if (i_values_table_length > I_DOUBLE_TABLE * i_number_of_elements && i_values_table_length > I_BASIC_TABLE_LENGTH)
	{
		cout << "short" << endl;
		v_change_table_length(false);
	}

}
int CSparseMatrix::i_get_value(int *piCords)
{
	int i_index = i_contains(piCords);
	if (i_index>= 0)
	{
		return pc_values[i_index]->i_value;
	}
	else
	{
		return i_basic_value;
	}
}

string CSparseMatrix::s_string_init()
{
	string s_result = S_SIZE;

	s_result += S_LBRACKET;
	for (int i = 0; i < i_number_of_dimensions; i++)
	{
		s_result += to_string(pi_ranges_in_dimensions[i]) + S_COMA;
	}
	s_result.replace(s_result.length() - 1, 1,S_RBRACKET);
	s_result += S_VALUES;
	return s_result;
}

string CSparseMatrix::s_attach_to_string(int *piActual)
{
	string s_result = S_LBRACKET;
	for (int i = 0; i < i_number_of_dimensions; i++)
	{
		s_result += to_string(piActual[i]) + S_COMA;
	}
	s_result.replace(s_result.length() - 1, 1, S_RBRACKET);
	s_result += S_DOUBLEDOT + to_string(i_get_value(piActual)) + S_SEMICOLON;
	return s_result;
}

std::string CSparseMatrix::s_ranges_to_string()
{
	string s_result = S_LBRACKET;
	for (int i = 0; i < i_number_of_dimensions; i++)
	{
		s_result += to_string(pi_ranges_in_dimensions[i]) + S_COMA;
	}
	s_result.replace(s_result.length() - 1, 1, S_RBRACKET);
	return s_result + S_END_LINE;
}

bool CSparseMatrix::b_normalize(int *piActual, int iGuard)
{
	bool b_in_defined_borders = true; //in borders means i_number_of_dimensions>i_helper
	int i_helper = 0;
	while (b_in_defined_borders && piActual[iGuard - i_helper] == pi_ranges_in_dimensions[iGuard - i_helper])
	{
		piActual[iGuard - i_helper] = 0;
		i_helper++;
		if (i_helper < i_number_of_dimensions)
		{
			piActual[iGuard - i_helper]++;
		}
		else
		{
			b_in_defined_borders = false;
		}
	}
	return b_in_defined_borders;
}



