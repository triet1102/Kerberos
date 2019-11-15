#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "createMask.h"
#include "encrypt.h"
#include "decrypt.h"
#include "intToString.h"

//identity IDV1 of server and key V1
char * IDV1 = "V1";
char * V1 = "8rSiqp!.Q";

int main (int argc, char *argv[]){
	printf("<IDc> <ADc> <TicketV>\n");
	char input[1024], split[] = "-";
	char IDc[1024], IDcCheck[1024];
	char ADc[1024], ADcCheck[1024];
	char IDvCheck[1024];
	char ticketV[1024];
	
	// get IDc, ADc, IDv, ticketTGS
	scanf("%s",IDc);
	IDc[strlen(IDc)] = '\0';
	scanf("%s",ADc);
	ADc[strlen(ADc)] = '\0';
	scanf("%s",ticketV);
	ticketV[strlen(ticketV)] = '\0';
	
   	//check if IDc exists
   	if (strcmp("Client1", IDc) != 0 && strcmp("Client2", IDc) != 0){
   		printf("NON. Unknow Client.\n");
   		exit(1);
   	}

   	//generate ticketTGS_before = [IDC||ADC||IDtgs||TS1||Duree1] then copy to input
   	char *ticketV_before;
   	ticketV_before = ticketV;
   	ticketV_before = decrypt(V1, ticketV_before);
   	strcpy(input,ticketV_before);
   	input[strlen(input)] = '\0'; 	
	strcat(input, "-N-N");
	
   	//get IDc in the ticketV_before 
   	char * ptr = strtok(input, split);
   	strcpy(IDcCheck, ptr);
   	IDcCheck[strlen(IDcCheck)] = '\0';

   	//get ADc in the ticketV_before 
   	ptr = strtok(NULL, split);
   	strcpy(ADcCheck, ptr);
   	ADcCheck[strlen(ADcCheck)] = '\0';

   	//get IDv in the ticketV_before
   	ptr = strtok(NULL, split);
   	strcpy(IDvCheck, ptr);
   	IDvCheck[strlen(IDvCheck)] = '\0';

	if (strcmp(IDvCheck, IDV1) != 0){
   		printf("NON. Wrong destination, I am V1.\n");
   		exit(1);
   	}else {
   		if (strcmp(IDcCheck, IDc) != 0){
   			printf("NON. IDc not match with IDc in your TicketV.\n");
   			exit(1);
   		}
   		if (strcmp(ADcCheck, ADc) != 0){
   			printf("NON. ADc not match with ADc in your TicketV.\n");
   			exit(1);
   		}
   	}   	
   	
   	//get timestamp then verify if the ticket is expired or not
   	time_t seconds;	
   	seconds = time(NULL);	
   	long timestamp = 0;
   	ptr = strtok(NULL, split);
   	timestamp = atol(ptr);
   	if (seconds > timestamp + 3600){
   		printf("NON. TicketV expired.\n");
   		exit(1);
   	}
	
	//now everything is good
	printf("OK!\n");

}



