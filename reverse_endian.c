#include<stdio.h>

int reverse_endian(int n);

void main(){}

//Function to reverse the endian format of a 32-bit integer
int reverse_endian(int n) {
    int reversed = 0x00; //To store the reversed value
    const int total_bytes = 4; //Assuming a 32-bit (4-byte) integer
    
    //Loop through each byte in the integer
    for (int i = 0; i < total_bytes; i++) {
        //Extract the current byte by shifting and masking with 0xFF
        int current_byte = (n >> (i * 8)) & 0xFF;
        
        //Shift the byte to its new reversed position
        current_byte = current_byte << ((total_bytes - 1 - i) * 8);
        
        //Combine the current byte with the reversed result
        reversed = reversed | current_byte;
    }
    
    return reversed;
}