// CSE557 Assignment 4
// Calculate SMV with openMPI
// 04/27/12
// Mike Banning
// Dan Keating

#include <omp.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

int main(int argc, const char* argv[])
{
	// Verify arguements
	if (argc <2)
	{
		cout<<"Correct format is ./matrixsum inputfile.csr"<<endl;
		return 0;
	}

// Begin code from mwm126 to load mtx file directly
	FILE *input = fopen(argv[1], "rb");

	char* line = NULL;
	size_t line_sz;

	do {
		if (-1==getline(&line,&line_sz,input)) {
		  perror("Error reading input\n");
		  exit(0);
		}
	} while (line[0]=='%');

	int rows = 0;
	int cols = 0;
	int vals = 0;
	sscanf(line, "%d %d %d", &rows, &cols, &vals); // read header line

	int x[cols];
	double y[rows];

	int A_row[rows];
	int A_col[vals];
	double A_val[vals];

	for (int i = 0; i < rows; i++)
		A_row[i] = 0;

	for (int i = 0; i < vals; i++)
		A_col[i] = 0;

	for (int i = 0; i < vals; i++)
		A_val[i] = 0;

	int row,col;
	int val=1;  // use 1 as an arbitrary value
	int limit=0;

	int row_idx = -1;
	int col_idx = 0;
	double* val_p = A_val;

	while (2==fscanf(input, "%d %d", &col, &row)) {
	// while (3==fscanf(input, "%d %d %g", &col, &row, &val)) { // recompile for shipsec
		col--; // index from zero, not one 
		row--; // index from zero, not one

		if (row_idx < row) {
		  row_idx++;
		  A_row[row_idx] = col_idx;
		} else if (row < row_idx) {
		  printf("Error with input, rows not monotonically increasing\n");
		  exit(-1);
		} else if (col < A_col[col_idx]) {
		  printf("Error with input, columns not monotonically increasing within a row\n");
		  exit(-1);
		}
		A_col[col_idx] = col;
		col_idx++;
		val_p++;
		(*val_p) = val;

	}
// End code from mwm126

	// Calculate the sum
	double sum;
	double begin = omp_get_wtime();
  	#pragma omp parallel for schedule(static)
	for (int i = 0; i < rows; i++)
	{
		sum = 0.0;
		for (int j = A_row[i]; j <  A_row[i+1]; j++)
		{
			double Xi = x[A_col[j]];
			double Ai = A_val[j];
			sum = sum + Ai*Xi;
		}
		y[i]=sum;
	}
	double end = omp_get_wtime();
	cout <<"Time to calculate:" <<end - begin <<endl;

	// // Output the resulting vector
	// for (int i = 0; i < rows; i++)
	// {
	// 	cout <<"y["<<i<<"] = "<<y[i]<<endl;
	// }

	return 0;
} 