#include<stdio.h>

int main()
{

    FILE *fp;
    fp=fopen("compressed.txt","r");

    int c=getc(fp);
    while(c!=EOF)
    {

        while(c!=1 && c!=0)
        {
            printf("%d",c%2);
            c=c/2;

        }printf("%d",c);
        c=getc(fp);
    }

    return 0;
}
