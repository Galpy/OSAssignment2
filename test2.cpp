#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/shm.h>
#include <signal.h>

int main(int argc, const char * argv[]) {
    char *p;
    int shmid;

    shmid = shmget(IPC_PRIVATE, 128, 0777);

    return 0;
}