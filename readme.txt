How to Compile/use code
    - Use make command to open two terminals, one will be server side, one will be client side
    - Use command ./server followed by your target word on one of the terminals, then on the other use the command ./client followed by "test.txt" 
    (for the file given to us for the assignment)
Design of code
    - The code is designed to allow the server to take one command line arg and the client to take one as well, server will take in the target word, client will take in the file name.
    - The client side then takes the .txt file assiged to "fp" and opens it so we can read each line and send it over to the server side.
    - If fp is unable to be opened, then we give an error message. 
    - This file is then sent over to the server side so that it can go through all of the lines and pass it to the function "toLowerCase" so that we can determine if a line 
    contains the word or not.
    - If the function toLowerCase returns true, then we know the string is found in the line, we will output the line.
    - After we determine all of the lines that contain our target word, we then pass them back over to the client side for output.
Problems encountered
    - Passing char * back and forth was brutal, especially figuring out how to get certain lines into another array to pass to the client or server side. 
        - Figured this out by using strcpy and .c_str() functions to get the strings over to character arrays.
    - Figuring out how to pass command line args to server and client side, struggled with this one for a bit even thought it's very simple.
        - This was solved by realizing that I didnt have to pass & to ./server in order for it to compile correctly.
IPC methods
    - bind is necessary when creating a new socket because it basically links the socket to memory, as well as memset.
    - Accept is accepting a connection and this is key when communicating between a server side and client side.
    - write and read are essential for passing information back and forth between the two sides.
