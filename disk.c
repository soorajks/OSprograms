#include<stdio.h>
#include<sys/vfs.h>

void main()
{	int status;
	
    struct statfs info;

	status=statfs("/dev/sda1",&info);

	printf("Total No. of Blocks : %d \n",info.f_blocks);
	printf("Total disk space: %d \n",(info.f_blocks*info.f_bsize));
	printf("Total No. of Free Blocks : %d \n",info.f_bfree);
	printf("Free spcace : %d \n",(info.f_bsize*info.f_bfree));
	printf("disk usage: %d \n",(info.f_blocks*info.f_bsize)-(info.f_bsize*info.f_bfree));
	printf("Total No. of Files : %d \n",info.f_files);
	printf("TOTAL : %d \n\n",info.f_ffree);
}

