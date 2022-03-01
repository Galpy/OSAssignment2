 #include <stdio.h>
       #include <stdlib.h>
       #include <string.h>
       #include <sys/socket.h>
       #include <sys/un.h>
       #include <unistd.h>
       #include "connection.h"
       #include "toLowerCase.h"
       #include <stdio.h>
       #include <omp.h>
       using namespace std;

       int
       main(int argc, char *argv[])
       {
           struct sockaddr_un name;
           int down_flag = 0;
           int ret;
           int connection_socket;
           int data_socket;
           string resultLines;
           char line[BUFFER_SIZE];
           char fileString[BUFFER_SIZE];
           char buffer[BUFFER_SIZE];
           char finalString[BUFFER_SIZE];

           
           /* Create local socket. */

           connection_socket = socket(AF_UNIX, SOCK_SEQPACKET, 0);
           cout << "Socket Created" << endl;
           if (connection_socket == -1) {
               perror("socket");
               exit(EXIT_FAILURE);
           }

           /*
            * For portability clear the whole structure, since some
            * implementations have additional (nonstandard) fields in
            * the structure.
            */

           memset(&name, 0, sizeof(struct sockaddr_un));
           cout << "Memset done" << endl;

           unlink(SOCKET_NAME);

           /* Bind socket to socket name. */

           name.sun_family = AF_UNIX;
           strncpy(name.sun_path, SOCKET_NAME, sizeof(name.sun_path) - 1);
           ret = bind(connection_socket, (const struct sockaddr *) &name,
                      sizeof(name));
           if (ret == -1) {
               perror("bind");
               exit(EXIT_FAILURE);
           }

           /*
            * Prepare for accepting connections. The backlog size is set
            * to 20. So while one request is being processed other requests
            * can be waiting.
            */
           
           ret = listen(connection_socket, 20);
           cout << "Listen Done" << endl;
           if (ret == -1) {
               perror("listen");
               exit(EXIT_FAILURE);
           }

           /* This is the main loop for handling connections. */

           for (;;) {


               /* Wait for incoming connection. */
               data_socket = accept(connection_socket, 0, 0);
               if (data_socket == -1) {
                   perror("accept");
                   exit(EXIT_FAILURE);
               }

               for (;;) {

                   /* Wait for next data packet. */
                    
                   ret = read(data_socket, buffer, sizeof(buffer));
                   if (ret == -1) {
                       perror("read");
                       exit(EXIT_FAILURE);
                   }

                   /* Handle commands. */

                   if (!strncmp(buffer, "DOWN", sizeof(buffer))) {
                       cout << "DOWN CALLED" << endl;
                       down_flag = 1;
                       break;
                   }

                   if (!strncmp(buffer, "END", sizeof(buffer))) {
                       cout << "END CALLED" << endl;
                       break;
                   }

                   /* Add received summand. */  
                   if (argv[1] == NULL) {
                       cout << "You have not entered in a target word" << endl;
                   }else {
                        string input = argv[1];
                   
                    strcpy(fileString,input.c_str());
                            if (toLowerCase(buffer, fileString)) {
                           sprintf(finalString, "%s", buffer);
                           resultLines += finalString;
                           strcpy(line,resultLines.c_str());
                            }
                   }
                            
               }
               

               /* Send result. */
                    ret = write(data_socket, line, sizeof(finalString));
                    
           
               /* Close socket. */

               close(data_socket);

               /* Quit on DOWN command. */

               if (down_flag) {
                   break;
               }
           }

           close(connection_socket);

           /* Unlink the socket. */

           unlink(SOCKET_NAME);

           exit(EXIT_SUCCESS);
       }