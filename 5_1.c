#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#define Buf_rozmiar 256
int main(int argc, char *argv[]) {

	pid_t pid;
	int fd[2], in_fd, n;
	char buf [Buf_rozmiar];

	if(pipe(fd)<0)//sprawdzanie pipe
        {
        fprintf(stderr, "eror\n");
        }

	pid = fork();//tworzenie syna

	if(pid==0)//syn
		{
		close(fd[1]);
		while(read(fd[0],&buf,1)>0)//wyswietlanie terminala
            {
                write(STDOUT_FILENO,"#",1);
                write(STDOUT_FILENO,&buf,1);
                write(STDOUT_FILENO,"#",1);
                write(STDOUT_FILENO, "\n",1);
            }
            close(fd[0]);
		}

	else if(pid>0)//rodzic
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
    close (in_fd);
	}
}
