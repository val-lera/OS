#include<sys/wait.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int Prime(int n,int k){
    if(n==1) return 0;
    if(n>k){
        pid_t child;
        int fd[2];
        if (pipe(fd) == -1){
            write(STDERR_FILENO, "error: pipe\n", sizeof(char));
            exit(EXIT_FAILURE);
        }
        int s;
        child = fork();
        if (child > 0){
            close(fd[1]);
            wait(0);
            read(fd[0], &s, sizeof(s));
            if(s==0)
                return 0;
            else return Prime(n,k+1);
        }
        else if (child == 0){
            close(fd[0]);
            if((n%k)==0)
                s=0;
            else 
                s=1;
            write(fd[1], &s, sizeof(s));
            if(write(fd[1], &s, sizeof(s)) == -1)
                write(STDERR_FILENO, "error: write\n", sizeof(char));
            exit(0);
        }
        else 
            write(STDERR_FILENO, "error: fork\n", sizeof(char));
            exit(EXIT_FAILURE);;
    }
    else return 1;
}

int main()
{
    int n;
    printf("Введите число: ");
    scanf("%d", &n);
    if(Prime(n,2))
        printf("Число %d простое\n", n);
    else
        printf("Число %d не является простым\n", n);
    return 0;
}