#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int codelen(char* code)
{
    int l = 0;
    while (*(code + l) != '\0')
        l++;
    return l;
}
int fib(int n)
{
    if (n <= 1)
        return n;
    return fib(n - 1) + fib(n - 2);
}

void error(const char *msg)
{
    perror(msg);
    exit(1);
}
long int p,q,n,t,flag,e,d,temp[100],j,m[100],i;
char msg[1000] = "";
int prime(long int);
void encrypt();
void decrypt();
int gcd(int a , int b);
FILE *filePointer ;
char en[100];
int freq[50];
void str_cat(char* str, char* parentcode, char add);
char abcdef[1000]="";
typedef struct node_t {
	struct node_t *left, *right;
	int freq;
	char c1;
} *node;

struct node_t pool[256] = {{0}};
node q1q1q1[255], *q1 = q1q1q1 - 1;
int n_nodes = 0, qend = 1;
char *code[128] = {0}, buf[1024];

node new_node(int freq, char c1, node a1, node b1)
{
	node n1 = pool + n_nodes++;
	if (freq) n1->c1 = c1, n1->freq = freq;
	else {
		n1->left = a1, n1->right = b1;
		n1->freq = a1->freq + b1->freq;
	}
	return n1;
}

/* priority queue */
void qinsert(node n1)
{
	int j1, i1 = qend++;
	while ((j1 = i1 / 2)) {
		if (q1[j1]->freq <= n1->freq) break;
		q1[i1] = q1[j1], i1 = j1;
	}
	q1[i1] = n1;
}

node qremove()
{
	int i1, l1;
	node n1 = q1[i1 = 1];

	if (qend < 2) return 0;
	qend--;
	while ((l1 = i1 * 2) < qend) {
		if (l1 + 1 < qend && q1[l1 + 1]->freq < q1[l1]->freq) l1++;
		q1[i1] = q1[l1], i1 = l1;
	}
	q1[i1] = q1[qend];
	return n1;
}

/* walk the tree and put 0s and 1s */
void build_code(node n1, char *s1, int len1)
{
	static char *out = buf;
	if (n1->c1) {
		s1[len1] = 0;
		strcpy(out, s1);
		code[n1->c1] = out;
		out += len1 + 1;
		return;
	}

	s1[len1] = '0'; build_code(n1->left,  s1, len1 + 1);
	s1[len1] = '1'; build_code(n1->right, s1, len1 + 1);
}

void init(const char *s1)
{
	int i1, freq[128] = {0};
	char c1[16];

	while (*s1)
    {
        freq[(int)*s1++]++;
    }

	for (i1 = 0; i1 < 128; i1++)
		if (freq[i1]) qinsert(new_node(freq[i1], i1, 0, 0));

	while (qend > 2)
		qinsert(new_node(0, 0, qremove(), qremove()));

	build_code(q1[1], c1, 0);
}

void encode(const char *s1, char *out)
{
	while (*s1) {
		strcpy(out, code[*s1]);
		out += strlen(code[*s1++]);
	}
}

void decode(const char *s1, node t1)
{
	node n1 = t1;
	while (*s1) {
		if (*s1++ == '0') n1 = n1->left;
		else n1 = n1->right;

		if (n1->c1) putchar(n1->c1), n1 = t1;
	}

	putchar('\n');
	if (t1 != n1) printf("garbage input\n");
}

// *****/ MAIN STARTS HERE /***/
int main(int argc, char *argv[])
{
    printf("**WELCOME TO SECURE**\n");
    printf("PLEASE SELECT YOUR ROLE FROM BELOW\n");
    printf("1.DATA SECURING\n");
    printf("2.MORE INFORMATION OR HELP\n");
    int type;
    scanf("%d",&type);
    switch(type)
    {
        case 1:
        {
    printf("FOR SECURITY WE HAVE IMPLEMENTED THE HUFFMANN CODING AND RSA ALGORITHM\n");
    printf("choose your data type which you want to secure from below:-\n");
    printf("1.TEXT\n");
    //printf("2.IMAGE\n");
    int choice;
    scanf("%d",&choice);
    getchar();
    switch(choice)
    {
        case 1 : {
            int i1;
	char text[100];

	printf("ENTER THE TEXT YOU WANT TO BE SEND\n");
	printf("FIRST TEXT COMPRESSION WILL BE DONE\n");
        char chr[50];
        fgets(chr, 50, stdin);

	const char *str = chr;
        char buf[1024];
	init(str);
	for (i1 = 0; i1 < 128; i1++)
		if (code[i1]) printf("'%c': %s\n", i1, code[i1]);

	encode(str, buf);
	printf("AFTER APPLYING HUFFMANN ENCODING:-\n");
	printf("encoded: %s\n", buf);

	//printf("decoded: ");
	//decode(buf, q1[1]);

        strcpy(msg, buf);
        /////////////////
        ////////////////
        ////////////////
        ///////////////
        printf("ENCRYPTING THE COMPRESSED MESSAGE:-");
   printf("\nENTER FIRST PRIME NUMBER\n");

scanf("%d",&p);

	flag = prime(p);

	if(flag==0) {

		printf("\nWRONG INPUT\n");



		exit(1);

	}

	printf("\nENTER ANOTHER PRIME NUMBER\n");

	scanf("%d",&q);

	flag=prime(q);

	if(flag==0||p==q) {

		printf("\nWRONG INPUT\n");


		exit(1);
 }

	for (i=0;msg[i]!=NULL;i++)

	m[i]=msg[i];

	n=p*q;

	t=(p-1)*(q-1);
    e = 2;
	while(e<t)
	{
	    int count = gcd(e,t);
	    if(count==1)
	    {
	        break;
	    }
	    else
	    {
	        e++;
	    }
	}
	long int k = 2;
	d = (1+(k*t))/e;
	encrypt();
	decrypt();
	printf("\n");
	printf("AFTER APPLYING HUFFAMN DECODING:-\n");
	printf("DECODED MESSAGE: ");
	decode(buf, q1[1]);
        break;
        }

default :
{
    printf("PLEASE SELECT THE CORRECT DATA TYPE\n");
    break;
}


    }

            break;
        }

    /*case 2 :
        {
           printf("**HELP***\n");
           printf("->OUR PROJECT DEALS WITH THE FAST AND SECURE DATA TRASMISSION\n");
            printf("->FOR SECURITY WE ARE USING HUFFMAN ENCODING DECODING AND RSA ENCRYPTION DECRYPTION\n");
            printf("->AFTER THE COMPLETION OF FIRST PHASE , A FILE IS GENERATED AND GET SAVED IN YOUR FILE SYSYEM\n");
            printf("->IN SECOND PHASE , WE ARE USING SOCKET PROGRAMMING TO TRANSFER THE FILE BETWEEN TWO SYSTEMS\n");
            printf("->THEN REPEATING THE SAME PROCESS IN SYSTEM 2 ie DECRYPTION AND DECODING\n");
            printf("->THANK YOU\n");
         break;
        }*/
    default :
        {
            printf("FOR SOCKET PROGRAMMING WE HAVE A SEPARATE PACKAGE\n");
            printf("TWO FILES WILL BE REQUIRED, A SERVER AND A CLIENT \n");
            printf("IN THE SERVER PART WE NEED TO ENTER THE PORT NUMBER AS A COMMAND LINE ARGUMENT\n");
            printf("FOR CLIENT PART WE ENTER THE FILENAME TO BE RECIEVED \n");
        }
    }


}
int prime(long int pr) {

	int i;

	j=sqrt(pr);

	for (i=2;i<=j;i++) {

		if(pr%i==0)

		    return 0;

	}

	return 1;

}
int gcd(int a, int h)
{
    int temp;
    while(1)
    {
        temp = a%h;
        if(temp==0)
        return h;
        a = h;
        h = temp;
    }
}
void encrypt() {

	long int pt,ct,key=e,k,len;

	i=0;

	len = strlen(msg);
	//printf("%d",len);

	while(i!=len) {

		pt=m[i];

		pt=pt-96;

		k=1;

		for (j=0;j<key;j++) {

			k=k*pt;

			k=k%n;

		}

		temp[i]=k;

		ct=k+96;

		en[i]=ct;

		i++;

	}

	en[i]=-1;

	printf("\nTHE ENCRYPTED MESSAGE IS\n");

	for (i=0;en[i]!=-1;i++){
	printf("%c",en[i]);}

	//Writing to a FILE/

	filePointer = fopen("database.txt", "w") ;


    if ( filePointer == NULL )
    {
        printf( "database.txt file failed to open." ) ;
    }
    else
    {
        printf("\n");
        printf("The file is now opened.\n") ;


        if ( strlen (  en  ) > 0 )
        {

            fputs(en, filePointer) ;
           // fputs("\n", filePointer);
        }
        fclose(filePointer) ;
}

}
void decrypt() {

	long int pt,ct,key=d,k;

	i=0;

	while(en[i]!=-1) {

		ct=temp[i];

		k=1;

		for (j=0;j<key;j++) {

			k=k*ct;

			k=k%n;

		}

		pt=k+96;

		m[i]=pt;

		i++;

	}

	m[i]=-1;

	printf("\nTHE DECRYPTED MESSAGE IS\n");

	for (i=0;m[i]!=-1;i++)

	printf("%c",m[i]);

}
