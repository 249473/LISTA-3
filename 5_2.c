#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#define Buf_rozmiar 256
int main(int argc, char *argv[]) {

	pid_t pid;
	int fd[2], in_fd, n;
	char buf [Buf_rozmiar];

	if(pipe(fd)<0)
        {
        fprintf(stderr, "eror\n");
        }

	pid = fork();

	if(pid==0)
		{
		close(fd[1]);
		close(0);
		dup(fd[0]);
		close(fd[0]);
		execlp("display","display","-",NULL);
            //close(fd[0]);
		}

	else if(pid>0)
	{
		close(fd[0]);
		//scanf("%s",fname);
		if((in_fd=open(argv[1],O_RDONLY))<0)
			{
			fprintf(stderr,"eror\n");
			return 2;
			}

	while ((n= read(in_fd, &buf,Buf_rozmiar))>0){
		if(write(fd[1],&buf,n)<0){
			fprintf(stderr,"eror\n");
			return 3;
			}

		}
	sleep(1);  
	close(fd[1]);  
	close (in_fd);
	
	}
}

