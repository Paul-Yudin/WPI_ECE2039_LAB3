#include <stdio.h>
#include <ctype.h>

int main() {
    FILE *fp = fopen("ssl_lib.c", "r"); //Open ssl_lib.c in read-only mode
    if (fp == NULL) {
        perror("Error opening ssl_lib.c");
        return 1;
    }

    int c;
    int line_count = 0;
    int word_count = 0;
    int byte_count = 0;
    int in_word = 0;

    //Read characters from the file until EOF
    while ((c = getc(fp)) != EOF) {
		//Count bytes
        byte_count++;

        //Count lines
        if (c == '\n') {
            line_count++;
        }

        //Count words
		//Check for letters, numbers, or symbols
		if (0x20 < c && c < 0x7F){
			if (!in_word) {
				//Start of a new word
                in_word = 1;
                word_count++;
            }
		}
		else{
			if (in_word) {
				//End of a word
                in_word = 0;
            }
		}
    }

    //Print the results
    printf("%d %d %d ssl_lib.c\n", line_count, word_count, byte_count);

    //Close the file
    fclose(fp);
    return 0;
}
