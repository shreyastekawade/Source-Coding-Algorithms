#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//STRUCTURE DECLARATIONS START
struct string
{
    char str[10];
    int index;
    struct string *next;
};
struct string *first = NULL, *last = NULL,*original=NULL,*point1=NULL;
//STRUCTURE DECLARATIONS END

//GLOBAL VARIABLE DECLARATIONS START
int current_in,last_in,length,maximum=1,encoded[100],enid=-1;
char input[100],output[100];
char initial[10];
FILE *fp=NULL;
//GLOBAL VARIABLE DECLARATIONS END

//FUNCTION DECLARATIONS START
struct string* getnode(char *c,int i);
//FUNCTION DECLARATIONS END

//________________________________________________MAIN STARTS________________________________________________
int main()
{
    struct string *newnode = NULL, *point=NULL,*match[10];
    printf("Enter the string : ");
    gets(input);
    length = strlen(input);
    printf("The length of the string is = %d\n\n",length);
    int n,i,j,k;
    printf("Enter the size of the initial dictionary : ");
    scanf("%d",&n);
    for(i=0;i<n;i++)
    {
        printf("Enter Dictionary element NO %d : ",i+1);
        scanf("%s",initial);
        newnode = getnode(initial,i+1);
        if(newnode!=NULL)
        {
            if(first == NULL)
            {
                first = newnode;
                last = newnode;
            }//if(first == NULL) ends
            else
            {
                last->next = newnode;
                last = newnode;
            }
        }//if(newnode!=NULL) ends
    }//for(i=0;i<n;i++) ends
    original = last;
    point = first;
    current_in = 0;
    last_in = 0;
    printf("___ENCODING___\n");
    while(input[current_in] != '\0')
    {
       j=-1;
        for(i=0;i<maximum;i++)
        {
            initial[i] = input[current_in+i];
            point = first;
            while(point!=NULL)
            {
                if(!(strcmp(point->str,initial)))
                {
                    match[++j] = point;
                }
                point = point->next;
            }
        }
    encoded[++enid] = match[j]->index;
    last_in = current_in;
    current_in += strlen(match[j]->str);

        for(k=0;k<10;k++)
        {
            initial[k] = '\0';
        }
        n=0;
        for(k=last_in;k<=current_in;k++)
        {
            initial[n++] = input[k];
        }
        newnode = getnode(initial,0);
        if(newnode!=NULL)
        {
            newnode->index = last->index + 1;
            last->next = newnode;
            last = newnode;
            if(strlen(initial)>maximum)
            {
                maximum = strlen(initial);
            }
        }
        for(k=0;k<10;k++)
        {
            initial[k] = '\0';
        }
    }//while(current_in < (strlen(input)+1)) ends
    printf("\n___INPUT DICTIONARY___\n");
    point = first;
    while(point->next!=NULL)
    {
        printf("(%d, %s)->",point->index,point->str);
        point = point->next;
    }
    printf("\n\n___OUTPUT IS___\n");
    for(i=0;i<=enid;i++)
    {
        printf("%d ",encoded[i]);
    }
    last = original;
    original = original->next;
    last->next=NULL;
    while(original!=NULL)
    {
        point = original;
        original = original->next;
        free(point);
    }
    printf("\n____________________________________________\nEarlier Dictionary cleared.\n");
    printf("__________NOW, DECODE THE ENCODED STRING USING INITIAL DICTIONARY__________\n\n");
    point=first;

    while(encoded[0]!=point->index)
    {
        point = point->next;
    }
    strcpy(output,point->str);
    current_in = strlen(output) - 1;

    for(i=1;i<=enid;i++)
    {
        last_in = current_in;
        while(output[current_in] != '\0')
        {
            current_in++;
        }
        point = first;
        while(point->index != encoded[i])
        {
            point = point->next;
        }
        strcat(output,point->str);
        for(j=0;j<10;j++)
        {
            initial[j] = '\0';
        }
        for(j=last_in;j<=current_in;j++)
        {
            initial[j-last_in] = output[j];
        }
        newnode = getnode(initial,0);
        if(newnode!=NULL)
        {
            newnode->index = last->index + 1;
            last->next = newnode;
            last = newnode;
        }
    }//for(i=1;i<=enid;i++) ends
    printf("%s\n\n_____OUTPUT DICTIONARY_____\n",output);
    point = first;
    while(point!=NULL)
    {
        printf("(%d, %s)->",point->index,point->str);
        point = point->next;
    }
    return 0;
}
//________________________________________________MAIN ENDS________________________________________________
//FUNCTION DEFINITION BEGINS
struct string* getnode(char *c,int i)
{
    struct string *newnode = NULL;
    newnode = (struct string*)malloc(sizeof(struct string));
    if(newnode!=NULL)
    {
        strcpy(newnode->str,c);
        newnode->next = NULL;
        newnode->index = i;
    }
    return(newnode);
};
//FUNCTION DEFINITION ENDS
