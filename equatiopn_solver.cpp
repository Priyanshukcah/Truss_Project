vector<double>eqn_solver(int no_of_var,int no_of_equat, vector<vector<double>>mat)
{
  (but assume well defined solution)
  //the downfall
  for(int i=0;i<no_of_equat-1;i++)//selecting the main row
  {
    //always the largest should be taken
      double maxi=abs(mat[i][i]);
      int ind =i;
      for(int l=i+1;l<no_of_equat;l++)
      {
        if(maxi<abs(mat[l][i]))
        {
            maxi=abs(mat[l][i]);
            ind=l;
        }
      }
      // swapping to ensure blow up does not happen  
      for(int z=0;z<no_of_var+1;z++)
        {
          swap(mat[i][z],mat[ind][z]);
        }
      
  for(int j=i+1;j<no_of_equat;j++)// selecting its lower rows
  {
    double factor = mat[j][i]/mat[i][i];
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
      double factor=mat[j][i]/mat[i][i];
      mat[j][i]=0;
      mat[j][no_of_var]-=factor*mat[i][no_of_var]; 
    }
  }
  vector<double>ans(no_of_var);
  //final answer
  for(int i=0;i<no_of_var;i++)ans[i]=mat[i][no_of_var]/mat[i][i];;
  return ans;
}
