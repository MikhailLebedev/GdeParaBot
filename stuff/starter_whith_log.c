#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <time.h>
#include <fcntl.h>
#include <dirent.h>

volatile pid_t pid;

void handler(int signal)
{
    kill(SIGKILL, 0);
    if (signal == SIGINT){
        raise(SIGKILL);
    }
}

int main(int argc, char **argv)
{
	chdir("C:\\Users\\Administrator\\Dropbox\\ChatBot");
    int status;
    time_t t;
    struct tm *aTm;
    signal(SIGINT, handler);
    signal(SIGQUIT, handler);
	int logfile;
	setvbuf(stdout, NULL, _IONBF, 0);
	printf("\n");
    if (argc < 2){
        printf("No args!\n");
    } else {
        printf("Started with arg = %s\n", argv[1]);
    }
    while(1){
		logfile = open("chat.txt", O_WRONLY | O_APPEND | O_CREAT);
		dup2(logfile, 1);
        t = time(NULL);
        aTm = localtime(&t);
        printf("%04d/%02d/%02d %02d:%02d:%02d   |   ",aTm->tm_year+1900, aTm->tm_mon+1, aTm->tm_mday, aTm->tm_hour, aTm->tm_min, aTm->tm_sec);
        printf("Starting bot ...\n");
        if(!(pid = fork())){
            printf("---------- Bot log ----------\n");
            execlp("C:\\Python34\\python", "C:\\Python34\\python", argv[1], NULL);
            exit(0);
        } else {
            wait(&status);
            printf("-----------------------------\n");
            t = time(NULL);
            aTm = localtime(&t);
            printf("%04d/%02d/%02d %02d:%02d:%02d   |   ",aTm->tm_year+1900, aTm->tm_mon+1, aTm->tm_mday, aTm->tm_hour, aTm->tm_min, aTm->tm_sec);
            printf("Bot fell! Restarting ...\n");
        }
		close(logfile);
    }
    return 0;
}
