#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<sys/stat.h>
#include <fcntl.h>
#include<unistd.h>


int main(){
	int pid = fork();
	if(pid < 0){
		perror("fork");
		return 1;
	}else if(pid == 0){
		printf("child process with pid: %d\n",getpid());
		exit(0);
	}else{
		printf("parent proces. child process with pid: %d\n",pid);
		wait(NULL);
	}	
	
	int fd = open("demo.txt",O_RDWR);
	if(fd < 0){
		perror("write");
		close(fd);
		return 1;
	}
	char buffer[] = "Operating System is ezzy pezzy\n";
	int size = write(fd,buffer,sizeof(buffer));
	close(fd);
	
	char read_buffer[1024];
	fd = open("demo.txt",O_RDONLY);
	int bytes = read(fd,read_buffer,sizeof(read_buffer));
	close(fd);
	printf("Data readed from file: %.*s\n",(int)bytes,read_buffer);
	
	system("ls -l demo.txt");
	if(chmod("demo.txt",0775) != 0){
		perror("chmod");
		return 1;
	}
	system("ls -l demo.txt");
 	return 0;
}