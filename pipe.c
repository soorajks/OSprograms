#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

void main()
{
	int id, pipefd[2];
	char buffer[20];
	
    pipe(pipefd);
	id = fork();
    
    if(id < 0)
	{   printf("Process cannot be created!!!\n");
		exit(-1);
	}

      if(id == 0)
	    {	printf("Enter END-1 message : \n");
		    scanf("%s", buffer);
		
            write(pipefd[1], buffer, 20);
		    sleep(1);
		    lseek(pipefd[0], 0 , SEEK_SET);
		    read(pipefd[0], buffer, 20);
		
            printf("END-1 reads message : %s\n", buffer);	
	    }
	    else
	    {   lseek(pipefd[0], 0 , SEEK_SET);
		    read(pipefd[0], buffer, 20);
		    
            printf("END-2 reads message : %s\n", buffer);
		    printf("Enter END-2 message : \n");
		    scanf("%s", buffer);
		    
            write(pipefd[1], buffer, 20);
            sleep(1);
	    }
    
}
