#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct output
{
    int off;
    int match;
    char code;
    struct output *next;
};

struct output *first = NULL;
struct output *last = NULL;

char str[255],searchbuffer[8],alpha;
int sbstart,sbend,labstart,labend,in,matchn,sp,i,offset,i_dash,sp_dash,matchid[7],j,matchnumber[7],k,l,maximum,minimum,flag;
int maxind,minind;

//FUNCTION DECLARATION STARTS
struct output* getnode(char o,char m, char c);
//FUNCTION DECLARATION ENDS

//_____________________MAIN STARTS_____________________
int main()
{
    struct output *newnode=NULL;
    printf("Enter the String : ");
    gets(str);
    printf("Size of string = %d\n",strlen(str));
    in=0;
    sbstart = 0;
    sbend = 6;
    labstart = 7;
    labend = 12;
    sp=labstart;
    for(in=0;in<7;in++)
    {
        searchbuffer[in] = str[in];
    }
    printf("Search Buffer for Decoding will be = [%s]\n\n",searchbuffer);
    printf("Pointers set for 1st iteration.\n");
    printf("\nOUTPUT IS :\n");
    /*__________________________________ENCODE THE STRING__________________________________*/
    while(str[sp-1]!='\0')
    {
        sp = labstart;
        i=sp-1;
        j=0;
        for(l=0;l<7;l++)
        {
            matchnumber[l] = -1;
            matchid[l] = -1;
        }
        j=0;
        while((sp-i)!=8)
        {
            if(str[sp]==str[i])
            {
                matchid[j++] = i;
                //printf("'%c'Matched at offset = %d, location = %d\n",str[i],(sp-i),i);
            }//if(str[sp]==str[i] ends
            i--;
        }//while((sp-i)!=7) ends

        for(k=0;k<j;k++)
        {
            i_dash = matchid[k];
            sp_dash = sp;
            //printf("For match at index %d,\n",matchid[k]);
            while(str[i_dash]==str[sp_dash] && sp_dash!=labend+1)
            {
                matchnumber[k]++;
                i_dash++;sp_dash++;
            }//while(str[i_dash]==str[sp_dash]) ends
            matchnumber[k]+=1;
        }
        maximum = -1;
        for(k=0;k<7;k++)
        {
           if(matchnumber[k] > maximum)
           {
               maximum = matchnumber[k];
           }
        }
       if(maximum>=0)
        {
            for(k=0;k<7;k++)
            {
                if(matchnumber[k]==maximum)
                {
                    minind = matchid[k];
                    offset = sp - minind;
                    matchn = maximum;
                    alpha = str[sp+matchn];
                    printf("(%d, %d, C(%c))\n",offset,matchn,alpha);
                    break;
                }//if(matchnumber[k]==maximum) ends
            }
        }//if(maximum!=0) ends

        else if(maximum==-1)
        {
            offset = 0;
            matchn = 0;
            alpha = str[sp+matchn];
            printf("(%d, %d, C(%c))\n",offset,matchn,alpha);
        }//else if(maximum==0)
        //store the offset, matchlength and character in the output linked list
        newnode = getnode(offset,matchn,alpha);
        if(newnode!=NULL)
        {
            if(first==NULL)//is first node
            {
                first=newnode;
                last=newnode;
            }//is first node ends
            else//is not first node
            {
                last->next = newnode;
                last = newnode;
            }//is not first node
        }
        sbstart+=(matchn+1);
        sbend+=(matchn+1);
        labstart+=(matchn+1);
        labend+=(matchn+1);
   }//while(str[sp]!='\0') ends
   /*__________________________________ENCODED THE STRING__________________________________*/
   /*__________________________________DECODE THE STRING__________________________________*/
   char decoded[strlen(str)+1];
   for(k=0;k<strlen(str)+1;k++)
   {
       decoded[k] = '\0';
   }

   strcpy(decoded,searchbuffer);

   struct output *point = first;
   sp=6;
   while(point->next!=NULL)
   {
       offset = point->off;
       matchn = point->match;
       alpha = point->code;
       i = sp - offset + 1;
       for(k=0;k<matchn;k++)
       {
           decoded[sp+1] = decoded[i];
           sp++;i++;
       }
       decoded[++sp] = alpha;
       printf("\n = %s\n",decoded);
       point = point->next;
   }
    return 0;
}//main ends
//_____________________MAIN ENDS_____________________

//FUNCTION DEFINITION STARTS
struct output* getnode(char o,char m, char c)
{
    struct output *newnode=NULL;
    newnode = (struct output*)malloc(sizeof(struct output));
    if(newnode==NULL)
    {
        printf("Memory not allocated.\n");
    }
    else
    {
        newnode->code = c;
        newnode->match = m;
        newnode->off = o;
        newnode->next = NULL;
    }
    return(newnode);
};
//FUNCTION DEFINITION ENDS
