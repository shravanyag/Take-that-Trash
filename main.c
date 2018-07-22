#include "header.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define FIXEDDISTANCE 0.75

int main()
{
	WSADATA wsa;
    SOCKET s;
    struct sockaddr_in server;
	
    printf("\nInitialising Winsock...");
    if (WSAStartup(MAKEWORD(2,2),&wsa) != 0)
    {
        printf("Failed. Error Code : %d",WSAGetLastError());
        //return 1;
    }
     
    printf("Initialised.\n");
     
    //Create a socket
    if((s = socket(AF_INET , SOCK_STREAM , 0 )) == INVALID_SOCKET)
    {
        printf("Could not create socket : %d" , WSAGetLastError());
    }
 
    printf("Socket created.\n");
     
     
    server.sin_addr.s_addr = inet_addr("74.125.235.20");
    server.sin_family = AF_INET;
    server.sin_port = htons( 80 );
 
    //Connect to remote server
    if (connect(s , (struct sockaddr *)&server , sizeof(server)) < 0)
    {
        puts("connect error");
        //return 1;
    }
     
    puts("Connected");
	float destnx, destny;
	scanf("%f %f",&destnx, &destny);
	struct node destn;
	struct node present;
	destn.x = destnx;
	destn.y = destny;
	destn.theta = 0.00;
	destn.d = 0.00;
	present.x = 0.00;
	present.y = 0.00;
	float A,D;
	present.theta = roundf((calculateTheta(present, destn)) * 100) / 100;
	present.d = roundf((calculateDistance(present, destn)) * 100) / 100;
	//socket(present.theta, 0.5m);
	
	float distance2;
	int S;
	char distance[7];
	strcpy(distance,"D ");
	char angle[7];
	strcpy(angle,"A ");
	char sA[4];
	char sD[4];
	char server_reply[4];
	int recv_size;
		
	do
	{
	
		A = present.theta;
		D = FIXEDDISTANCE;
		
			itoa(A,sA,10); //convert to string
			itoa(D,sD,10);
			 //Send some data
			strcat(distance,sD); //concatenate two string
			strcat(angle,sA);
		
			if( send(s , angle , strlen(angle) , 0) < 0)
			{
				puts("Send failed");
				continue();
			}
			puts("Angle Sent\n");
			
			//messageDistance = "D_";
			if( send(s , distance , strlen(distance) , 0) < 0)
			{
				puts("Send failed");
				continue();
			}
			puts("Distance Sent\n");
			 
			//Receive a reply from the server
			if((recv_size = recv(s , server_reply , 2000 , 0)) == SOCKET_ERROR)
			{
				puts("recv failed");
				S = 00;
				continue();
			}
			 
			//Add a NULL terminating character to make it a proper string before printing
			server_reply[recv_size] = '\0';
			puts(server_reply);

				//return this theta and the distance to the bot 
		//the bot must rotate by this angle and then move
		//in forward direction ; when obstruction reached or distance 
		//return the distance to this function
		
		distance2 = 10.00;
		
		char why[2];
		strcat(why, server_reply[2]);
		strcat(why, server_reply[3]);
		S = atoi(why);
		
		if (S == 00)
		{	
			present.x += distance2 * sin(present.theta);
			present.y += distance2 * cos(present.theta);
			continue();	
		}
		
		/*
		if(distance == present.d)
		{
			printf("Path completed\n");
			
			
			A = NOANGLE;
			D = NODISTANCE;
			break;
		}
		*/
		
			
		if (S != 00)	
		{
			overcomeObs(S, &present, destn);
			present.theta = calculateTheta(present, destn);
			present.d = calculateDistance(present, destn);
		}	

	}
	while(present.x != destn.x && present.y != destn.y );

	printf("Destination reached!!\n");
	// DONE YAY!!
}