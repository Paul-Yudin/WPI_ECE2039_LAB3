#include <stdio.h>

char *strncpy(char *dst, const char *src, size_t sz){
    //Define character counter
	size_t i;
    
	//Copy characters from 'src' to 'dst' until either 'sz' characters 
    //have been copied or the end of 'src' (null character) is reached
    for (i = 0; i < sz && src[i] != '\0'; i++) {
        dst[i] = src[i];
    }
	
	//If 'src' is shorter than 'sz', pad the remainder of 'dst' with '\0' (null characters)
    for (; i < sz; i++) {
        dst[i] = '\0';
    }
	
	return dst;
}

void main(){
    char src[] = "Test String";
    char dst[50];
	
	//Copy part of the string
    strncpy(dst, src, 9);
    printf("Copied string: %s\n", dst);
	
	//Copy full string including terminator
    strncpy(dst, src, 11+1);
    printf("Copied string: %s\n", dst);
	
	//Copy full string and pad the rest
	strncpy(dst, src, 20);
    printf("Copied string: %s\n", dst);
}