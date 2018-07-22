#include "header.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <winsock2.h>
#define MINANGLE 0.15
#define NODISTANCE 0.00
#define NOANGLE 0.00
#define MINDISTANCE 0.30

float calculateTheta(struct node present, struct node destn)
{
	return atan((destn.y - present.y)/(destn.x - present.x));//find tan inverse for the given value
}

float calculateDistance(struct node present, struct node destn)
{
	return sqrt(pow((destn.x - present.x),2) + pow((destn.y - present.y),2));
}

void overcomeObs(int S,struct node* present,struct node destn)
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
 
    //return 0;
	float phi = 0.00, phicumulative = 0.00;
	float A, D;
	char distance[7];
	strcpy(distance,"D ");
	char angle[7];
	strcpy(angle,"A ");
	char sA[4];
	char sD[4];
	char server_reply[4];
	int recv_size;
	
	
	while (S != 00)
	{	
		while(S == 11 || S == 10)
		{
			phi += MINANGLE;
			present -> theta += MINANGLE;
			present -> d = NODISTANCE;
			A = MINANGLE;
			D = present -> d;
			
			itoa(A,sA,10); //convert to string
			itoa(D,sD,10);
			 //Send some data
			strcat(distance,sD); //concatenate two string
			strcat(angle,sA);
		
			if( send(s , angle , strlen(angle) , 0) < 0)
			{
				puts("Send failed");
				//return 1;
			}
			puts("Angle Sent\n");
			
			//messageDistance = "D_";
			if( send(s , distance , strlen(distance) , 0) < 0)
			{
				puts("Send failed");
				//return 1;
			}
			puts("Distance Sent\n");
			 
			//Receive a reply from the server
			if((recv_size = recv(s , server_reply , 2000 , 0)) == SOCKET_ERROR)
			{
				puts("recv failed");
			}
			 
			//Add a NULL terminating character to make it a proper string before printing
			server_reply[recv_size] = '\0';
			puts(server_reply);

			//send A & D to bot and receive D and S
			
			char why[2];
			strcat(why, server_reply[2]);
			strcat(why, server_reply[3]);
			S = atoi(why);
		}
		while(S == 01)
		{
			D = MINDISTANCE;
			present -> d += D;
			float distance2 = 4.00;
			present -> x += distance2 * sin(present.theta);
			if (present.theta > 90)
				present -> y -= distance2 * cos(present.theta);
			else 
				present -> y += distance2 * cos(present.theta);
			
			A = NOANGLE;
			
			itoa(A,sA,10); //convert to string
			itoa(D,sD,10);
			 //Send some data
			 strcat(distance,sD); //concatenate two string
			 strcat(angle,sA);
		
			if( send(s , angle , strlen(angle) , 0) < 0)
			{
				puts("Send failed");
				//continue();
			}
			puts("Angle Sent\n");
			
			messageDistance = "D_";
			if( send(s , distance , strlen(distance) , 0) < 0)
			{
				puts("Send failed");
				//continue();
			}
			puts("Distance Sent\n");
			 
			//Receive a reply from the server
			if((recv_size = recv(s , server_reply , 2000 , 0)) == SOCKET_ERROR)
			{
				puts("recv failed");
				S = 00;
				//continue();
			}
			 
			//Add a NULL terminating character to make it a proper string before printing
			server_reply[recv_size] = '\0';
			puts(server_reply);
																																																																																																																																																																											   cc
			//send A & D to bot and receive D and S	
			char why[2];
			strcat(why, server_reply[2]);
			strcat(why, server_reply[3]);
			S = atoi(why);
		}
	
	}

	realignBot(phi,&present,destn);	
}
void realignBot(int phi,struct node* present,struct node destn)
{
	char distance[7];
	strcpy(distance,"D ");
	char angle[7];
	strcpy(angle,"A ");
	char sA[4];
	char sD[4];
	//char server_reply[4];
	//int recv_size;
	float A =  360-phi;
	D = NODISTANCE;
	itoa(A,sA,10); //convert to string
	itoa(D,sD,10);
	 //Send some data
	strcat(distance,sD); //concatenate two string
	strcat(angle,sA);

	if( send(s , angle , strlen(angle) , 0) < 0)
	{
		puts("Send failed");
		//continue();
	}
	puts("Angle Sent\n");
	
	//distance = "D ";
	if( send(s , distance , strlen(distance) , 0) < 0)
	{
		puts("Send failed");
		//continue();
	}
	puts("Distance Sent\n");
	 
	/*Receive a reply from the server
	if((recv_size = recv(s , server_reply , 2000 , 0)) == SOCKET_ERROR)
	{
		puts("recv failed");
	}
	 
	//Add a NULL terminating character to make it a proper string before printing
	server_reply[recv_size] = '\0';
	puts(server_reply);
																																																																																																																																																																									   cc
		//send A & D to bot and receive D and S			
	}
	//send A to bot*/
	
	present -> theta = 0.00; // since we realign to y axis
}
