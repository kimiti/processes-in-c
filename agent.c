#include <stdio.h>
#include <fcntl.h>
#include <signal.h>
#include <unistd.h>


int pidsco;

void sendSIGTERM(int sig_val);
void sendSIGTERMQ(int sig_val);

int main(){
    int fd;
    fd = open("agent_pid.txt",O_RDONLY);
    if(fd == -1){
        printf("file has not opened \n");
    }else{
        printf("agent pid found \n");
    }

    ssize_t rn;

    rn = read(fd,&pidsco, sizeof(pidsco));
    if(rn == -1)
    {
        printf("file not read \n");
    }
    else{
        printf("this agent pid is %d \n", pidsco);
    }

    int check = kill(pidsco,0);
    if(check == -1){
        printf("agent does not exist \n");
        pid_t mypid = getpid();
        kill(mypid,SIGSTOP);
    }else{
        printf("agent exists \n");
        while(1){
            printf("select a signal to send between SIGINT and SIGQUIT: \n");
            sleep(5);
            signal(SIGINT, sendSIGTERM);
            signal(SIGQUIT, sendSIGTERMQ);
        }
    }
}

void sendSIGTERM(int sig_val)
{
    pid_t agent_pid = pidsco;
    kill(agent_pid, SIGTERM);
    printf("agent stopped \n");
    }

void sendSIGTERMQ(int sig_val)
{
    pid_t agent_pid =pidsco;
    kill(agent_pid, SIGTERM);
    printf("agent stopped \n");
    pid_t mypid = getpid();
    printf("i am terminating now \n");
    kill(mypid, SIGSTOP);
}