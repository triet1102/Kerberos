#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "createMask.h"
#include "encrypt.h"
#include "decrypt.h"
#include "intToString.h"

//identity IDTGS1 of server and key TGS1
char * IDTGS1 = "TGS1";
char * TGS1 = "ab5utiqp";

//keys shared between server TGS1 and servers V1 V2
char * V1 = "8rSiqp!.Q";
char * V2 = "90QjCleit=";

int main (int argc, char *argv[]){
	printf("<IDc> <ADc> <IDv> <TicketTGS>\n");
	char input[1024], *keyV, split[] = "-";
	char IDc[1024], IDcCheck[1024];
	char ADc[1024], ADcCheck[1024];
	char IDTGSCheck[1024];
	char IDv[1024];
	char ticketTGS[1024];
	
	// get IDc, ADc, IDv, ticketTGS
	scanf("%s",IDc);
	IDc[strlen(IDc)] = '\0';
	scanf("%s",ADc);
	ADc[strlen(ADc)] = '\0';
	scanf("%s",IDv);
	IDv[strlen(IDv)] = '\0';
	scanf("%s",ticketTGS);
	ticketTGS[strlen(ticketTGS)] = '\0';
	
   	//check client ID
   	if (strcmp("Client1", IDc) != 0 && strcmp("Client2", IDc) != 0){
   		printf("NON. Unknow Client.\n");
   		exit(1);
   	}

   	//get IDv and keyV
	if (strcmp("V1", IDv) == 0){
   		keyV = V1;
   	}else if (strcmp("V2", IDv) == 0){
   		keyV = V2;
   	}else {
   		printf("NON. Unknow service system V.\n");
   		exit(1);
   	}
 	
   	//generate ticketTGS_before = [IDC||ADC||IDtgs||TS1||Duree1] then copy to input
   	char *ticketTGS_before;
   	ticketTGS_before = ticketTGS;
   	ticketTGS_before = decrypt(TGS1, ticketTGS_before);
   	strcpy(input,ticketTGS_before);
   	input[strlen(input)] = '\0';
   	strcat(input, "-N-N");
   	
   	//get IDc in the ticketTGS_before 
   	char * ptr = strtok(input, split);
   	strcpy(IDcCheck, ptr);
   	IDcCheck[strlen(IDcCheck)] = '\0';

   	//get ADc in the ticketTGS_before 
   	ptr = strtok(NULL, split);
   	strcpy(ADcCheck, ptr);
   	ADcCheck[strlen(ADcCheck)] = '\0';

   	//get IDtgs in the ticketTGS_before
   	ptr = strtok(NULL, split);
   	strcpy(IDTGSCheck, ptr);
   	IDTGSCheck[strlen(IDTGSCheck)] = '\0';

	if (strcmp(IDTGSCheck, IDTGS1) != 0){
   		printf("NON. Wrong destination, I am TGS1.\n");
   		exit(1);
   	}else {
   		if (strcmp(IDcCheck, IDc) != 0){
   			printf("NON. IDc not match with IDc in your TicketTGS.\n");
   			exit(1);
   		}
   		if (strcmp(ADcCheck, ADc) != 0){
   			printf("NON. ADc not match with ADc in your TicketTGS.\n");
   			exit(1);
   		}
   	}   	
   	
   	
   	//get timestamp then verify if the ticket is expired or not
   	time_t seconds;
   	char TS[20];
   	char * duree = "3600";
   	
   	seconds = time(NULL);
   	intToString(seconds,TS); 
   	TS[strlen(TS)] = '\0';
   	
   	long timestamp = 0;
   	ptr = strtok(NULL, split);
   	timestamp = atol(ptr);
   	if (seconds > timestamp + 3600){
   		printf("NON. TicketTGS expired.\n");
   		exit(1);
   	}
   	
   	char ticketV_before[1024] = {};
   	strcat(ticketV_before, IDc);
   	strcat(ticketV_before, "-");
   	strcat(ticketV_before, ADc);
   	strcat(ticketV_before, "-");
   	strcat(ticketV_before, IDv);
   	strcat(ticketV_before, "-");
   	strcat(ticketV_before, TS);
   	strcat(ticketV_before, "-");
   	strcat(ticketV_before, duree);
   	int len = strlen(ticketV_before);
   	ticketV_before[len] = '\0';
  
	char * messageTGStoClient;
	messageTGStoClient = ticketV_before;
	messageTGStoClient = encrypt(keyV ,messageTGStoClient);
	messageTGStoClient[len] = '\0';
	//Client now receive ticket from TGS
	printf("Your ticketV:\n");
	puts(messageTGStoClient);  	
  
}



