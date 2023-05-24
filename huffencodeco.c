#include<stdio.h>
#include<string.h>
#include<stdlib.h>

//STRUCTURE DECLARATION
struct node
{
    char c;
    int freq;
    char code[255];
    struct node *next;
    struct node *left;
    struct node *right;
    struct node *parent;
};
struct node *first;
struct node *last;
struct node *root;

//STACK AS LINKED LIST DECLARATION
struct llnode
{
    char sc;
    struct llnode *next;
};
struct llnode *prime;
struct llnode *rear;

//DECLARE FILE POINTER AND OTHER REQUIRED GLOBAL VARIABLES
FILE *fp=NULL;
int in;//INDEX while decoding the encoded Huffman string
//FILE POINTER DECLARATION COMPLETE

//FUNCTION DECLARATION
int check(char *str,char *alpha);
struct node* getnode(char *z,int *fr);
void place(struct node *newnode);
struct llnode* getllnode(char a);
void push(char *a);
void pop(int a);
void copy(char *string);
void inorder(struct node *newnode);
void print(char *a,struct node *newnode);
void decode(void);
//GLOBAL VARIABLE DECLARATIONS
char str[255], alpha[255];
int f[255];
int main()//MAIN STARTS_________________________________________________________________
{
printf("Enter the string : ");
gets(str);
int i=0,flag=-1,j=0;
struct node *newnode=NULL;
while(str[i]!='\0')
{
    if(i==0)
    {
        alpha[0] = str[j++];
        f[0]++;
    }
    else
    {
        flag = check(&str[i],alpha);
        if(flag==-1)
        {
            alpha[j] = str[i];
            f[j++]++;
        }
        else
        {
            alpha[flag] = str[i];
            f[flag]++;
        }
    }
    i++;
}
int n=i,tempn;//number of characters in the string
char tempc;
for(i=0;i<n;i++)
{
    for(j=0;j<n;j++)
    {
        if(f[i]>f[j])
        {
            tempn=f[j];
            f[j]=f[i];
            f[i]=tempn;
            tempc=alpha[j];
            alpha[j]=alpha[i];
            alpha[i]=tempc;
        }
    }
}

i=0;
while(alpha[i]!='\0')
{
    newnode=getnode(&alpha[i],&f[i]);
    if(newnode!=NULL)
    {
        if(first==NULL)//is first element
        {
            first=newnode;
            last=first;
        }
        else//not first element
        {
            last->next=newnode;
            last=newnode;
        }
    }//newnode!=NULL
    i++;
}
struct node *point=first;
//DISPLAY THE LINKED LIST
point=first;
printf("____SORTED LINKED LIST____\n");
while(point!=NULL)
{
    printf("(%c,%d)-->",point->c,point->freq);
    point=point->next;
}
//END DISPLAY OF LINKED LIST
struct node *leftchild=NULL,*rightchild=NULL;
char sub='%';//substitute character for middle parent nodes
int addf=0;//additive frequency to create parent node
while(first->next!=last)
{
    rightchild=last;//last linked list node is the right child
    leftchild=first;
    while(leftchild->next!=rightchild)//2nd last ll node is the left child
    {
        leftchild=leftchild->next;
    }
    last=first;
    while(last->next!=leftchild)//3rd last ll node is now last node
    {
        last=last->next;
    }
    last->next=NULL;
    addf = leftchild->freq + rightchild->freq;
    newnode=getnode(&sub,&addf);
    if(newnode!=NULL)//memory is allocated
    {
        newnode->left = leftchild;
        newnode->right = rightchild;
        rightchild->parent=newnode;
        leftchild->parent=newnode;
        leftchild->next=NULL;
        rightchild->next=NULL;
        place(newnode);
    }
}//first->next!=last
point=first;

//use the root node to create the entire binary tree
leftchild=first;
rightchild=first->next;
last->next=NULL;
addf = leftchild->freq + rightchild->freq;
newnode=getnode(&sub,&addf);
if(newnode!=NULL)//memory is allocated
    {
        newnode->left = leftchild;
        newnode->right = rightchild;
        rightchild->parent=newnode;
        leftchild->parent=newnode;
        leftchild->next=NULL;
        rightchild->next=NULL;
        place(newnode);
    }
printf("\n_____ROOT NODE CREATED_____\n");
printf("%c %d\n",newnode->c,newnode->freq);
root=newnode;
printf("____INORDER TRAVERSAL AND CODE ASSIGNMENT____\n\n");
printf("(S,F) = code\n");
inorder(newnode);
//NOW PRINT THE ENCODED DATA TO A FILE
fp=fopen("encoded.txt","w");
i=0;
printf("\n____Encoded String is : ____\n");
while(str[i]!='\0')
{
    print(&str[i],root);
    i++;
}
fclose(fp);
//READ THE ENCODED DATA IN THE FILE AND PRINT DECODED TEXT TO FILE
decode();
printf("\n");
return 0;
}
//MAIN ENDS_________________________________________________________________
//FUNCTION DEFINITION
int check(char *a,char *alpha)
{
    int i=0,flag=-1;
    while(alpha[i]!='\0')
    {
        if(alpha[i]==*a)
        {
            flag=i;
            return(flag);
        }
        i++;
    }
return(flag);
}
//CHECK FUNCTION ENDS
struct node* getnode(char *z,int *fr)
{
    struct node *newnode=NULL;
    newnode = (struct node*)malloc(sizeof(struct node));
    if(newnode==NULL)
    {
        printf("Memory not allocated for %c.\n",*z);
    }
    else
    {
        newnode->c = *z;
        newnode->freq = *fr;
        newnode->next=NULL;
        newnode->left=NULL;
        newnode->right=NULL;
        newnode->parent=NULL;
    }
return(newnode);
}
//GETNODE FUNCTION ENDS
void place(struct node *newnode)
{
    struct node *point=first;
    while(point->freq > newnode->freq)
    {
        point = point->next;
    }//while point->freq >= newnode->freq
    if(point==first)//additive frequency is largest frequency
    {
        newnode->next = point;
        first=newnode;
    }//additive frequency is the largest frequency
    else if(point==NULL)//additive frequency is minimum frequency
    {
        last->next=newnode;
        last=newnode;
    }//additive frequency is minimum frequency
    else//additive frequency is intermediate
    {
        newnode->next=point->next;
        point->next=newnode;
    }//additive frequency is intermediate
}
//PLACE NODE FUNCTION ENDS
struct llnode* getllnode(char a)
{
    struct llnode *newnode=NULL;
    newnode = (struct llnode*)malloc(sizeof(struct llnode));
    if(newnode!=NULL)
    {
        newnode->sc=a;
        newnode->next=NULL;
    }
return(newnode);
}
//GET LLNODE FUNCTION ENDS
void push(char *a)
{
    struct llnode *newnode=NULL;
    newnode = getllnode(*a);
    if(newnode!=NULL)
    {
        if(prime==NULL)
        {
            prime=newnode;
            rear=newnode;
        }//prime is null therefore, stack is empty
        else//stack is not empty
        {
            rear->next=newnode;
            rear=newnode;
        }
    }
    newnode=prime;
}
//PUSH FUNCTION ENDS
void pop(int a)
{
    struct llnode *point=prime,*pointi=NULL;

    if(prime==rear)//first and last node remaining
    {
        pointi=prime;
        prime=NULL;
        rear=NULL;
        free(pointi);
    }
    else//more than one element in stack
    {
        while(point->next!=rear)
        {
            point=point->next;
        }
        rear=point;
        pointi=point->next;
        rear->next=NULL;
        free(pointi);
    }
}
//POP FUNCTION ENDS
void copy(char *string)
{
    int i=0;
    struct llnode *point=prime;
    while(point!=NULL)
    {
        string[i] = point->sc;
        point=point->next;
        i++;
    }
}
//FUNCTION COPY ENDS
void inorder(struct node *newnode)
{
    struct llnode *point=prime;
    if(newnode==NULL)
    {
        return;
    }
    if(newnode!=root)
    {
        if(newnode==newnode->parent->right)
            push("1");
        else if(newnode==newnode->parent->left)
            push("0");
    }
    inorder(newnode->right);
    copy(newnode->code);
    if(newnode->c!='%')
        printf("(%c ,%d) = %s\n",newnode->c,newnode->freq,newnode->code);
    inorder(newnode->left);
    pop(0);
}
//INORDER FUNCTION ENDS
void print(char *a, struct node *newnode)
{
    if(newnode==NULL)
    {
        return;
    }
    print(a,newnode->right);
    if(newnode->c==*a)
    {
        fprintf(fp,"%s",newnode->code);
        return;
    }
    print(a,newnode->left);

}
//PRINT FUNCTION ENDS
void decode(void)
{
    fp=fopen("encoded.txt","r");
    struct node *newnode=root;
    char a[2000];
    fscanf(fp,"%s",a);
    printf("\n%s\n",a);
    in=0;
    printf("\n____Decoded String is : ____\n\n");
    while(a[in]!='\0')
    {
        newnode=root;
        while(newnode->left!=NULL && newnode->right!=NULL)
        {
            if(a[in]=='0')
            {
                newnode=newnode->left;
            }
            else
            {
                newnode=newnode->right;
            }
            in++;
        }
        printf("%c",newnode->c);
    }
}
//DECODE AND PRINT FUNCTION ENDS
