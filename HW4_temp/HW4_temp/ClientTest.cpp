#include<iostream>
#include<fstream>
#include<string>
#include"theaterline.h"
using namespace std;

void simulation(int startHour, int startMin, int maxSize, string title, ifstream& fs);

int main(){
	int hour, min, max;
	string movieName;
	ifstream input;
	input.open("C:\\lab4_testOne.txt");
	if (input.is_open()){
		input >> hour >> min >> max;
		getline(input, movieName);
		simulation(hour, min, max, movieName, input);
 	}
	else{
		cout << "invalid file's name" << endl;
	}
}

void simulation(int startHour, int startMin, int maxSize, string title, ifstream& fs){
	int curHour = startHour - 2;
	int curMin = startMin;
	int endEnter = startHour * 100 + startMin;
	int beginEnter = endEnter - 100;
	theatreLine movieLine(maxSize);
	while (!fs.eof()){
		string t;
		getline(fs, t);
		int hour = stoi(t);
		t = t.substr(t.find(" ",0)+1, t.size());
		int min = stoi(t);
		t = t.substr(t.find(" ",0) + 1, t.size());
		bool getRemoved = false;
		while ((curHour < hour) || (curMin < min)){
			curMin++;
			if (curMin == 60){
				curMin -= 60;
				curHour++;
			}
			int time = curHour * 100 + curMin;
			bool canEnter = ((time >= beginEnter) && (time <= endEnter));
			if (canEnter){
				string removedName = movieLine.deleteQueue(getRemoved);
				if (getRemoved){
					cout << curHour << ":" << curMin << "  "
						<< removedName << " entering the theater" << endl;
				}
			}
		}
		int pos = 1;
		string name;
		bool success;
		while (pos > 0){
			pos = t.find(" ", 0);
			name = t.substr(0, pos);
			t = t.substr(pos + 1, t.size());
			success = movieLine.addQueue(name);
			if (success){
				cout << curHour << ":" << curMin << "   "
					<< name << " enter the line." << endl;
			}
			else{
				cout << curHour << ":" << curMin << "   "
					<< "Line is full!  " << name <<
					" was turned away!" << endl;
			}
		}
	}
	while ((curHour <= startHour) && (curMin <= startMin)){
		curMin++;
		if (curMin == 60){
			curMin -= 60;
			curHour++;
		}
		bool Removed = false;
		int time = curHour * 100 + curMin;
		bool canEnter = ((time >= beginEnter) && (time <= endEnter));
		if (canEnter){
			string removedName = movieLine.deleteQueue(Removed);
			if (Removed){
				cout << curHour << ":" << curMin << "  "
					<< removedName << " entering the theater" << endl;
			}
		}
	}
} 

//this is a basic outline for your code. Now the file is read properly, you can adjust how to enter the theater 
//write another while loop after reading whole text file run from cur time to end time