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
      for (int i = 0; i < num; i++)
      {
         x[i]=1;
      }
      double sum;
      time_t start, end;
  
      time(&start);
      //#pragma omp parallel for private(sum) schedule(static) 
      for (int i = 0; i < n; i++)
      {
         sum = 0.0;
         for (int j = row[i]-1; j < row[i+1]-1; j++)
         {
            double Xi = x[col[j]];
            double Ai = val[j];
            sum = sum + Ai*Xi;
         }
         y[i]=sum;
      }
      time(&end);
      double diff = difftime(start, end);
      cout<<"The time to run was"<<diff<<endl;
   }
   return 0;
} 