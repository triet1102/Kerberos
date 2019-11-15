#ifndef CREATEMASK_H_   
#define CREATEMASK_H_

#include <string.h>

//function use to create mask for encryption and decryption 

//suppose we have mask.length = letter.length
//mask is created in main.c by using calloc/malloc
void createMask(char * key, char * mask ,char * letter){
	int i = 0, j = 0;
	
	//length of letter
	int length1 = strlen(letter);
	
	//length of key
	int length2 = strlen(key);
	for (i = 0; i < length1; i++){
		mask[i] = key[j];
		j++;
		if (j == length2) j = 0;
	}
	mask[length1] = '\0';
}

#endif
