#include <string>
#include <iostream>
#include "CSparseMatrix.h"
#include "CSparseMatrixManager.h"

using namespace std;

int main()
{
	//int *pi_ranges = new int[3];
	//	pi_ranges[0] = 2;
	//	pi_ranges[1] = 1;
	//	pi_ranges[2] = 3;
	//CSparseMatrix x("master");
	//CSparseMatrix *y;
	//x.iInitialize(1, 3, pi_ranges);

	//int *pi_ranges1 = new int[3];
	//pi_ranges1[0] = 0;
	//pi_ranges1[1] = 0;
	//pi_ranges1[2] = 0;
	//x.iAddValue(pi_ranges1, 5);

	//int *pi_ranges2 = new int[3];
	//pi_ranges2[0] = 1;
	//pi_ranges2[1] = 0;
	//pi_ranges2[2] = 2;
	//x.iAddValue(pi_ranges2, 17);

	//y = new CSparseMatrix(x);

	//int *pi_ranges3 = new int[3];
	//pi_ranges3[0] = 1;
	//pi_ranges3[1] = 0;
	//pi_ranges3[2] = 2;
	//y->iAddValue(pi_ranges3, 631);

	//cout << x.sToString() << endl;

	//cout << y->sToString() << endl;
	//
	//delete y;

	//cout << x.sToString() << endl;

	CSparseMatrixManager x;
	x.vRun();

	return 0;
}