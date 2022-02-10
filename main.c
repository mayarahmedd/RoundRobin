#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * Process: Each process has a name and has an execution time.
 *          We keep track of how long the process still needs
 *          to run on the processor. "remaining_time" is the
 *          remaining execution time of the process.
 */


typedef struct
{
    char *name;
    int starting_time;
    int remaining_time;
} Process;
/*
 *
 */
typedef struct Node
{
    Process data;
    struct Node* next;
} Node;
/*
 *
 */
typedef struct
{
   Node *head;
} Queue;
/*
 *
 */
Queue* init()
{
    Queue *q=malloc(sizeof(Queue));
    q->head=NULL;
    return q;
}
/*
 *
 */
int isEmpty(Queue *q)
{
   if (q->head==NULL)
    return 1;
   else
    return -1;
}
/*
 *
 */
Process dequeue(Queue *q)
{
    Node *dp=q->head;
   Process temp;
    if (q->head==NULL)
        exit(0);

   else {

    temp=q->head->data;
    q->head=q->head->next;
     free(dp);

   }

   return temp;
}
/*
 *
 */
void enqueue(Queue *q, Process val)
{
    Node *temp=q->head;

   Node *n=malloc(sizeof(Node));
   n->data=val;
   n->next=NULL;

   if (q->head==NULL)
    q->head=n;


   else
       {
           while(temp->next !=NULL)
            temp =temp->next;

            temp->next=n;
            temp =n;

       }


}

void destroy(Queue *q)
{
    while (q->head){
    Node *temp=q->head;
    q->head=q->head->next;


    free (temp);

    }


}



/*
 * RoundRobin Scheduling
 */
void RoundRobin(char* filename)
{
 Process p[100];

FILE *file;
    char g[260];
    file=fopen(filename,"r");
   int processNum=0;
   int numItems=0;
   int numSlots;



        fscanf(file,"%[^=]= %d",g,&numSlots);

        fscanf(file,"\n");




       while(!feof(file))
        {
            char str[50];
            fscanf(file,"%s %d %d ",str,&p[processNum].starting_time,&p[processNum].remaining_time);
            p[processNum].name=malloc(strlen(str)+1);
            strcpy(p[processNum].name,str);


            fscanf(file,"\n");
            processNum++;


        }
        fclose(file);



 Queue *q=init();


    int i;
    for(i=0;i<processNum;i++)
    {
        enqueue(q,p[i]);
        numItems++;

    }

    int j;
    int flag=0;
    Process temp2;
    for(i=0;i<numSlots;i++)
    {flag=0;
        for(j=0;j<numItems;j++)
        {
            temp2=dequeue(q);
            numItems--;


            if(temp2.starting_time<=i)
            {
                printf("%s (%d --> %d) ",temp2.name,i,i+1);

                temp2.remaining_time--;
                flag=1;
                if(temp2.remaining_time>0)
                {
                    enqueue(q,temp2);
                     numItems++;

                    printf("\n");
                    break;
                }

                else
                {
                    printf("%s aborts\n",temp2.name);

                    break;
                }
            }
            else
            {
                enqueue(q,temp2);
                 numItems++;


            }



        }if(flag==0)
            {
                printf("idle (%d --> %d)\n",i,i+1);



            }

    }

 destroy(q);
    printf("\nStop\n\n");



}
/*
 *
 */
int main()
{
    char filename[261];
    puts("Enter file name or Ctrl+Z to exit:");
    puts("----------------------------------");
    while(fgets(filename, 260, stdin) != NULL)
    {
        filename[strlen(filename)-1]='\0';
        if(fopen(filename,"r"))
            RoundRobin(filename);
        else
        {
            puts("File Not Found!");
            puts("----------------------------------");
        }
        puts("Enter file name or Ctrl+Z to exit:");
        puts("----------------------------------");
    }

    return 0;
}
