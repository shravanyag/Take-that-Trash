#ifndef HEADER_H
#define HEADER_H

struct node
{
	float x;
	float y;
	float theta;
	float d;
};

float calculateTheta(struct node present,struct node destn);
float calculateDistance(struct node present,struct node destn);
void overcomeObs(int S,struct node* present,struct node destn);
void realignBot(int phi,struct node* present,struct node destn);

#endif