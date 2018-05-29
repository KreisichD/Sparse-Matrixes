#pragma once
#include <string>
#include <vector>
#include "constants.h"
#include "CSparseMatrix.h"
#include "interface.h"

using namespace std;

const int I_SINGLE_ELEMENT = 1;

class CSparseMatrixManager {
public:
	CSparseMatrixManager();
	~CSparseMatrixManager();

	void vRun();
	
private:
	vector <CSparseMatrix*> *pv_matrix_container;
	int i_error_id;
	CInterface *pc_interface;

	void v_do_instruction(int iInstructionId);
	void v_get_mat_off(int *piMatOff);
	void v_rename();
	void v_clone();
	void v_print();
	void v_def();
	void v_del_all();
	void v_del_elem();
	void v_list();
	void v_add_mat();
	bool b_check_offset(int iMatOff);
	bool b_check_tail();

};