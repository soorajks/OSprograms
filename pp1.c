#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main()
{
int id,pd[2];
char buf[20];
pipe(pd);
id= fork();
if(id<0)
{
printf("Child can not be created");
exit(-1);
}
if(id==0)
{
printf("Enter server message : ");
scanf("%s",buf);
write(pd[1],buf,20);
sleep(1);
lseek(pd[0],0,SEEK_SET);
read(pd[0],buf,20);
printf("\nclient1 reads message : %s",buf);
lseek(pd[0],0,SEEK_SET);
read(pd[0],buf,20);
printf("\nclient2 reads message : %s",buf);

}
else
{
lseek(pd[0],0,SEEK_SET);
read(pd[0],buf,20);
printf("\nclient1 reads message : %s",buf);
printf("\nclient2 reads message : %s",buf);
printf("\nEnter client1 message : ");
scanf("%s",buf);
write(pd[1],buf,20);
sleep(1);
printf("\nEnter client2 message : ");
scanf("%s",buf);
write(pd[1],buf,20);
}
}
