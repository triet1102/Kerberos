#ifndef ENCRYPT_H_   
#define ENCRYPT_H_

#include <string.h>
#include "createMask.h"

//function use to encrypt message

//letter.length == mask.length == letterEnc.length

char * encrypt(char * key, char * letter){
	char * alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789@.,!?:;-=%";
	int len = strlen(letter);
	char * mask = (char*)calloc(len, sizeof(char));
	char * letterEnc = (char*)calloc(len, sizeof(char));
	createMask(key, mask , letter);
	char *tmp1, *tmp2;
	int i = 0, length1 = 0, index = 0, index1 = 0, index2 = 0;
	length1 = strlen(letter);
	for (i = 0; i < length1; i ++){
		tmp1 = strchr(alphabet, letter[i]);
		index1 = (int)(tmp1 - alphabet); 
		
		tmp2 = strchr(alphabet, mask[i]);
		index2 = (int)(tmp2 - alphabet);
		
		index = (index1 + index2)%72;
		letterEnc[i] = alphabet[index];
	}
	letterEnc[length1] = '\0';
	letter = letterEnc;
	return letter;
}

#endif
