#include <stdio.h>
int main(int argc, char** argv) {
    if (argc < 4) {
        printf("ex - ./myTr -t abc ABC \"<\" text.txt\n");
        printf("ex - ./myTr -d abc \"<\" text.txt\n");
        return 0;
    }
    FILE* fp = NULL;
    char buf[1024];
    int i = 0, j = 0, k = 0, size = 0;
    switch (argv[1][1]) {   // checks option argv[1][1] is either 't' or 'd'
    case 't':   // if option entered is 't'
       // argv[1] has option (-t)
        // argv[2] has from_characters
        // argv[3] has to characters
        // argv[4] is <
        // argv[5] is filename
        printf("file - %s\n", argv[5]);   // print filename
        fp = fopen(argv[5], "r");   // open file to read
        if (fp != NULL) {   // if file was successfully opened to read
            while ((buf[i++] = fgetc(fp)) != EOF)   // get all characters from file into buf character array, i contains size of file
                ;
            fclose(fp);   // close file
        }
        else
            printf("File is not exist\n");   // if file does not exists, show a message
        size = i;   // set size to i, because i contains size of the file
        for (i = 0; argv[2][i]; i++) //check character one by one from argv[2]
        {
            for (j = 0; j < size; j++) {   // iterate through all characters of file
                if (buf[j] == argv[2][i]) // if character match
                    buf[j] = argv[3][i]; // replace with new character
            }
        }
        printf("%s", buf); //print edited data on the screen
        fp = fopen(argv[5], "w"); //open file in write mode
        if (fp != NULL) {   // if file was succesfully opened to write
            fputs(buf, fp); //put buffer data in file
            fclose(fp);   // clse file
        }
        else
            printf("File can not open for write\n"); // display if file is not exist
        break;
    case 'd':   // if option entered in 'd'
    // argv[1] has option (-d)
    // argv[2] has characters to delete
    // argv[3] is <
    // argv[4] is filename
        fp = fopen(argv[4], "r");   // open file to read
        if (fp != NULL) {// if file was successfully opened to read
            while ((buf[i++] = fgetc(fp)) != EOF)// get all characters from file into buf character array, i contains size of file
                ; //read all data in buffer
            fclose(fp);// close file
        }
        else
            printf("File is not exist\n");// if file does not exists, show a message
        size = i;// set size to i, because i contains size of the file
        for (i = 0; argv[2][i]; i++) {//check character one by one from argv[2]
            for (j = 0; j < size; j++) {// iterate through all characters of file
                if (buf[j] == argv[2][i]) //if character match remove it
                {
                    for (k = j; k < size; k++) {
                        buf[k] = buf[k + 1];
                    }
                }
            }
        }
        printf("%s", buf); //print edited buffer
        fp = fopen(argv[4], "w"); //open file in write mode so data truncate
        if (fp != NULL) {
            fputs(buf, fp); // puf buffer data in file
            fclose(fp);
        }
        else
            printf("File can not open for write\n");
        break;
    default:
        printf("Wrong Option\n"); //display if wrong option selected
        break;
    }
}