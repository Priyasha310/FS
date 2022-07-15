#include<stdio.h>
#include<curses.h>
#include<iostream>
#include<fstream>
#include<stdlib.h>
#include<string.h>

#define k 8

using namespace std;
//function to open a file in different mode
void opener(fstream &file, char *fn, ios_base::openmode mode)
{
  file.open(fn,mode);
  if(!file)
  {
  cout<<"unable to open the file \n";
  getch();
  exit(1);
  }
}

//main program
int main()
{
  fstream list[8], outfile;
  char name[8][20]={"name0.txt","name1.txt","name2.txt","name3.txt","name4.txt","name5.txt","name6.txt","name7.txt"};
  char item[8][20],min[20]="";
  int i,count=0;
  for(i=0;i<k;i++)
  opener(list[i],name[i],ios::in);
  opener(outfile,"merge8.txt",ios::out);
  for(i=0;i<k;i++)
  {
  list[i].getline(item[i],20,'\n');
  if(list[i].eof())
  count++;
  }
  cout<< "the names after merging using k-way merge algorithm\n";
  while(count<k)
  {
  strcpy(min,"") ;
  for(i=0;i<k;i++)
  if(!list[i].eof())
  {
  strcpy(min,item[i]) ;
  break;
  }
  count=0;
  for(i=0;i<k;i++)
  {
  if(list[i].eof())
  count++;
  else if(strcmp(item[i],min)<0)
  strcpy(min,item[i]);
  }
  if(count==8)break;

  outfile<<min<<"\n";
  cout<<min<<"\n";
  for(i=0;i<k;i++)
  if(strcmp(item[i],min)==0)
  list[i].getline(item[i],20,'\n');
  }
  for(i=0;i<8;i++)
  list[i].close();
  getch();
  return 0;
}
