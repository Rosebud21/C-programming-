#include <stdio.h>
#include <stdlib.h>
void populateArray(int stu[][11]);
void sortRows(int stu[][11]);
void sort(int stu[][11],int k);
int main()
{
     int stu[5][11];
     
     populateArray(stu);
     sortRows(stu);

     for(int i=0;i<5;i++)
  {
      for(int j=0;j<11;j++)
      {
        printf("%d ",stu[i][j]);
      }
      printf("\n");
  }
    return 0;

}
void populateArray(int stu[][11])
{
  FILE* input;
  input = fopen("input2.txt", "r");
if(input == NULL)
   {
      printf("input2.txt not found");   
      exit(1);             
   }
  
  for(int i=0;i<5;i++)
  {
      for(int j=0;j<11;j++)
      {
           fscanf(input, "%d",&stu[i][j] );
           //printf("%d ",stu[i][j]);
      }
      //printf("\n");
  }

  
}

void sortRows(int stu[][11])
{
    for(int i=0;i<5;i++)
    {
        sort(stu,i);
    }
}

void sort(int stu[][11],int k)
{

    for (int i = 1; i < 11; ++i)
    {
    for (int j = i + 1; j < 11; ++j)
    {
      if (stu[k][i] > stu[k][j])
      {
         int a = stu[k][i];
         stu[k][i] = stu[k][j];
         stu[k][j] = a;
      }
    }
    }
}