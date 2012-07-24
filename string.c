/*
Count the n. of vowels in given string
-----------------------------------------
C-program for fork using

 1. Count no of words when child process is executing

 2. Count no of vowels when parent process is executing

*/

#include<stdio.h>
#include<unistd.h>
#include<string.h>

char s[50];
void count_words();
void count_vowels();

int main(void)
{
  int pid;
  int i,j;
  printf("\nEnter a string::");
  gets(s);
  pid=fork();
  if(pid==0)
  {    
                         
        printf("\nChild Process is Executing");
        printf("\nProcess ID = %d\nParent ID = %d",getpid(),getppid());
        count_words();
        printf("\n\n");
   }
   else
   {    
         printf("\nParent Process is Executing");
         printf("\nProcess ID= %d\nParent ID= %d",getpid(),getppid());
         count_vowels();
         printf("\n\n");
    }


        return 0;
}



void count_words()
{
   int i,j,k;
   int count=1;
   
   for(i=0;i<strlen(s);i++)
   {
    if(s[i]==32)
    {
        count++;
    }
   }   
     printf("\nThe No of Words in String::%d",count);


}


void count_vowels()
{
  int i,j,k;
  int count=0;
  for(i=0;i<strlen(s);i++)
  {
    if(s[i]=='a'||s[i]=='A'||s[i]=='e'||s[i]=='E'||s[i]=='i'||s[i]=='I'||s[i]=='o'||s[i]=='u'||s[i]=='U')
    {
        count++;
    }
  }

    printf("\nThe No Vowels in String :: %d",count);
}


