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
	ifstream myFile(argv[1], ifstream::in);

	// Read from input file
	if (myFile.is_open())
	{
		//gets rid of documentation line
		getline(myFile, line);
		
		getline(myFile, line);
		int space = line.find_first_of(" ");

		A.n = atoi(line.substr(0, space).c_str());
		A.num = atoi(line.substr(space+1, line.length()-space).c_str());
cout<<A.n <<" " <<A.num <<endl;
		// while (myFile.good())
		// {
		// 	getline(myFile, line);
		// 	space = atoi(line.c_str());

		// 	if (space < last && last != 0)
		// 	{
		// 		A.col.push_back(space);
		// 		break;
		// 	}

		// 	last=space;
		// 	A.row.push_back(space);
		// }

		for (int i = 0; i < A.n+1; i++)
		{
			getline(myFile, line);
			space=atoi(line.c_str());
			A.row.push_back(space);
		}
		for (int i = 0; i < A.num; i++)
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
	
	// Define arrays for multiplication
	// int *x = new int[A.n];
	// double *y = new double[A.n];

	vector<int> x;
	vector<double> y;

	for (int i = 0;  i < A.n+1; i++)
	{
		x.push_back(1);
		//x[i]=1;
	}

//size
	cout<<"row "<<A.row.size() <<endl;
	cout<<"col "<<A.col.size() <<endl;
	cout<<"val "<<A.val.size() <<endl;
	cout<<"x "<<x.size() <<endl;
	cout<<"y "<<y.size() <<endl;


	// Calculate the sum
	double sum;
	cout<<"Running sum now"<<endl;
	for (int i = 0; i < A.n+1; i++)
	{
		sum = 0.0;
		//cout<<"J goes from "<<A.row.at(i)<< " to " <<A.row.at(i+1)-1<<endl;
		for (int j = A.row.at(i)-1; j <  A.row.at(i+1)-1; j++)
		{
			double Xi = x.at(A.col.at(j));
			double Ai = A.val.at(j);
			sum = sum + Ai*Xi;
		}
		y.push_back(sum);
		//y[i]=sum;
	}

	// Output the resulting vector
	for (int i = 0; i < y.size(); i++)
	{
		cout <<"y["<<i<<"] = "<<y.at(i)<<endl;
	}
	return 0;
} 