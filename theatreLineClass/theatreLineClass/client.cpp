//Charlie Ang
//May 5, 2016
//CSC 2431 Spring 2016
//Assignment 4
//Client for theatreList Class
//Simulation to model a new policy for for theatre lines of poeple waiting to see various movies.

#include <iostream>
#include <cassert>
#include <stack>
#include <fstream>
#include <string>
#include <iomanip>
#include <queue>

#include "theatreLine.h"

using namespace std;

//Function prototype
void simulateMovie(int startHour, int startMin, int lineSize, string title, ifstream &fs, theatreLine test);

int main()
{
	//Declare stream variable
	ifstream inFile;

	//Ask user for the name of the data file they wish to use
	string inData;
	cout << "Enter the input file: ";
	cin >> inData;
	cout << endl;

	inFile.open(inData);	//opens input file inData  

	if (inFile.fail())		//if file can't be opened 
	{
		cout << "Error Opening File" << endl;
		exit(1);
	}

	//*********************************after opening file*********************************
	
	//string fileText;
	//getline(inFile, fileText);	//grabs next line and store in fileText 
	
	string fileText;
	getline(inFile, fileText);	//string with data in memory is stored in dataInMemory 

	int index = 0;	//index in memory array
	int space = 0;	//finding index of first space 

	int hour;		//variable to hold startHour
	int min;		//variable to hold startMin
	int lineSize;	//variable to hold lineSize 
	string title;	//varibale to hold movie title
	//fs = inFile

	if (space != -1 && fileText.size() != 0)	//if there is another space and the string isn't empty  
	{
		hour = stoi(fileText);	//Type casting
		space = fileText.find(" ");	//find index of space...returns -1 if no space is found 
		fileText = fileText.substr(space + 1);	//chop off the already retrived data value 
		index++;	//increment index for placing into memory array 
	}

	if (space != -1 && fileText.size() != 0)	//if there is another space and the string isn't empty  
	{
		min = stoi(fileText);	//Type casting
		space = fileText.find(" ");	//find index of space...returns -1 if no space is found 
		fileText = fileText.substr(space + 1);	//chop off the already retrived data value 
		index++;	//increment index for placing into memory array 
	}

	if (space != -1 && fileText.size() != 0)	//if there is another space and the string isn't empty  
	{
		lineSize = stod(fileText);	//Type casting
		space = fileText.find(" ");	//find index of space...returns -1 if no space is found 
		fileText = fileText.substr(space + 1);	//chop off the already retrived data value 
		index++;	//increment index for placing into memory array 
	}

	if (space != -1 && fileText.size() != 0)	//if there is another space and the string isn't empty  
	{
		title = fileText;	//Type casting
		space = fileText.find(" ");	//find index of space...returns -1 if no space is found 
		fileText = fileText.substr(space + 1);	//chop off the already retrived data value 
		index++;	//increment index for placing into memory array 
	}
	theatreLine test(lineSize);				//initialize simulator 
	simulateMovie(hour, min, lineSize, title, inFile, test);	//call client function
	
	inFile.close();	//close input file 	
	return 0;
}

void simulateMovie(int startHour, int startMin, int lineSize, string title, ifstream &fs, theatreLine test)
{
	if (startHour < 10 && startMin >= 10)	//if hours less than 10, append an extra 0 at beg
	{
		cout << "Starting simulation for " + title + " " + "which starts at " + "0" + to_string(startHour) + ":" + to_string(startMin) + "." << endl;
	}
	else if (startHour >= 10 && startMin < 10)	//if min less than 10, append an extra 0 and end 
	{
		cout << "Starting simulation for " + title + " " + "which starts at " + to_string(startHour) + ":" + "0" + to_string(startMin) + "." << endl;
	}
	else if (startHour < 10 && startMin < 10)	//if hours and min less than 10, append extra 0s
	{
		cout << "Starting simulation for " + title + " " + "which starts at " + "0" + to_string(startHour) + ":" + "0" + to_string(startMin) + "." << endl;
	}
	else
	{
		cout << "Starting simulation for " + title + " " + "which starts at " + to_string(startHour) + ":" + to_string(startMin) + "." << endl;
	}


	cout << "The line can hold a maximum of " + to_string(lineSize) + " patrons." << endl;

	if (startHour == 0)
	{
		startHour = 24;
	}
	if (startHour == 1)
	{
		startHour = 25;
	}

	if (startHour < 10 && startMin >= 10)	//if hours less than 10, append an extra 0 at beg
	{
		cout << "The time is currently 0" + to_string(startHour - 2) + ":" + to_string(startMin) + "." << endl;
	}
	else if (startHour >= 10 && startMin < 10)	//if min less than 10, append an extra 0 and end 
	{
		cout << "The time is currently " + to_string(startHour - 2) + ":" + "0" + to_string(startMin) + "." << endl;
	}
	else if (startHour < 10 && startMin < 10)	//if hours and min less than 10, append extra 0s
	{
		cout << "The time is currently 0" + to_string(startHour - 2) + ":" + "0" + to_string(startMin) + "." << endl;
	}
	else
	{
		cout << "The time is currently " + to_string(startHour - 2) + ":" + to_string(startMin) + "." << endl;
	}

	int curHour = startHour - 2;	//keep track of current hour (2 hours before movie starts)
	int curMin = startMin;		//cur min

	int space = 0;	//finding index of first space 

	int hour;		//variable to hold startHour
	int min;		//variable to hold startMin
	int hourTrack = 0;	//keeping track of number of hours gone by
	bool newLine = true;
	string line;
	string patron;
	//int lineSize;	//variable to hold lineSize 
	//string title;	//varibale to hold movie title


	while (curHour < startHour)	//iterating thorugh each hour...if time is between 2 hours before movie and movie start time 
	{
		while (curMin < 60)	//iterating through each min line closes as soon as time hits 
		{
			if (curHour == startHour && curMin == startMin)	//if current time matches movie start time
			{
				cout << "Doors closing, ending simulation!" << endl;
				cout << "There are " << test.curCount() << " patrons left in line!" << endl;
				return;	//exit out of function
			}
			
			if (newLine == true)	//if we should grab a new line 
			{
				if (getline(fs, line))	//while there is another line in the file...so not end of file
				{
					if (space != -1)	//if there is another space and the string isn't empty  
					{
						hour = stod(line);	//Type casting
						space = line.find(" ");	//find index of space...returns -1 if no space is found 
						line = line.substr(space + 1);	//chop off the already retrieved data value 
					}

					if (space != -1 && line.size() != 0)	//if there is another space and the string isn't empty  
					{
						min = stod(line);	//Type casting
						space = line.find(" ");	//find index of space...returns -1 if no space is found 
						line = line.substr(space + 1);	//chop off the already retrieved data value 
					}
				}	//end of get line 
			}	//end of grabbing new line 
			
			//***************checks to see if time matches current time***************************************

			if (hour == curHour && min == curMin)	//add to queue if time matches 
			{
					//space = line.find(" ");	//find index of space...returns -1 if no space is found 
					while (space != -1 && line.size() >= 1)	//while there is another space and the string isn't empty  
					{
						space = line.find(" ");	//find index of space...returns -1 if no space is found 
						patron = line.substr(0, space);
						line = line.substr(space + 1);	//chop off the already retrieved data value 

						//if there is room in the line
						if (test.addQueue(patron))
						{
							if (curHour < 10 && curMin >= 10)	//if hours less than 10, append an extra 0 at beg
							{
								cout << "0" << hour << ":" << min << "   " << patron << " is entering the line" << endl;
							}
							else if (curHour >= 10 && curMin < 10)	//if min less than 10, append an extra 0 and end 
							{
								cout << hour << ":" << "0" << min << "   " << patron << " is entering the line" << endl;
							}
							else if (curHour < 10 && curMin < 10)	//if hours and min less than 10, append extra 0s
							{
								cout << "0" << hour << ":" << "0" << min << "   " << patron << " is entering the line" << endl;
							}
							else
							{
								cout << hour << ":" << min << "   " << patron << " is entering the line" << endl;
							}
							
						}
						else //cannot add into queue because queue is full 
						{
							if (test.addQueue(line) == false)	//cannot add into queue
							{
								if (curHour < 10 && curMin >= 10)	//if hours less than 10, append an extra 0 at beg
								{
									cout << "0" << hour << ":" << min << "   " << "Line has overflowed!" << "   " << "Patron " << patron << " was turned away!" << endl;
								}
								else if (curHour >= 10 && curMin < 10)	//if min less than 10, append an extra 0 and end 
								{
									cout << hour << ":" << "0" << min << "   " << "Line has overflowed!" << "   " << "Patron " << patron << " was turned away!" << endl;
								}
								else if (curHour < 10 && curMin < 10)	//if hours and min less than 10, append extra 0s
								{
									cout << "0" << hour << ":" << "0" << min << "   " << "Line has overflowed!" << "   " << "Patron " << patron << " was turned away!" << endl;
								}
								else
								{
									cout << hour << ":" << min << "   " << "Line has overflowed!" << "   " << "Patron " << patron << " was turned away!" << endl;
								}
							}
						}	
					}
					line = "";	//chop off the already retrived data value 
					newLine = true; //only grab new line if done with all patrons at current time 
					space = 0;
			}
			else //iterate time until time catches up
			{
				newLine = false;	//dont grab new line
			}

			if (hourTrack >= 60) //people can start entering theatre 
			{
				if (test.curCount() != 0)	//if queue isn't empty...then remove one patron
				{
					patron = test.deleteQueue();
					if (curHour < 10 && curMin >= 10)	//if hours less than 10, append an extra 0 at beg
					{
						cout << "0" << curHour << ":" << curMin << "   " << patron << " has entered the theatre!" << endl;
					}
					else if (curHour >= 10 && curMin < 10)	//if min less than 10, append an extra 0 and end 
					{
						cout << curHour << ":" << "0" << curMin << "   " << patron << " has entered the theatre!" << endl;
					}
					else if (curHour < 10 && curMin < 10)	//if hours and min less than 10, append extra 0s
					{
						cout << "0" << curHour << ":" << "0" << curMin << "   " << patron << " has entered the theatre!" << endl;
					}
					else
					{
						cout << curHour << ":" << curMin << "   " << patron << " has entered the theatre!" << endl;
					}
				}
			}

			curMin++;		//increment mins
			hourTrack++;	//one hour has gone by......if this is one..people can start entering theatre 
			if (curMin == 60)
			{
				curHour++;	//increment hour
				curMin = 0;
			}
		} //end of while loop for iterating through mins 
	}	//end of iterating for hours 
}
