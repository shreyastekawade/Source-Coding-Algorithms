#include<stdio.h>
#include<string.h>
#include<stdlib.h>

//STRUCTURE DEFINITION
struct node
{
    char string[10];
    struct node *next;
};
struct node *first=NULL;
struct node *last=NULL;
struct node *end=NULL;
//STRUCTURE DEFINTION ENDS

//FUNCTION DECLARATION STARTS
struct node* getnode(char *str);
void check(char *str);
//FUNCTION DECLARATION ENDS
char str[10],str1[10],str2[10];
int main()
{
    int n,i;
    int minimum=0,flag=0,flag1=0,length1=0,length2=0;
    printf("Enter the number of codewords : ");
    scanf("%d",&n);
    struct node *newnode=NULL;
    for(i=0;i<n;i++)//create primary linked list with n codewords
    {
        printf("Enter codeword number %d : ",i+1);
        scanf("%s",str);
        newnode = getnode(str);
        if(first==NULL)//is first in linked list
        {
            first=newnode;
            last=newnode;
            printf("Made node for : %s\n",str);
        }//first==NULL ends
        else//is not first
        {
            last->next = newnode;
            last = newnode;
            printf("Made node for : %s\n",str);
        }//is not first ends
    }//primary linked list with n codewords created
    end = last;
    struct node *point=NULL,*pointnext=NULL;
    point = first;

    while(point!=NULL)
    {
        pointnext = first;
        strcpy(str1,point->string);
        length1 = strlen(str1);
        while(pointnext!=end)
        {
            strcpy(str2,pointnext->string);
            length2 = strlen(str2);
            if(length1!=length2)
            {
                if(length1>length2)
                {
                    minimum = length2;
                }
                if(length2>length1)
                {
                    minimum = length1;
                }
                flag = strncmp(str1,str2,minimum);
                if(flag==0)
                {
                    if(length1>length2)
                    {
                        strcpy(str,&str1[minimum]);
                    }//if(length1>length2)
                    else
                    {
                        strcpy(str,&str2[minimum]);
                    }
                    check(str);
                }//if(flag==0)
            }//if(length1!=length2)
            pointnext = pointnext->next;
        }//while(pointnext!=end)
        point = point->next;
    }//while(point!=NULL)
    printf("\nThe Code is Uniquely Decodable.\n");
return 0;
}
//MAIN ENDS

//FUNCTION DEIFINITION STARTS
//FUNCTION 1 : ADD NODE TO LINKED LIST
struct node* getnode(char *str)
{
    struct node *newnode=NULL;
    newnode = (struct node*)malloc(sizeof(struct node));
    if(newnode!=NULL)
    {
        strcpy(newnode->string,str);
        newnode->next = NULL;
    }
    else
    {
        printf("Memory not allocated.\n");
    }
    return(newnode);
};

//FUNCTION 2 : CHECK DANGLING SUFFIX IN LIST
void check(char *str)
{
    struct node *point=first;
    while(point!=end)
    {
        if(strlen(str)==strlen(point->string))
        {
            if(!strcmp(str,point->string))
            {
                printf("\nNot uniquely Decodable.\n\nDangling Suffix(%s) from (%s,%s) equal to Codeword(%s).\n",str,str1,str2,point->string);
                exit(0);
            }
        }
        point = point->next;
    }
    while(point!=NULL)
    {
        if(strlen(str)==strlen(point->string))
        {
            if(!strcmp(str,point->string))
            {
                return;
            }
        }
        point = point->next;
    }
    point = getnode(str);
    if(point!=NULL)
    {
        last->next = point;
        last = point;
    }
}//check presence of dangling suffix ends
//FUNCTION DEFINITION ENDS

