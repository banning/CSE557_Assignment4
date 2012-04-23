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

// Define matrix struct
struct matrix
{
	vector<int> row;
	vector<int> col;
	vector<double> val;
	int n;
	int num;
};

int main(int argc, const char* argv[])
{
	// Verify arguements
	if (argc <2)
	{
		cout<<"Correct format is ./matrixsum inputfile.csr"<<endl;
		return 0;
	}

	// Allocate variables
	string line;
	matrix A;
	int last=0;
	ifstream myFile(argv[1]);

	// Read from input file
	if (myFile.is_open())
	{
		//gets rid of documentation line
		getline(myFile, line);
		getline(myFile, line);
		int space = line.find_first_of(" ");

		A.n = atoi(line.substr(0, space).c_str());
		A.num = atoi(line.substr(space+1, line.length()-space).c_str());

		while (myFile.good())
		{
			getline(myFile, line);
			space = atoi(line.c_str());

			if (space < last && last != 0)
			{
				A.col.push_back(space);
				break;
			}

			last=space;
			A.row.push_back(space);
		}

		for (int i = 0; i < A.num-1; i++)
		{
			getline(myFile, line);
			space=atoi(line.c_str());
			A.col.push_back(space);
		}

		for (int i = 0; i < A.num; i++)
		{
			getline(myFile, line);
			double val=atof(line.c_str());
			A.val.push_back(val);
		}
	}

	// cout<<"Values"<<endl;
	// for (int i = 0; i < A.num; i++)
	// {
	// 	cout<<A.val.at(i)<<'\t';
	// }
	// cout<<endl;
	
	// Define other matrix for multiplication
	int x[A.n];
	double y[A.n];
	for (int i = 0;  i < A.num; i++)
	{
		x[i]=1;
	}

	// Calculate the sum
	double sum;
	cout<<"Running sum now"<<endl;
	for (int i = 0; i < A.n; i++)
	{
		sum = 0.0;  
		cout<<"J goes from "<<A.row.at(i)<< " to " <<A.row.at(i+1)-1<<endl;
		for (int j = A.row.at(i)-1; j <  A.row.at(i+1)-1; j++)
		{
			double Xi = x[A.col.at(j)];
			double Ai = A.val.at(j);
			sum = sum + Ai*Xi;
		}
		y[i]=sum;
	}

	// Output the resulting vector
	for (int i = 0; i < A.n; i++)
	{
		cout <<"y["<<i<<"] = "<<y[i]<<endl;
	}
	return 0;
} 