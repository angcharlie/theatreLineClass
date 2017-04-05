//Charlie Ang
//May 5, 2016
//CSC 2431 Spring 2016
//Assignment 4
//Header file for theatreList Class
//Simulation to model a new policy for for theatre lines of poeple waiting to see various movies.

#ifndef H_THEATRELIST
#define H_THEATRELIST

#include <iostream>
#include <cassert>
#include <stack>
#include <fstream>
#include <string>
#include <iomanip>
#include <queue>

using namespace std;

class theatreLine
{
public:

	//Default constructor to initialize queue
	theatreLine();

	//Parameterized constructor for total number of patrons allowed 
	theatreLine(int queueSize);

	//Accessor for the maximum number of people allowed in the queue
	//Postcondition: Returns the maximum number of poeple allowed in the queue 
	int maxNum();

	//Accessor for the current number of people in the queue
	//Postcondition: Returns the current number of people in the queue 
	int curCount();

	//Method to add a single patron to the end of the queue if there is space available.
	//Precondition: Queue exists and is not full
	//Postcondition: Single patron name is added to the queue 
	bool addQueue(string patronName);

	//Method to remove a single patron from the front of the queue.
	//Precondition: The queue exists and is not empty
	//Postcondition: The first element is removed from the queue and the name of the the person is returned.
	string deleteQueue();




private:
	queue<string> myQueue;	//STL queue to model a single line of patrons waiting to enter theatre
	int maxQueueSize;		//maximum number of poeple allowed in the queue
	int count;				//keeps track of current number of patrons in queue
};
#endif;

//*************************************IMPLEMENTATION********************************************

//Default constructor 
theatreLine::theatreLine()
{
	count = 0;
	maxQueueSize = 100;
}

//Parameterized constructor
theatreLine::theatreLine(int queueSize)
{
	count = 0;
	if (queueSize <= 0)
	{
		cout << "Size of queue must be positive." << endl;
		cout << "Creating a queue of size 100." << endl;

		maxQueueSize = 100;
	}
	else
	{
		maxQueueSize = queueSize;	//set maxQueueSize to passed in value 
	}
}

//Accessor to return maximum number of people allowed in the queue
int theatreLine::maxNum()
{
	return maxQueueSize;
}

//Accessor to return the current number of people in the queue 
int theatreLine::curCount()
{
	return count;
}

//Adding a single patron to end of queue 
bool theatreLine::addQueue(string patronName)
{
	if (count != maxQueueSize)	//queue is full
	{
		count++;	//increment counter for number of patrons
		myQueue.push(patronName);		//adds a patron to back of queue
		return true;
	}
	else
	{
		//cout << "Cannot add to a full queue." << endl;
		return false;
	}
}

//Removes a single patron from the front of the queue and returns the person's name 
string theatreLine::deleteQueue()
{
	if (count != 0)	//if queue is not empty 
	{
		count--;					//decrement counter 
		string name;				//temp variable 
		name = myQueue.front();		//saves name of patron in temp string variable 
		myQueue.pop();				//remove first element 
		return name;				//returns the name of patron 
	}
	else
	{
		cout << "Cannot remove from an empty queue." << endl;
		return "";
	}
}