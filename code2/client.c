#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "createMask.h"
#include "encrypt.h"
#include "decrypt.h"
#include "intToString.h"

//function use to decrypt message from AS to client

int main (int argc, char *argv[]){
		printf("<your client key> <message encrypted>\n");
		char Client[1024];
		char messageEncrypted[1024];	
		scanf("%s",Client);
		Client[strlen(Client)] = '\0';
		scanf("%s",messageEncrypted);
		messageEncrypted[strlen(messageEncrypted)] = '\0';
		
		
		char * ticketTGS;
		ticketTGS = messageEncrypted;
		ticketTGS = decrypt(Client, ticketTGS);
		ticketTGS[strlen(messageEncrypted)] = '\0';
		printf("Your ticketTGS:\n");
		//ticket now is decrypted to client
		puts(ticketTGS);

}
