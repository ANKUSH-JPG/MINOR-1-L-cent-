#include<stdio.h>

int main()
{

    FILE *fp;
    fp=fopen("compressed.txt","r");

    int c=getc(fp);
    while(c!=EOF)
    {
        printf("%c",c);


        c=getc(fp);
    }

    return 0;
}
