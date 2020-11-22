#include<stdio.h>

int main()
{

    FILE *fp;
    fp=fopen("compressed.txt","r");

    int c=getc(fp);
    while(c!=EOF)
    {
        int a[8]={0};
        int i=0;
        while(c!=1 && c!=0)
        {
            a[i]=c%2;
            c=c/2;
            i=i+1;

        }a[i]=c;
        c=getc(fp);

        for(int x=0;x<8;x++)
        {
            printf("%d",a[x]);
        }
    }

    return 0;
}
