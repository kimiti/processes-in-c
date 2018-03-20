#include <stdio.h>
#include <fcntl.h>
#include <signal.h>
#include <unistd.h>


int main(){
    pid_t mypid = getpid();
    int fd;
    int wd = mypid;
    ssize_t nr;

    fd = creat("agent_pid.txt",0777);
    if(fd == -1){
        printf("file has not opened");
    }else{
        printf("file has been found \n");

        nr = write(fd,&wd,sizeof(wd));
        close(fd);
    }

    if(nr == -1){
        printf("not able to write \n");
    }else{
        printf("file has %d\n",wd);
    }
    while(1){
        signal(SIGINT, reading);
        signal(SIGQUIT,terminating);
    }
}


void terminating(int sig_val){

    pid_t mypid = getpid();
    kill(mypid , SIGSTOP);
    printf("processes are terminating");
}

void reading(int sig_val){
    int fs;

    fs = open("test.txt",O_RDONLY);
    if(fs == -1){
        printf("file has not found \n");
    }
    else{
        printf("file has been found \n");
    }
    char dw[100];
    ssize_t rf;

    rf =read(fs,dw, sizeof(dw));
    if(rf == -1)
    {
        printf("file has not been read \n");
    }
    else{
        printf("file has %s \n",dw);
    }
    sleep(2000000);
}
