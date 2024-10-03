#include <stdlib.h>
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

char *strncpy_alloc(char *dst, const char *src, size_t sz) {
    //If dst is null, allocate memory for it
    if (dst == NULL) {
		
        //Allocate memory for the new destination array
        dst = (char*)malloc(sz*sizeof(char));
        if (dst == NULL) {
            //Handle memory allocation failure
            return NULL;
        }
    }

    //Use the previously defined strncpy to copy from src to dst
    strncpy(dst, src, sz);

    return dst;
}

void main(){
    char src[] = "Test String";
	char *null_dst_res;
	
	//Copy part of the string to null dst
	null_dst_res = strncpy_alloc(NULL, src, 9);
	printf("Copied string: %s\n", null_dst_res);
	
	//Copy full string including terminator to null dst
	null_dst_res = strncpy_alloc(NULL, src, 11+1);
    printf("Copied string: %s\n", null_dst_res);
	
	//Copy full string and pad the rest to null dst
	null_dst_res = strncpy_alloc(NULL, src, 20);
    printf("Copied string: %s\n", null_dst_res);
}