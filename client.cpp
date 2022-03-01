 #include <errno.h>
       #include <stdio.h>
       #include <stdlib.h>
       #include <string.h>
       #include <sys/socket.h>
       #include <sys/un.h>
       #include <unistd.h>
       #include "connection.h"
       #include <fstream>
       #include <iostream>
       using namespace std;

       int
       main(int argc, char *argv[])
       {
           struct sockaddr_un addr;
           int ret;
           int data_socket;
           char buffer[BUFFER_SIZE];
           string fileString;
           string file, stringLine, inputLines;
           FILE *fp = fopen(argv[1],"r");

           /* Create local socket. */

           data_socket = socket(AF_UNIX, SOCK_SEQPACKET, 0);
           if (data_socket == -1) {
               perror("socket");
               exit(EXIT_FAILURE);
           }

           /*
            * For portability clear the whole structure, since some
            * implementations have additional (nonstandard) fields in
            * the structure.
            */

           memset(&addr, 0, sizeof(addr));

           /* Connect socket to socket address. */

           addr.sun_family = AF_UNIX;
           strncpy(addr.sun_path, SOCKET_NAME, sizeof(addr.sun_path) - 1);

           ret = connect(data_socket, (const struct sockaddr *) &addr,
                          sizeof(addr));
           if (ret == -1) {
               fprintf(stderr, "The server is down.\n");
               exit(EXIT_FAILURE);
           }

           /* Send arguments. */
                int ch = 0;
                int lines = 0;
                do {
                    ch = fgetc(fp);
                    if (ch == '\n')
                        lines++;
                } while (ch != EOF);

                rewind(fp);

                char* contents[lines];
                int i = 0;
                size_t len = 0;
                for (i = 0; i <= lines; i++) {
                    contents[i] = NULL;
                    len = 0;
                    getline(&contents[i], &len, fp);
                        ret = write(data_socket, contents[i], sizeof(buffer));
                }
                fclose(fp);
                    
           /* Request result. */
            strcpy(buffer, "END");
           ret = write(data_socket, buffer, strlen(buffer) + 1);
           cout << "Client write END" << endl;

           /* Receive result. */

           ret = read(data_socket, buffer, sizeof(buffer));
           if (ret == -1) {
               perror("read");
               exit(EXIT_FAILURE);
           }

           /* Ensure buffer is 0-terminated. */

           printf("Result = %s\n", buffer);

           /* Close socket. */

           close(data_socket);

           exit(EXIT_SUCCESS);
       }