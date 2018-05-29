#include "CSparseMatrixManager.h"

CSparseMatrixManager::CSparseMatrixManager()
{
	pc_interface = new CInterface();
	i_error_id = I_NO_ERROR;
	pv_matrix_container = new vector<CSparseMatrix*>();
}
CSparseMatrixManager::~CSparseMatrixManager()
{
	delete pc_interface;
	for (unsigned int i = 0; i < pv_matrix_container->size(); i++)
	{
		delete pv_matrix_container->at(i);
	}
	delete pv_matrix_container;
}
void CSparseMatrixManager::vRun()
{
	bool b_end = false;
	int i_instruction_id;
	while (!b_end)
	{
		i_error_id = I_NO_ERROR;
		pc_interface->vReadNext();
		i_error_id = pc_interface->iGetInstruction(i_instruction_id);
		if (i_error_id == I_NO_ERROR)
		{
			v_do_instruction(i_instruction_id);
		}
		pc_interface->vPrintError(i_error_id);
		if (i_instruction_id == I_QUIT)
		{
			b_end = true;
		}
	}
}
void CSparseMatrixManager::v_do_instruction(int iInstructionId)
{
	switch (iInstructionId)
	{
		case I_ADDMAT : 
			v_add_mat();
			break;
		case I_LIST :
			v_list();
			break;
		case I_DEL :
			v_del_elem();
			break;
		case I_DELALL :
			v_del_all();
			break;
		case I_DEF :
			v_def();
			break;
		case I_PRINT :
			v_print();
			break;
		case I_CLONE :
			v_clone();
			break;
		case I_RENAME :
			v_rename();
			break;
	}
}
void CSparseMatrixManager::v_get_mat_off(int *piMatOff)
{
	i_error_id = pc_interface->iGetArguments(1, piMatOff);
}
void CSparseMatrixManager::v_rename()
{
	int pi_mat_off[I_SINGLE_ELEMENT];
	string s_new_name;
	v_get_mat_off(pi_mat_off);
	if (i_error_id == I_NO_ERROR && b_check_offset(pi_mat_off[0]))
	{
		s_new_name = pc_interface->sGetString();		
		if (b_check_tail())
		{
			pv_matrix_container->at(pi_mat_off[0])->vSetName(s_new_name);
		}
	}
	else if (i_error_id == I_NO_ERROR)
	{
		i_error_id = I_NO_SUCH_MATRIX;
	}
}
void CSparseMatrixManager::v_clone()
{
	int pi_mat_off[I_SINGLE_ELEMENT];
	v_get_mat_off(pi_mat_off);
	CSparseMatrix *pc_clone;
	if (i_error_id == I_NO_ERROR && b_check_offset(pi_mat_off[0]))
	{
		if (b_check_tail())
		{
			pc_clone = new CSparseMatrix (*(pv_matrix_container->at(pi_mat_off[0])));
			pv_matrix_container->push_back(pc_clone);
		}
	}
	else if(i_error_id == I_NO_ERROR)
	{
		i_error_id = I_NO_SUCH_MATRIX;
	}
}
void CSparseMatrixManager::v_print()
{
	int pi_mat_off[I_SINGLE_ELEMENT];
	v_get_mat_off(pi_mat_off);
	if (i_error_id == I_NO_ERROR && b_check_offset(pi_mat_off[0]))
	{
		if (b_check_tail())
		{
			pc_interface->vPrint(pv_matrix_container->at(pi_mat_off[0])->sToString()+"\n");
		}
	}
	else if (i_error_id == I_NO_ERROR)
	{
		i_error_id = I_NO_SUCH_MATRIX;
	}
}
void CSparseMatrixManager::v_def()
{
	int pi_mat_off[I_SINGLE_ELEMENT];
	int pi_value[I_SINGLE_ELEMENT];
	v_get_mat_off(pi_mat_off);
	int *pi_cords;
	int i_number;
	if (i_error_id == I_NO_ERROR && b_check_offset(pi_mat_off[0]))
	{
		i_number = pv_matrix_container->at(pi_mat_off[0])->iGetNumberOfDimensions();
		pi_cords = new int[i_number];
		i_error_id = pc_interface->iGetArguments(i_number, pi_cords);
		i_error_id = pc_interface->iGetArguments(1, pi_value);
		if (b_check_tail() && i_error_id == I_NO_ERROR)
		{
			i_error_id = pv_matrix_container->at(pi_mat_off[0])->iAddValue(pi_cords, pi_value[0]);
		}
		else
		{
			delete [] pi_cords;
		}
	}
	else if (i_error_id == I_NO_ERROR)
	{
		i_error_id = I_NO_SUCH_MATRIX;
	}
}
void CSparseMatrixManager::v_del_all()
{
	for (int i = 0; i < pv_matrix_container->size(); i++)
	{
		delete pv_matrix_container->at(i);
	}
	pv_matrix_container->clear();
}
void CSparseMatrixManager::v_del_elem()
{
	int pi_mat_off[I_SINGLE_ELEMENT];
	v_get_mat_off(pi_mat_off);
	if (i_error_id == I_NO_ERROR && b_check_offset(pi_mat_off[0]))
	{
		if (b_check_tail())
		{
			delete pv_matrix_container->at(pi_mat_off[0]);
			pv_matrix_container -> erase(pv_matrix_container -> begin() + pi_mat_off[0]);
		}
	}
	else if (i_error_id == I_NO_ERROR)
	{
		i_error_id = I_NO_SUCH_MATRIX;
	}
}
void CSparseMatrixManager::v_list()
{
	if (b_check_tail())
	{
		string result = to_string(pv_matrix_container->size()) + S_MATRICES;
		for (int i = 0; i < pv_matrix_container->size(); i++)
		{
			result += S_LBRACKET + to_string(i) + S_RBRACKET + S_HYPHEN + pv_matrix_container->at(i)->sGetName()
				+ SPACE + S_SIZE + pv_matrix_container->at(i)->sGetDimRange();
		}
		cout << result << endl;
	}
}
void CSparseMatrixManager::v_add_mat()
{
	int pi_nr_of_dim[I_SINGLE_ELEMENT];
	int pi_basic_val[I_SINGLE_ELEMENT];
	int *pi_ranges;
	string s_name;
	CSparseMatrix *pc_matrix;
	i_error_id = pc_interface -> iGetArguments(I_SINGLE_ELEMENT, pi_nr_of_dim);
	int i_number = pi_nr_of_dim[0];
	if (i_error_id == I_NO_ERROR && i_number > 0)
	{
		pi_ranges = new int[i_number];
		i_error_id = pc_interface -> iGetArguments(i_number, pi_ranges);
		i_error_id = pc_interface -> iGetArguments(I_SINGLE_ELEMENT, pi_basic_val);
		s_name = pc_interface -> sGetString();
		if (s_name == S_EMPTY && i_error_id == I_NO_ERROR)
		{
			pc_matrix = new CSparseMatrix();
			i_error_id = pc_matrix -> iInitialize(pi_basic_val[0], i_number, pi_ranges);
			if (i_error_id == I_NO_ERROR)
			{
				pv_matrix_container->push_back(pc_matrix);
			}
			else
			{
				delete pc_matrix;
				delete[] pi_ranges;
			}
		}
		else if (b_check_tail() && i_error_id == I_NO_ERROR)
		{
			pc_matrix = new CSparseMatrix(s_name);
			i_error_id = pc_matrix->iInitialize(pi_basic_val[0], i_number, pi_ranges);
			if (i_error_id == I_NO_ERROR)
			{
				pv_matrix_container->push_back(pc_matrix);
			}
			else
			{
				delete pc_matrix;
				delete[] pi_ranges;
			}
		}
		else
		{
			delete [] pi_ranges;
		}
	}
	else if (i_error_id == I_NO_ERROR)
	{
		i_error_id = I_ERROR_DIM;
	}
}

bool CSparseMatrixManager::b_check_offset(int iMatOff)
{
	int i_size = pv_matrix_container->size();
	return iMatOff >= 0 && iMatOff < i_size;
}
bool CSparseMatrixManager::b_check_tail()
{
	if (pc_interface->sGetString() == S_EMPTY)
	{
		return true;
	}
	else
	{
		i_error_id = I_WRONG_ARGUMETS;
		return false;
	}
}


