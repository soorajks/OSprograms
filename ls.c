//Program implementing Ls Command of Unix To Display The Contents Of The HardDisk

#include<stdio.h>
#include<stdlib.h>
#include<dirent.h>

void main(int argc, char *argv[])
{
	DIR *lan;
	struct dirent *wan;
	if(argc<2)
	{	lan=opendir(".");
	}
	else
	{	lan=opendir(argv[1]);
	}
	while(wan=readdir(lan))
	{	if(wan->d_name[0]!='.')
 		{	printf("%s \t", wan->d_name);
		}
	}
	closedir(lan);
	printf("\n");
}

/*
	OUTPUT
===============
./a.out /

tmp		initrd.img		lost+found	 	vmlinuz		var		cdrom	 	boot 	selinux
srv		vmlinuz.old		run		media		mnt		opt		initrd.img.old		bin
proc 	dev 	root 	home 	sbin 	etc 	sys 	usr 	lib 	

*/
