#include <bits/stdc++.h>
using namespace std;
  int main()
{
  // give no of variables then space then number of equations
  int no_of_var,no_of_equat;
  cin>>no_of_var>>no_of_equat;
  vector<vector<float>>mat(no_of_equat,vector<float>(no_of_var+1));

  //Enter each equation line by line(also enter the constant term of the equation)
  for(int i=0;i<no_of_equat;i++)
  for(int j=0;j<no_of_var+1;j++)
  cin>>mat[i][j]; 

  // now we have to solve the system of equations(but assume well defined solution)
  //the downfall
  for(int i=0;i<no_of_equat-1;i++)//selecting the main row
  {
    if(mat[i][i]==0)// swapping need check
    {
      for(int l=i+1;l<no_of_equat;l++)
      if(mat[l][i]!=0)
      {
        for(int z=0;z<no_of_var+1;z++)
        {
          swap(mat[i][z],mat[l][z]);
        }
      }
    }
  for(int j=i+1;j<no_of_equat;j++)// selecting its lower rows
  {
    float factor = mat[j][i]/mat[i][i];
    for(int z=0;z<no_of_var+1;z++)
    {
      mat[j][z]=mat[j][z]-factor*mat[i][z];
    }
  }
  }
  //the uprise
  for(int i=no_of_equat-1;i>=0;i--)
  {
    for(int j=i-1;j>=0;j--)
    {
      float factor=mat[j][i]/mat[i][i];
      mat[j][i]=0;
      mat[j][no_of_var]-=factor*mat[i][no_of_var]; 
    }
  }

  //output of matrix
  // for(int i=0;i<no_of_equat;i++)
  // {
  // for(int j=0;j<no_of_var+1;j++)
  // {
  //   cout<<mat[i][j]<<" ";
  // }
  // cout<<"\n";
  // }
  
  //final answer
  for(int i=0;i<no_of_var;i++)cout<<mat[i][no_of_var]/mat[i][i]<<" | ";
  return 0;
}
