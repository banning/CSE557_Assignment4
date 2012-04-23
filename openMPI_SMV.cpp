#include <omp.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
using namespace std;
int main(int argc, const char* argv[])
{
<<<<<<< HEAD
   if (argc <2)
   {
      cout<<"Correct format is ./matrixsum inputfile.csr"<<endl;
      return 0;
   }
   string line;
   int n;
   int num;
   int last=0;
   ifstream myFile(argv[1]);
   if (myFile.is_open())
   {
      //gets rid of documentation line
      getline(myFile, line);
      getline(myFile, line);
      int space = line.find_first_of(" ");
      n = atoi(line.substr(0, space).c_str());
      num=atoi(line.substr(space+1, line.length()-space).c_str());
      int row[n+1];
      int col[num];
      double val[num];
      for (int i = 0; i < n+1; i++)
      {
         getline(myFile, line);
         row[i] = atoi(line.c_str());
      }
      for (int i = 0; i < num; i++)
      {
         getline(myFile, line);
         col[i]=atoi(line.c_str());
      }
      for (int i = 0; i < num; i++)
      {
         getline(myFile, line);
         val[i]=atof(line.c_str());
      }
      int x[n];
      double y[n];
      cout<<"N is "<<n<<endl;
      cout<<"Num is "<<num<<endl;
      for (int i = 0; i < num; i++)
      {
         x[i]=1;
         cout<<row[i]-1<<" ";
      }
      cout<<endl;
      double sum;
      time_t start, end;
      time(&start);
     // #pragma omp parallel for private(sum) schedule(static) 
      for (int i = 0; i < n; i++)
      {
         double sum = 0.0;
         for (int j = row[i]-1; j < row[i+1]-1; j++)
         {
            cout<<"Attempting to find col[j]="<<col[j]<< " from "<<j<<endl;
            double Xi = x[col[j]];
            double Ai = val[j];
            sum = sum + Ai*Xi;
         }
         y[i]=sum;
      }
      cout<<"end"<<endl;
      time(&end);
      double diff = difftime(start, end);
      cout<<"The time to run was"<<diff<<endl;
   }
   return 0;
=======
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
	
	// Define arrays for multiplication
	// int *x = new int[A.n];
	// double *y = new double[A.n];

	vector<int> x;
	vector<double> y;

	for (int i = 0;  i < A.n; i++)
	{
		x.push_back(1);
		//x[i]=1;
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
>>>>>>> Tried using vectors
} 