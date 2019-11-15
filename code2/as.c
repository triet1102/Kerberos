#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "createMask.h"
#include "encrypt.h"
#include "decrypt.h"
#include "intToString.h"

//keys of Client1 and key of Client2
char * Client1 = "8Rqn094QQ"; 
char * Client2 = "u%!j:Vn";    

//keys shared between AS and TGS1 TGS2
char * TGS1 = "ab5utiqp";
char * TGS2 = "fis30@Flq";    

int main (int argc, char *argv[]){
	printf("<IDc> <ADc> <IDtgs>\n");
	
	char IDc[1024], ADc[1024], IDtgs[1024];
	char *keyClient, *keyTGS;
	
	
	//get IDc ADc IDtgs
	scanf("%s", IDc);
	IDc[strlen(IDc)] = '\0';
	scanf("%s", ADc);
	ADc[strlen(ADc)] = '\0';
	scanf("%s", IDtgs);
	IDtgs[strlen(IDtgs)] = '\0';
	
	
   	//check client ID
   	if (strcmp("Client1", IDc) == 0){
   		keyClient = Client1;
   	}else if (strcmp("Client2", IDc) == 0){
   		keyClient = Client2;
   	}else {
   		printf("Unknow Client!\n");
   		exit(1);
   	}
   	
   	//check TGS ID
	if (strcmp("TGS1", IDtgs) == 0){
   		keyTGS = TGS1;
   	}else if (strcmp("TGS2", IDtgs) == 0){
   		keyTGS = TGS2;
   	}else {
   		printf("Unknow TGS!\n");
   		exit(1);
   	}
   	
   	time_t seconds;
   	char TS[20];
   	char * duree = "3600";
   	char ticketTGS_before[1024] = {};
   	
   	//get current time
   	seconds = time(NULL);
   	intToString(seconds,TS); 
   	TS[strlen(TS)] = '\0';
   	
   	//generate ticketTGS_before = [IDC||ADC||IDtgs||TS1||Duree1]
   	strcat(ticketTGS_before, IDc);
   	strcat(ticketTGS_before, "-");
   	strcat(ticketTGS_before, ADc);
   	strcat(ticketTGS_before, "-");
   	strcat(ticketTGS_before, IDtgs);
   	strcat(ticketTGS_before, "-");
   	strcat(ticketTGS_before, TS);
   	strcat(ticketTGS_before, "-");
   	strcat(ticketTGS_before, duree);
   	int len = strlen(ticketTGS_before);
   	ticketTGS_before[len] = '\0';
   	//generate TicketYGS = E(Ktgs,ticketTGS_before)
   	char * ticketTGS = ticketTGS_before;
   	ticketTGS = encrypt(keyTGS,ticketTGS);
	ticketTGS[len] = '\0';
	
	//message from AS to Client = E(Kc, ticketTGS)
   	char * messageAStoClient;
   	messageAStoClient = ticketTGS;
   	messageAStoClient = encrypt(keyClient,ticketTGS);
   	messageAStoClient[len] = '\0';
   	printf("Message encrypt ticketTGS with client's key:\n");
	printf("%s\n",messageAStoClient);

}



