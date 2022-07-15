/* Write a program to implement simple index on primary key for a file of student objects. Implement 
add ( ), search ( ), delete ( ) using the index. */
#include<iostream>
#include<fstream>
#include<curses.h>
#include<stdio.h>
#include<iomanip>
#include<stdlib.h>
#include<string.h>
using namespace std;
#define max 10
#define datafile "student5.txt"
#define indexfile "index5.txt"
fstream stdfile, indfile;
int i,indsize;
char buffer[80];
class Student
{
char dusn[15],name[20],age[5],branch[5],sem[5];
public:
void read();
void pack();
friend int search(char*);
void recDisp(int);
void remove(int);
void dataDisp();
void unpack();
};
class index
{
public:
char iusn[15],addr[5];
void initial();
void write();
}in,id[max];
void index::initial()
{
indfile.open(indexfile,ios::in);
if(!indfile)
{
indsize=0;
return;
}
for(indsize=0;;indsize++)
{
indfile.getline(id[indsize].iusn,15,'|');
indfile.getline(id[indsize].addr,5,'\n');
if(indfile.eof())
break;
}
indfile.close();
}

// function to open file
void opener(fstream &sfile,char* fn,ios_base::openmode mode)
{
sfile.open(fn,mode);
if(!sfile)
{
cout<<"Unable to open the file\n";
exit(1);
}
}
// function to write
void index::write()
{
opener(indfile,indexfile,ios::out);
for(i=0;i<indsize;i++)
indfile<<id[i].iusn<<"|"<<id[i].addr<<"\n";
indfile.close();
}
int search(char* fusn)
{
int low=0,high=indsize-1;
int mid;
while(low<=high)
{
mid=(low+high)/2;
if(strcmp(fusn,id[mid].iusn)==0)
return mid;
else if(strcmp(fusn,id[mid].iusn)>0)
low=mid+1;
else
high=mid-1;
}
return -1;
}
// function to read
void Student::read()
{
cout<<"Enter the usn no.\n";
scanf("%s",dusn);
if(search(dusn)>=0)
{
cout<<"usn is already present,we can't add to index file\n";
return;
}
for(i=indsize;i>0;i--)
{
if(strcmp(dusn,id[i-1].iusn)<0)
id[i]=id[i-1];
else
break;
}
opener(stdfile,datafile,ios::app);
cout<<"Enter the Name\n";
scanf("%s",name);

cout<<"Enter the age\n";
scanf("%s",age);
cout<<"Enter the branch\n";
scanf("%s",branch);
cout<<"Enter the semester\n";
scanf("%s",sem);
pack();
stdfile.seekg(0,ios::end);
int k=stdfile.tellg();
stdfile<<buffer<<endl;
strcpy(id[i].iusn,dusn);
sprintf(id[i].addr,"%d",k);
indsize++;
}
// function to pack
void Student::pack()
{
strcpy(buffer,dusn); strcat(buffer,"|");
strcat(buffer,name); strcat(buffer,"|");
strcat(buffer,age); strcat(buffer,"|");
strcat(buffer,branch); strcat(buffer,"|");
strcat(buffer,sem); strcat(buffer,"|");
}
// function to record display
void Student::recDisp(int pos)
{
opener(stdfile,datafile,ios::in);
stdfile.seekg(atoi(id[pos].addr),ios::beg);
cout<<"The searched record details are:\n";
cout<<setw(16)<<"USN"<<setw(16)<<"Name"<<setw(16)<<"Age"<<setw(16)
<<"Branch"<<setw(16)<<"Sem"<<endl;
unpack();
}
// function to Remove
void Student::remove(int pos)
{
opener(stdfile,datafile,ios::in|ios::out);
stdfile.seekg(atoi(id[pos].addr),ios::beg);
stdfile.put('$');
for(i=pos;i<indsize;i++)
id[i]=id[i+1];
indsize--;
}
// function to data display
void Student::dataDisp()
{
cout<<setiosflags(ios::left);
cout<<setw(16)<<"USN"<<setw(16)<<"Name"<<setw(16)<<"Age" \
<<setw(16)<<"Branch"<<setw(16)<<"Sem"<<endl;
while(1)
{
unpack();
if(stdfile.eof())
break;
}
}
// function to unpack
void Student::unpack()
{
stdfile.getline(buffer,100,'\n');
i=0;
if(buffer[i]!='$')
{
cout<<"\n";
while(buffer[i]!='\0')
{
if(buffer[i]=='|')
cout<<"\t\t";
else
cout<<buffer[i];
i++;
}
}
}
int main()
{
int ch,pos,flag;
char susn[15];
Student S;
in.initial();
curscr;
for(;;)
{
cout<<endl<<"1.Read\n2.Display\n3.Search\n4.Delete\n5.exit\n";
cin>>ch;
switch(ch)
{
case 1: cout<<"Enter student details\n";
S.read();
in.write();
break;
case 2: opener(stdfile,datafile,ios::in);
cout<<endl<<"Student Details\n";
S.dataDisp();
cout<<endl<<"Index file details are:\n";
cout<<setw(10)<<"USN"<<setw(10)<<"Address";
for(i=0;i<indsize;i++)
{
cout<<endl<<setw(10)<<id[i].iusn<<setw(10)<<id[i].addr<<endl;
}
break;
case 3: cout<<"Enter the USN to be searched\n";
cin>>susn;
flag=search(susn);
if(flag==-1)
cout<<"Record Not found\n";
else
S.recDisp(flag);
break;
case 4: cout<<"Enter the usn no to delete from the record\n";
cin>>susn;
pos=search(susn);
if(pos==-1)
cout<<"Usn No. not found\n";
else
{
S.remove(pos);
in.write();
}
break;
default: exit(0);
}
stdfile.close();
}
return 0;
}
/*Output :
1 for rea d, 2 for dis pla y, 3 for s ea rch, 4 for delet e, 5 for e xit
1
enter s tudent deta ils :
enter the us n number= is 101
enter the na me= ma noj kuma r
enter the a ge= 25
enter the bra nch= is e
enter the s emet er= 6
1 for rea d, 2 for dis pla y, 3 for s ea rch, 4 for delet e, 5 for e xit
2
the s tudent deta ils a re
us n na me a ge branch s em
is 101 ma noj kuma r 25 is e 6
the index file deta ils a re
us n a ddress
is 101 0
1 for rea d, 2 for dis pla y, 3 for s ea rch, 4 for delet e, 5 for e xit
1
enter s tudent deta ils :
enter the us n number= cs 201
enter the na me= vikra m na ra ya n
enter the a ge= 35
enter the bra nch= cs e
enter the s emet er= 8
1 for rea d, 2 for dis pla y, 3 for s ea rch, 4 for delet e, 5 for e xit
2
the s tudent deta ils a re
us n na me a ge bra nch s em
is 101 ma noj kuma r 25 is e 6
cs 201 vikra m na ra ya n 35 cs e 8
the index file deta ils a re
us n a ddress
cs 201 29
is 101 0
1 for rea d, 2 for dis pla y, 3 for s ea rch, 4 for delet e, 5 for e xit
FS LAB MANUAL 2022
Page 
23
1
enter s tudent deta ils :
enter the us n number= me301
enter the na me= pra deep
enter the a ge= 24
enter the bra nch= mec
enter the s emet er= 7
1 for rea d, 2 for dis pla y, 3 for s ea rch, 4 for delet e, 5 for e xit
1
enter s tudent deta ils :
enter the us n number= e e401
enter the na me= s hruthi
enter the a ge= 20
enter the bra nch= eee
enter the s emet er= 6
1 for rea d, 2 for dis pla y, 3 for s ea rch, 4 for delet e, 5 for e xit
1
enter s tudent deta ils :
enter the us n number= it501
enter the na me= s unitha
enter the a ge= it
enter the bra nch= it
enter the s emet er= 6
1 for rea d, 2 for dis pla y, 3 for s ea rch, 4 for delet e, 5 for e xit
2
the s tudent deta ils a re
us n na me a ge bra nch s em
is 101 ma noj kuma r 25 is e 6
cs 201 vikra m na ra ya n 35 cs e 8
me301 pra deep 24 mec 7
ee401 shruthi 20 eee 6
it501 s unitha 21 it 6
the index file deta ils a re
us n a ddress
cs 201 29
ee401 86
is 101 0
it501 111
me301 61
1 for rea d, 2 for dis pla y, 3 for s ea rch, 4 for delet e, 5 for e xit
3
enter us n number to s ea rch : me301
us n = me301
na me = pra deep
a ge = 24
bra nch = mec
s em = 7
1 for rea d, 2 for dis pla y, 3 for s ea rch, 4 for delet e, 5 for e xit
3
enter us n number to s ea rch : ec250
us n number rec ord not found for s ea rch
1 for rea d, 2 for dis pla y, 3 for s ea rch, 4 for delet e, 5 for e xit
4
enter us n number to delete the r ec ord : me301

1 for rea d, 2 for dis pla y, 3 for s ea rch, 4 for delet e, 5 for e xit
2
the s tudent deta ils a re
us n na me a ge bra nch s em
is 101 ma noj kuma r 25 is e 6
cs 201 vikra m na ra ya n 35 cs e 8
ee401 s hruthi 20 eee 6
it501 sunitha 21 it 6
the index file deta ils a re
us n a ddress
cs 201 29
ee401 86
is 101 0
it501 111
1 for rea d, 2 for dis pla y, 3 for s ea rch , 4 for delet e, 5 for e xit
4
enter us n number to delete the r ec ord : c v105
us n number not found to delet e
1 for rea d, 2 for dis pla y, 3 for s ea rch, 4 for delet e, 5 for e xit
5
C :\tc\typ es td5.txt
is 101|ma noj kuma r|25|is e|6|
cs 201|vikra m na ra ya n|35|cs e|8|
$e301|pra deep|24|mec|7|
ee401|s hruthi|20|eee|6|
it501|s unitha |21|it|6|
c:\tc\t yoe index5.t xt
cs 201|29
ee401|86
is 101|0
it501|111
*/


Program 7
/* Write a program to read two lists of names and then match the names in the two lists using 
consequential Match based on a single loop. Output the names common to both the files */
#include<stdio.h>
#include<iostream>
#include<curses.h>
#include<stdlib.h>
#include<fstream>
#include<string.h>
using namespace std;
//function to open a file in different mode
void opener(fstream &file, char *fn,ios_base::openmode mode)
{
file.open(fn,mode);
if(!file)
{
cout<<"unable to open the file \n ";
getch();
exit(1);
}
}
//function to match the common names from two files
void match(fstream &file1 ,fstream &file2 ,fstream &ofile)
{
char s1[25] ,s2[25];
file1.getline(s1,25,'\n');
file2.getline(s2,25,'\n');
while(!file1.eof() && !file2.eof())
{
if(strcmp(s1,s2)== 0)
{
FS LAB MANUAL 2022
Page 
32
ofile<<s1<<"\n";
cout<<s1<<endl;
file1.getline(s1,25,'\n');
file2.getline(s2,25,'\n');
}
else if(strcmp(s1,s2)<0)
file1.getline(s1,25,'\n');
else
file2.getline(s2,25,'\n');
}
}
//main program
int main()
{
fstream list1,list2,outlist;
curscr;
opener(list1,"name1.txt",ios::in);
opener(list2,"name2.txt",ios::in);
opener(outlist,"names.txt",ios::out);
match(list1,list2,outlist);
cout<<"name1.txt & name2.txt matching names in names.txt\n";
list1.close();
list2.close();
outlist.close();
getch();
return 0;
}
NOTE: In file name1.txt and name2.txt
Names should be in ascending order
OUTPUT:
names1.txt
navnish
pavan
sharath
sagar
vallish
names2.txt
navnish
niranjan
pavan
puneeth
sharath
sagar
output.txt
name1.txt & name2.txt matching names in names.txt
na vnis h
pa va n
s ha ra th
s a ga r
Program 8
/*Write a program to read k Lists of names and merge them using k-way merge algorithm with k = 8. */
FS LAB MANUAL 2022
Page 
33
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
FS LAB MANUAL 2022
Page 
34
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
OUTPUT
N ame 0.txt
A ka rsh
*
N ame 2.txt
N a vnis h
Pa va n
*
N ame 3.txt
N a vnis h
Sha ra th
*
N ame 4.txt
Sha ra th
Srinidhi
*
Name 5 .txt
Srinidhi
V a llis h
*
Name 6 .txt
V a llis h
*
Name 7 .txt
*
M e rge 8.txt
A ka rsh
A nura g
N a vnis h
Pa va n
Sha ra th
Srinidhi
V a llis 
