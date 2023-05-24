#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>

//STRUCTURE DECLARATION

//FUNCTION DECLARATION

char str[50];
float p[50],l[50];
char c[50],temp;
int main()
{
    printf("Enter the String : ");
    gets(str);
    float length = strlen(str);
    float low=0,high=0,range=0;
    int i=1,j=1;
    c[0] = str[0];
    p[0] = 1;
    i=1;
    while(str[i]!='\0')
    {
        j=0;
        while(c[j]!='\0')
        {
            if(str[i]==c[j])
            {
                break;
            }
            j++;
        }
        if(c[j]=='\0')
        {
            c[j] = str[i];
        }
        i++;
    }
    i=0;
    j=0;
    while(c[i]!='\0')
    {
        j=0;
        while(c[j]!='\0')
        {
            if(c[j]>c[i])
            {
                temp = c[j];
                c[j] = c[i];
                c[i] = temp;
            }
            j++;
        }
        i++;
    }
    printf("%s\n",c);
    i=0;j=0;
    while(c[i]!='\0')
    {
        j=0;
        while(str[j]!='\0')
        {
            if(c[i]==str[j])
            {
                p[i]++;
            }
            j++;
        }
        i++;
    }

    i=1;
    while(c[i]!='\0')
    {
        p[i] = p[i-1]/length;
        i++;
    }
    i=1;
    while(c[i]!='\0')
    {
        p[i] = p[i-1] + p[i];
        i++;
    }
    p[0] = (p[0]-1)/length;
    l[0] = 0;
    i=1;
    while(c[i]!='\0')
    {
        l[i] = p[i-1];
        i++;
    }


    i=0;
    while(c[i]!='\0')
    {
        p[i] = p[i]/length;
        printf("%c %f\n",c[i],l[i]);
        i++;
    }
    return 0;
}
//FUNCTION DEFINITION
