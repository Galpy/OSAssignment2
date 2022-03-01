How to Compile/use code
    - Use make command to create the file "hello" 
    - Use command ./hello followed by the .txt file you want opened and then the target word you're looking for.
    - Example: ./hello test.txt target
Design of code
    - The code is designed to take 3 command line args, first one is just the program name (ex. "./hello")
    - 2nd command line arg will be the .txt file, that will be assigned to file.
    - 3rd command line arg will be the target word, which will be assigned to the string targetWord.
    - The code then takes the .txt file assiged to "file" and opens it so we can read each line and parse through them to find the targetWord.
    - If myfile is unable to be opened, then we give an error message. 
    - The code goes through each line, using the toLowerCase() method which converts our targetWord to a regular expression e (targetWord) that is all lowercase,
 and if found, will return true. 
    - If the function toLowerCase returns true, then we know the string is found in the line, we will output the line.
    - After we reach the end of the .txt file, we close the file.
