#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/shm.h>
#include <signal.h>
#include <fstream>
#include <iostream>
#include "toLowerCase.h"

using namespace std;

int main(int argc, const char * argv[]) {

    int fd1[2];
    int fd2[2];
    ifstream myfile;
    string file, stringLine, targetWord;
    file = argv[1];
    targetWord = argv[2];
    cout << "File Name: " << file << endl;

    if (pipe(fd1) < 0) {
        cout << "Failed to create a pipe\n" << endl;
        return -1;
    }

    if (pipe(fd2) < 0) {
        cout << "Failed to create a pipe\n" << endl;
        return -1;
    }

    int pid = fork();

    if (pid > 0) {

        char targetString[100];
        char line[100];

        close(fd1[0]);
        myfile.open(file);
        if (!myfile) {
            cout << "File was unable to be opened" << endl;
        }
        else {
            while (getline (myfile, stringLine)) {
                for (int i = 0; i <= stringLine.length(); i++) {
                    line[i] = stringLine[i];
                }
                    write(fd1[1], line, strlen(line));
                    close(fd1[1]);
            }
        }
        wait(NULL);

        close (fd2[1]);

        read(fd2[0], targetString, 100);
        cout << targetString << endl;
        close(fd2[0]);
    } else {
        close(fd1[1]);
        char line[100];
        string targetLine = "";

        read(fd1[0], line, 100);
        

        for (int i = 0; i < sizeof(line); i++) {
            targetLine += line[i];
        }
        cout << "This is targetLine: " << line << endl;
        cout << "This is target word: " << targetWord << endl;
        if (toLowerCase(targetLine, targetWord)) {
            write(fd2[1], line, strlen(line) +1);
            close(fd2[1]);
        // } else {
        //     return;
        // }
        }
        close(fd2[0]);

        waitpid(pid, NULL, 0);
        }

    return 0;
    }