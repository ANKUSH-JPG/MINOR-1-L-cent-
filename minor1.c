#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#define MAX 1000
#include <unistd.h>
#include <arpa/inet.h>
#define SIZE 1024
#define BINARYCODESIZE 1000000


long int p,q,n,t,flag,e[100],d[100],temp[100],j,mi[100],en[100],i;

char msg[100];

int prime(long int);

void ce();

long int cd(long int);

void encrypt();

void decrypt();

typedef struct node
{
        struct node *left;
        char ch;
        int freq;
        struct node *right;
}node;

struct table
{
    char alpha;
    int freq;
};

struct codes
{
    int sequence[MAX][8];
    int binary[8];
    char ch[MAX];
    int binary_codes[BINARYCODESIZE];
};

void table_generation(char str[],int length);
node * delete_from_heap();
void swap_fun(int current);

node * heap[MAX];
int max_heap=-1;
node *d1;node *d2;
int x=-1;

//FOR codes
struct codes c;
int m=0;
int b_c_v=0; //binary code variable


void table_generation(char str[],int length)
{
   char greatest='0';

   // FINDING GREATEST ELEMENT
    for(int i=0;i<length;i++)
    {
        if(str[i]>greatest)
           greatest=str[i];

    }

    // COUNTINING FREQUENCE
    int hashmap[MAX]={0};
    for(int i=0;i<length;i++)
    {
        if(str[i]>=97)
            hashmap[str[i]-97]=hashmap[str[i]-97]+1;

        else if(str[i]>=65)
            hashmap[(str[i]-65)+26]=hashmap[(str[i]-65)+26]+1;
        else if(str[i]==32)
            hashmap[99]=hashmap[99]+1;

    }

    // ADD DATA TO STRUCTURE TABLE A
    int position=0,n=0;
    for(int i=0;i<MAX;i++)
    {
        if(hashmap[i]!=0)
            n++;
    }

    // CREATING STRUCTURE
    struct table a[n];

    for(int i=0;i<MAX;i++)
    {
        if(hashmap[i]!=0)
        {
            if(i<25)
            {
              a[position].alpha=i+97;
              a[position].freq=hashmap[i];

            }
            else if(i==99)
            {
                a[position].alpha=32;
                a[position].freq=hashmap[99];
            }
            else
            {
                a[position].alpha=i+39;
                a[position].freq=hashmap[i];
            }

            position++;
         }
    }

    for(int i=0;i<n;i++)
    {
           printf("%c  %d\n",a[i].alpha,a[i].freq);
           Insert_into_heap(a[i].alpha,a[i].freq);
    }

    while(heap[1]!=NULL)
    {

        d1=delete_from_heap();

        d2=delete_from_heap();

        int f=d1->freq+d2->freq;
        //printf("%d\n",f);
        char c='0';

        Insert_into_heap(c,f);
    }

    // VALUE OF BINARY TO 2
    for(int i=0;i<8;i++)
    {
        c.binary[i]=2;
    }

    // VALUE OF SEQUENCE AND CH TO 2
    for(int i=0;i<MAX;i++)
    {
        c.ch[i]='0';
        for(int j=0;j<8;j++)
            c.sequence[i][j]=2;
    }
    display(heap[0]);

    // VALUE OF BINARY_CODE TO 2
    for(int i=0;i<BINARYCODESIZE;i++)
    {
        c.binary_codes[i]=2;
    }

    //PRINT SEQUENCE

    print_sequence(str);

    //SEND TO FILE
    send_to_file(c.binary_codes);
}

void Insert_into_heap(char alpha,int freq)
{
      max_heap=max_heap+1;

      if(alpha=='0')
      {
          node *temp=(node *)malloc(sizeof(node));
          temp->ch=alpha;
          temp->freq=freq;
          temp->left=d1;
          temp->right=d2;

          heap[max_heap]=temp;

          heap_sort(max_heap);
      }
      else
      {
      node *temp=(node *)malloc(sizeof(node));
      temp->ch=alpha;
      temp->freq=freq;
      temp->left=NULL;
      temp->right=NULL;

      heap[max_heap]=temp;

      heap_sort(max_heap);
      }


}

void heap_sort(int current)
{
    if(current==-1)
    {}
    else
    {
        if(current*2+1<=max_heap)
        {
            // OPERATION PERFORMANCE
            if(current*2+2<=max_heap)
            {
                // left+right
                if(heap[current*2+1]->freq<=heap[current*2+2]->freq)
                {
                    if(heap[current]->freq>heap[current*2+1]->freq)
                    {
                        swap_fun(current);
                        heap_sort(current-1);
                    }
                    else
                        heap_sort(current-1);
                }
                else
                {
                    if(heap[current]->freq>heap[current*2+2]->freq)
                    {
                            node *temp=heap[current];
                            heap[current]=heap[current*2+2];
                            heap[current*2+2]=temp;

                            heap_sort(current-1);
                    }
                    else
                        heap_sort(current-1);

                }

            }
            else
            {  //left
                if(heap[current*2+1]->freq<heap[current]->freq)
                {
                    swap_fun(current);
                    heap_sort(current-1);
                }
            }

        }
        else
        {
            heap_sort(current-1);
        }
    }
}

void swap_fun(int current)
{
    node *temp=heap[current];
    heap[current]=heap[current*2+1];
    heap[current*2+1]=temp;
}

node * delete_from_heap()
{
    node *d=heap[0];
    heap[0]=heap[max_heap];
    heap[max_heap]=NULL;

    max_heap=max_heap-1;
    int current=0;

    delete_heap(current);

    return d;
}

void delete_heap(int current)
{
    if(current<=max_heap)
    {
        if(current*2+1<=max_heap)
        {
            // OPERATION PERFORMANCE
            if(current*2+2<=max_heap)
            {
                // left+right
                if(heap[current*2+1]->freq<heap[current*2+2]->freq)
                {
                    if(heap[current]->freq>heap[current*2+1]->freq)
                    {
                        swap_fun(current);
                        heap_sort(current*2+1);
                    }

                }
                else
                {
                    if(heap[current]->freq>heap[current*2+2]->freq)
                    {
                            node *temp=heap[current];
                            heap[current]=heap[current*2+2];
                            heap[current*2+2]=temp;

                            heap_sort(current*2+2);
                    }

                }
            }
            else
            {  //left
                if(heap[current*2+1]->freq<heap[current]->freq)
                {
                    swap_fun(current);
                    heap_sort(current*2+1);
                }
            }
        }
    }
    else
    {}
}

void display(node *head)
{
    if(head->ch=='0')
    {
        if(head->left!=NULL)
        {
            x=x+1;

            c.binary[x]=0;
            display(head->left);
            x=x-1;
            if(head->right!=NULL)
            {
                x=x+1;
                c.binary[x]=1;
                display(head->right);
                x=x-1;
            }
        }
    }
    else
    {
        for(int i=0;i<8;i++)
        {
            if(c.binary[i]==0 || c.binary[i]==1)
                {
                    printf("%d",c.binary[i]);
                    c.sequence[m][i]=c.binary[i];
                }
            else
                break;
        }
        printf(" : character=%c\n",head->ch);
        c.ch[m]=head->ch;

        m=m+1;
    }
}

void print_sequence(char str[])
{
    int p=0;
    while(str[p]!='\0')
    {
        char character=str[p];

        for(int i=0;i<MAX;i++)
        {
            if(c.ch[i]==character)
            {

                for(int j=0;j<8;j++)
               {
                    if(c.sequence[i][j]==0 || c.sequence[i][j]==1)
                    {
                        printf("%d",c.sequence[i][j]);
                        c.binary_codes[b_c_v]=c.sequence[i][j];
                        b_c_v=b_c_v+1;

                    }
                    else
                        break;
                }


                break;
            }
        }

        p=p+1;

    }

}

void send_to_file(int binary_codes[])
{
    int count_times=1;
    printf("\n");
    int ascii=0;
    FILE *fp;
    fp=fopen("compressed.txt","w");

    for(int i=0;i<BINARYCODESIZE;i++)
    {
        if(count_times<=5)
        {
            if(binary_codes[i]==0 || binary_codes[i]==1)
            {

                ascii=ascii+(binary_codes[i]*pow(2,count_times-1));
            }
            else
                break;

        count_times=count_times+1;
        if(count_times>5 || binary_codes[i+1]==2)
        {
            putc(ascii+60,fp);
            count_times=1;
            ascii=0;
        }

        }
    }

    fclose(fp);

}

// FUNCTIONS FOR RSA

int prime(long int pr) {

	int i;

	j=sqrt(pr);

	for (i=2;i<=j;i++) {

		if(pr%i==0)

		    return 0;

	}

	return 1;

}

void ce() {

	int k;

	k=0;

	for (i=2;i<t;i++) {

		if(t%i==0)

		    continue;

		flag=prime(i);

		if(flag==1&&i!=p&&i!=q) {

			e[k]=i;

			flag=cd(e[k]);

			if(flag>0) {

				d[k]=flag;

				k++;

			}

			if(k==99)

			        break;

		}

	}

}

long int cd(long int x) {

	long int k=1;

	while(1) {

		k=k+t;

		if(k%x==0)

		    return(k/x);

	}

}

void encrypt() {

	long int pt,ct,key=e[0],k,len;

	i=0;

	len=strlen(msg);

	while(i!=len) {

		pt=mi[i];

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
	FILE *f;
	f=fopen("encrypted.txt","w");

	for (i=0;en[i]!=-1;i++)
    {
        printf("%c",en[i]);
        putc(en[i],f);
    }
    fclose(f);


}

void enc()
{
   long int pt,ct,key=e[0],k,len;

	i=0;

	len=strlen(msg);

	while(i!=len) {

		pt=mi[i];

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
}

void decrypt() {

	long int pt,ct,key=d[0],k;

	i=0;

	while(en[i]!=-1) {

		ct=temp[i];

		k=1;

		for (j=0;j<key;j++) {

			k=k*ct;

			k=k%n;

		}

		pt=k+96;

		mi[i]=pt;

		i++;

	}

	mi[i]=-1;

	printf("\nTHE DECRYPTED MESSAGE IS\n");
    FILE *f;
	f=fopen("decrypted.txt","w");
	for (i=0;mi[i]!=-1;i++)
    {
        printf("%c",mi[i]);
        putc(mi[i],f);
    }
    fclose(f);

}

// socket code
void send_file(FILE *fp, int sockfd){
  int n;
  char data[SIZE] = {0};

  while(fgets(data, SIZE, fp) != NULL) {
    if (send(sockfd, data, sizeof(data), 0) == -1) {
      perror("[-]Error in sending file.");
      exit(1);
    }
    bzero(data, SIZE);
  }
}

void write_file(int sockfd){
  int n;
  FILE *fp;
  char *filename = "encrypted.txt";
  char buffer[SIZE];

  fp = fopen(filename, "w");
  while (1) {
    n = recv(sockfd, buffer, SIZE, 0);
    if (n <= 0){
      break;
      return;
    }
    fprintf(fp, "%s", buffer);
    bzero(buffer, SIZE);
  }
  return;
}

int main()
{

        printf("******************************* L-cent ************************************** \n");

        printf("----------- 1. HUFFMAN + RSA \t 2. SOCKET PROGRAMMING \t 3. EXIT---------------- \n");
        int select;
        scanf("%d",&select);

        if(select==1)
        {
        int choice;
        printf("\nENTER STRING: ");
        getchar();
        char str[1000];

            fgets(str,1000,stdin);
            int length=0;
            while(str[length]!='\0')
            {
                length=length+1;
            }
            table_generation(str,length);


        // APPLYING RSA ON THE GENERATED COMPERESSED FILE
   printf("\n\n$$$$$$$$$$$ ENCRYPTING ENCODED SEQUENCE $$$$$$$$$$$$$$ ");

	printf("\nENTER FIRST PRIME NUMBER\n");

	scanf("%d",&p);

	flag=prime(p);

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


     FILE *fip;int x=0;
    fip=fopen("compressed.txt","r");

    int c=getc(fip);
    while(c!=EOF)
    {
        msg[x]=c;
        c=getc(fip);
        x++;
    }



	for (i=0;msg[i]!=NULL;i++)

	mi[i]=msg[i];

	n=p*q;

	t=(p-1)*(q-1);

	ce();

	printf("\nPOSSIBLE VALUES OF e AND d ARE\n");

	for (i=0;i<j-1;i++)

	printf("\n%ld\t%ld",e[i],d[i]);

	encrypt();

	// ONLY ENCRYPTION PART HAS TO BE RUN FOR THE SAFTEY
	decrypt();

	printf("\n\n*********************** PERFORMING SOCKET PROGRAMMING ***********************\n");
    printf("YOU ARE BEHAVING LIKE A CLIENT RIGHT NOW.......");

    // client code here

                      char *ip = "127.0.0.1";
                  int port;
                  printf("ENTER PORT:");
                  scanf("%d",&port);
                  int ea;

                  int sockfd;
                  struct sockaddr_in server_addr;
                  FILE *fp;
                  char *filename = "encrypted.txt";

                  sockfd = socket(AF_INET, SOCK_STREAM, 0);
                  if(sockfd < 0) {
                    perror("[-]Error in socket");
                    exit(1);
                  }
                  printf("[+]Server socket created successfully.\n");

                  server_addr.sin_family = AF_INET;
                  server_addr.sin_port = port;
                  server_addr.sin_addr.s_addr = inet_addr(ip);

                  ea = connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr));
                  if(ea == -1) {
                    perror("[-]Error in socket");
                    exit(1);
                  }
                 printf("[+]Connected to Server.\n");

                  fp = fopen(filename, "r");
                  if (fp == NULL) {
                    perror("[-]Error in reading file.");
                    exit(1);
                  }

                  send_file(fp, sockfd);
                  printf("[+]File data sent successfully.\n");

                  printf("[+]Closing the connection.\n");
                  close(sockfd);


        }
        else if(select==2)
        {
             int choice;
             printf("1. CLIENT \n2. SERVER");
             scanf("%d",&choice);

             if(choice==1)
             {

                 // CLIENT CODE
                  char *ip = "127.0.0.1";
                  int port;
                  printf("ENTER PORT:");
                  scanf("%d",&port);
                  int eb;

                  int sockfd;
                  struct sockaddr_in server_addr;
                  FILE *fp;
                  char *filename = "encrypted.txt";

                  sockfd = socket(AF_INET, SOCK_STREAM, 0);
                  if(sockfd < 0) {
                    perror("[-]Error in socket");
                    exit(1);
                  }
                  printf("[+]Server socket created successfully.\n");

                  server_addr.sin_family = AF_INET;
                  server_addr.sin_port = port;
                  server_addr.sin_addr.s_addr = inet_addr(ip);

                  eb = connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr));
                  if(eb == -1) {
                    perror("[-]Error in socket");
                    exit(1);
                  }
                 printf("[+]Connected to Server.\n");

                  fp = fopen(filename, "r");
                  if (fp == NULL) {
                    perror("[-]Error in reading file.");
                    exit(1);
                  }

                  send_file(fp, sockfd);
                  printf("[+]File data sent successfully.\n");

                  printf("[+]Closing the connection.\n");
                  close(sockfd);
             }
             else
             {
                 //SERVER CODE

                  char *ip = "127.0.0.1";
                  int port;
                  printf("ENTER PORT:");
                  scanf("%d",&port);
                  int e;

                  int sockfd, new_sock;
                  struct sockaddr_in server_addr, new_addr;
                  socklen_t addr_size;
                  char buffer[SIZE];

                  sockfd = socket(AF_INET, SOCK_STREAM, 0);
                  if(sockfd < 0) {
                    perror("[-]Error in socket");
                    exit(1);
                  }
                  printf("[+]Server socket created successfully.\n");

                  server_addr.sin_family = AF_INET;
                  server_addr.sin_port = port;
                  server_addr.sin_addr.s_addr = inet_addr(ip);

                  e = bind(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr));
                  if(e < 0) {
                    perror("[-]Error in bind");
                    exit(1);
                  }
                  printf("[+]Binding successfull.\n");

                  if(listen(sockfd, 10) == 0){
                 printf("[+]Listening....\n");
                 }else{
                 perror("[-]Error in listening");
                    exit(1);
                 }

                  addr_size = sizeof(new_addr);
                  new_sock = accept(sockfd, (struct sockaddr*)&new_addr, &addr_size);
                  write_file(new_sock);
                  printf("[+]Data written in the file successfully.\n");


                 printf("\n\n$$$$$$$$$$$ DECRYPTING MESSAGE $$$$$$$$$$$$$$ ");

                 printf("\nENTER FIRST PRIME NUMBER\n");

                 scanf("%d",&p);

                flag=prime(p);

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
                }FILE *fp;int x=0;
                fp=fopen("/client/compressed.txt","r");//set location of compressed file

                int c=getc(fp);
                while(c!=EOF)
                {
                    msg[x]=c;
                    c=getc(fp);
                    x++;
                }

                for (i=0;msg[i]!=NULL;i++)

                mi[i]=msg[i];

                n=p*q;

                t=(p-1)*(q-1);

                ce();

                printf("\nPOSSIBLE VALUES OF e AND d ARE\n");

                for (i=0;i<j-1;i++)

                printf("\n%ld\t%ld",e[i],d[i]);

                enc();// code for encrypt:

                decrypt();

                printf("\n\n###################  DECOMPRESSING THE SEQUENCE ################ \n");
                FILE *f;
                f=fopen("decrypted.txt","r");
                int chr=getc(f);
                while(chr!=EOF)
                {
                    int result[5]={0},mo=0;
                    int v=chr-60;
                    while(v!=1)
                    {
                        result[mo]=v%2;
                        v=v/2;
                        mo=mo+1;
                    }result[mo]=v;

                    for(int f=0;f<5;f++)
                        printf("%d",result[f]);
                    chr=getc(f);
                }

                fclose(f);
            }
        }
        else
        {}

    return 0;
}
