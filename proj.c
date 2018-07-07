#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct node
{
char name[50];
char dept[30];
float sal;
int age;
int empid;
struct node *link;
}*start,*visit,*qnew;
struct emp
{
char name[50];
char dept[30];
float sal;
int age;
int empid;
}tmp;
FILE *fptr,*p,*t;
void append(struct node **,char*,char*,float,int,int);
void addatbeg(struct node **,char*,char*,float,int,int);
void addafter(struct node *,char*,char*,float,int,int,int);
void display(struct node *);
int count(struct node *);
void del(struct node **,int);
void search(struct node *,int);
void displaylist();
void selection_sort(int);
void displaydept(struct node *,char *);
void birthday(struct node *,int);
void deptchange(struct node *,int,char*);
void salarychange(struct node *,int,float);
void searchname(struct node *,char *);
int main()
{
struct node *p;
char name[50],dept[30],deptchoice[30],newdept[30],namesearch[50];
float sal,raise;
int choice=0,age,empid,loc,id,choice2,n,em,choice3;
p=NULL;
fptr=fopen("text.txt","a");
while(choice!=8)
{
printf("What would you like to do?\n");
printf("Press\n1.Hire an employee\n2.Display\n3.No of emplyees in company\n4.Fire an employee\n5.Search for an employee\n6.Sort based on salary\n7.Update employee info\n8.Exit");
scanf("%d",&choice);
switch(choice)
{
case 1: printf("Enter employee info:\n");
printf("Name: ");
scanf("%s",name);
printf("\nDepartment: ");
scanf("%s",dept);
printf("\nSalary: ");
scanf("%f",&sal);
printf("\nAge: ");
scanf("%d",&age);
printf("\nEmployee ID: ");
scanf("%d",&empid);
fprintf(fptr,"%s\t",name);
fprintf(fptr,"%s\t",dept);
fprintf(fptr,"%f\t",sal);
fprintf(fptr,"%d\t",age);
fprintf(fptr,"%d\n",empid);
printf("\nWhere would to like to place your new employee?\n");
printf("1.At the end\n2.At the beginning\n3.Add after position\n");
scanf("%d",&choice2);
switch(choice2)
{
case 1: append(&p,name,dept,sal,age,empid);
start=p;
break;
case 2: addatbeg(&p,name,dept,sal,age,empid);
start=p;
break;
case 3: printf("\nAt what position would you like employee to be stored?\t");
scanf("%d",&loc);
addafter(p,name,dept,sal,age,empid,loc);
start=p;
break;
}
break;
printf("\n");
case 2: printf("Display:\n");
printf("1.All Employees\n2.Employees of a department\n");
scanf("%d",&em);
switch(em)
{
case 1: display(p);
break;
case 2: printf("Which department would you like to see?");
scanf("%s",deptchoice);
displaydept(p,deptchoice);
break;
}
printf("\n");
break;
case 3: printf("\nNo. of employees:%d",count(p));
printf("\n");
break;
case 4: printf("What is employee ID of the employee to be fired?");
scanf("%d",&id);
del(&p,id);
printf("\n");
break;
case 5: printf("Search by:\n");
printf("1.ID\n2.Name\n");
scanf("%d",&choice3);
switch(choice3)
{
case 1: printf("\nWhat is the employee ID?\t");
scanf("%d",&id);
search(p,id);
printf("\n");
break;
case 2: printf("\nWhat is name of employee to be searched?\t");scanf("%s",namesearch);
searchname(p,namesearch);
printf("\n");
break;
}
break;
case 6: n=count(start);
selection_sort(n);
displaylist();
break;
case 7: printf("\nID of employee whose info is to be updated: ");
scanf("%d",&id);
printf("\nWhat would you like to do: ");
printf("1.Birthday\n2.Change department\n3.Give a raise");
scanf("%d",&choice3);
switch(choice3)
{
case 1: birthday(p,id);
break;
case 2: printf("What is the new department?\n");
scanf("%s",newdept);
deptchange(p,id,newdept);
break;
case 3: printf("How much raise?\n");
scanf("%f",&raise);
printf("raise is:%f",raise);
salarychange(p,id,raise);
break;
}
break;
case 8: fclose(fptr);
exit(1);
break;
}
}
}
void append(struct node **q,char *name,char *dept,float sal,int age,int empid)
{
struct node *temp,*r;
if(*q==NULL)
{
temp=malloc(sizeof(struct node));
strcpy(temp->name,name);
strcpy(temp->dept,dept);
temp->sal=sal;
temp->age=age;
temp->empid=empid;
temp->link=NULL;
*q=temp;
}
else
{
temp=*q;
while(temp->link!=NULL)
temp=temp->link;
r=malloc(sizeof(struct node));
strcpy(r->name,name);
strcpy(r->dept,dept);
r->sal=sal;
r->age=age;
r->empid=empid;
r->link=NULL;
temp->link=r;}
}
void addatbeg(struct node **q,char *name,char *dept,float sal,int age,int empid)
{
struct node *temp;
temp=malloc(sizeof(struct node));
strcpy(temp->name,name);
strcpy(temp->dept,dept);
temp->sal=sal;
temp->age=age;
temp->empid=empid;
temp->link=*q;
*q=temp;
}
void addafter(struct node *q,char* name,char* dept,float sal,int age,int empid,int loc)
{
struct node *temp,*r;
int i;
temp=q;
for(i=0;i<loc;i++)
{
temp=temp->link;
if(temp==NULL)
{
printf("\nThere are less than %d elements in the list\n",loc);
return;
}
}
r=malloc(sizeof(struct node));
strcpy(r->name,name);
strcpy(r->dept,dept);
r->sal=sal;
r->age=age;
r->empid=empid;
r->link=temp->link;
temp->link=r;
}
void display(struct node *q)
{
printf("\n");
char c;
p=fopen("text.txt","r");
c=fgetc(p);
while(!feof(p) )
{
printf("%c",c);
c=fgetc(p);
}
int fclose(FILE *p);
while(q!=NULL)
{
printf("%s\t%s\t%.2f\t%d\t%d\n",q->name,q->dept,q->sal,q->age,q->empid);
printf("\n");
q=q->link;
}
}
void displaydept(struct node *q,char* dept)
{
printf("\n");
while(q!=NULL)
{
if(strcmp(q->dept,dept)==0)
{
printf("\nName:%s\nDepartment:%s\nSalary:%f\nAge:%d\nEmployee ID:%d\n",q->name,q->dept,q->sal,q->age,q->empid);
printf("\n");}
q=q->link;
}
}
int count(struct node *q)
{
int c=0;
while(q!=NULL)
{
q=q->link;
c++;
}
return c;
}
void del(struct node **q,int empid)
{
struct node *old,*temp;
temp=*q;
struct node te;
temp=*q;
p = fopen("text.txt", "r");
t=fopen("temp.txt","w");
char oldname[]="temp.txt";
char newname[]="text.txt";
while(temp!=NULL)
{
if(temp->empid==empid)
{
if(temp==*q)
*q=temp->link;
else
old->link=temp->link;
free(temp);
printf("\nFIRED!\n");
return;
}
else
{
old=temp;
temp=temp->link;
}
printf("\nEmployee not found in linked list\n");
}
fscanf(p,"%s %s %f %d %d",te.name,te.dept,&te.sal,&te.age,&te.empid);
while( !feof(p) )
{
printf("%s %s %.2f %d %d\n",te.name,te.dept,te.sal,te.empid,empid);
if(te.empid!=empid)
{
printf("%s\t%s\t%.2f\t%d\t%d\n",te.name,te.dept,te.sal,te.age,te.empid);
fprintf(t,"%s\t",te.name);
fprintf(t,"%s\t",te.dept);
fprintf(t,"%.2f\t",te.sal);
fprintf(t,"%d\t",te.age);
fprintf(t,"%d\n",te.empid);
}
fscanf(p,"%s %s %f %d %d",te.name,te.dept,&te.sal,&te.age,&te.empid);
}
int fclose(FILE *p);
int fclose(FILE *t);
rename(oldname,newname);
}
void search(struct node *q,int empid)
{
printf("\n");
while(q!=NULL){
if(q->empid==empid)
{
printf("\nName:%s\nDepartment:%s\nSalary:%f\nAge:%d\nEmployee ID:%d\n",q->name,q->dept,q->sal,q->age,q->empid);
return;
}
q=q->link;
}
printf("\nEmployee not found\n");
}
void searchname(struct node *q,char *name)
{
printf("\n");
while(q!=NULL)
{
if(strcmp(q->name,name)==0)
{
printf("\nName:%s\nDepartment:%s\nSalary:%f\nAge:%d\nEmployee ID:%d\n",q->name,q->dept,q->sal,q->age,q->empid);
return;
}
q=q->link;
}
printf("\nEmployee not found\n");
}
void displaylist()
{
visit=start;
while(visit!=NULL)
{
printf("\nName:%s\nDepartment:%s\nSalary:%f\nAge:%d\nEmployee ID:%d\n\n",visit->name,visit->dept,visit->sal,visit->age,visit->empid);
visit=visit->link;
}
}
void selection_sort(int n)
{ int i,j;
struct node *p,*q;
p=start;
for(i=0;i<n-1;i++)
{
q=p->link;
for(j=i+1;j<n;j++)
{
if(p->sal>q->sal)
{
strcpy(tmp.name,p->name);
strcpy(p->name,q->name);
strcpy(q->name,tmp.name);
strcpy(tmp.dept,p->dept);
strcpy(p->dept,q->dept);
strcpy(q->dept,tmp.dept);
tmp.sal=p->sal;
p->sal=q->sal;
q->sal=tmp.sal;
tmp.age=p->age;
p->age=q->age;
q->age=tmp.age;
tmp.empid=p->empid;
p->empid=q->empid;
q->empid=tmp.empid;
}
q=q->link;
}
p=p->link;
}}
void birthday(struct node *q,int empid)
{
while(q!=NULL)
{
if(q->empid==empid)
{
q->age+=1;
}
q=q->link;
}
q=qnew;
}
void deptchange(struct node *q,int empid,char *newdept)
{
while(q!=NULL)
{
if(q->empid==empid)
{
strcpy(q->dept,newdept);
}
q=q->link;
}
q=qnew;
}
void salarychange(struct node *q,int empid,float raise)
{
while(q!=NULL)
{
if(q->empid==empid)
{
q->sal=q->sal+raise;
}
q=q->link;
}
q=qnew;
}
