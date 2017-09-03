#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>

using namespace std;


int main(int argc, char* argv[])
{
  if(argc < 3){
    cerr << "Please provide an input and output file." << endl;
    return 1;
  }
  ifstream input(argv[1]);

  ofstream output(argv[2]);

  int experiments = 0;
  int *numsubjects = NULL;
  string **history = NULL;
  string line = "";
  string curr = "";
  int startFlag = 0;
  int openFlag = 0;

  //for each experiment, you will need to keep track of the number of subjects; and for each subject, of their history

  //input.open(argv[1]);
  if (!input.is_open() || input.bad())
  {
  	cout << "Error - File does not exist" << endl;
  	return 0;
  }


  //loop to read The Rani's logbook.
  while(getline(input, curr)) {
  	  line = curr;
	  stringstream ss;
	  ss << curr;
	  ss >> curr;
	  if (curr == "START") {
	    // Hint: This does not cover all errors yet.
		  int n = 0;
		  ss >> n;
		  if (ss.fail()) {
		    output << "Error - incorrect command: " << line << endl;
  		    output << "Parameter should be an integer" << endl;
		  }
		  else if (n < 0) {
		    output << "Error - incorrect command: " << line << endl;
		    output << "Number out of range" << endl;
		  }
		  else {
			// Take care of other errors here!!!
			
		  }

		  if(startFlag == 1)
		  {
		  	for(int i = 0; i < experiments; i++)
  			{
  		 	  delete[] history[i];
  			}
  			delete[] history;
  			delete[] numsubjects;
  			history = NULL;
  			numsubjects = NULL;

  			startFlag = 0;
		  }

		  experiments = 1;
		  history = new string*[experiments];
		  history[0] = new string[n];
		  for(int i = 0; i < n; i++)
		  {
		  	history[0][i] = "";
		  }

  		  numsubjects = new int[experiments];
  		  numsubjects[0] = n;
  		  startFlag = 1;
	  }
	  else if (curr == "ADD" && startFlag == 1) {
	  	if(startFlag == 0)
	  	{
	  	  output << "Error - incorrect command: " << line << endl;
	  	}
	  	experiments++;	  
	  	string **temp = new string*[experiments]();
	  	for(int index = 0; index < experiments-1; index++)
	  	{
	  	  temp[index] = new string[numsubjects[index]]();
	  	  for(int indexTwo = 0; indexTwo < numsubjects[index]; indexTwo++)
	  	  {
	  	    temp[index][indexTwo] = history[index][indexTwo];
	  	  }
	  	}
	  	for(int i = 0; i < experiments-1; i++)
	  	{
	  		delete[] history[i];
	  	}
	  	delete[] history;
	  	history = temp;

	  	int *numTemp = new int[experiments]();
	  	for(int index = 0; index < experiments-1; index++)
	  	{
	  		numTemp[index] = numsubjects[index];
	  	}
	  	delete[] numsubjects;
	  	numsubjects = numTemp;
	  	numTemp = NULL;
	  	//numsubjects[experiments] = 0;

	  }
	  else if (curr == "MOVE" && startFlag == 1) {
	  	int x, y = 0;
	  	int n, m = 0;

	  	ss >> x;
	  	ss >> y;
	  	ss >> n;
	  	ss >> m;

	  	int sizeX = numsubjects[x];
	  	int sizeY = numsubjects[y];

	  	int amountMoved = m - n + 1;
	  	numsubjects[x] -= amountMoved;
	  	numsubjects[y] += amountMoved;

	  	string *tempX = new string[numsubjects[x]]();
	  	string *tempY = new string[numsubjects[y]]();
	  	string *temp = new string[amountMoved]();


	  	int counter = 0;
	  	int counterTwo = 0;
		int counterThree = 0;
		stringstream numString;
	  	numString << y;
	  	string numStr = numString.str();
	  	for(int i = 0; i < sizeX; i++)
	  	{
	  	  if(i >= n && i <= m)
	  	  {
	  	  	temp[counterThree] = history[x][i];
	  	  	counterThree++;
	  	  }
	  	  else
	  	  {
	   	  	tempX[counterTwo] = history[x][i];
	   	  	counterTwo++;
	  	  }
	  	}

	  	for(int j = 0; j < numsubjects[y]; j++)
	  	{
	  		if(j < sizeY)
	  		{
	  		  tempY[j] = history[y][j];
	  		}
	  		else
	  		{
	  		  tempY[j] = temp[counter];
	  		  if(y != 0)
	  	  	  {
	  	  	  	if(tempY[j] == "")
	  	  	  	{
	  	  	  	  tempY[j] = tempY[j] + numStr;
	  	  	  	}
	  	  	  	else
	  	  	  	{
	  	  	      tempY[j] = tempY[j] + " " + numStr;
	  	  		}
	  	  	  }
	  		  counter++;
	  		}
	  	}

	  	delete[] history[x];
	  	delete[] history[y];
	  	delete[] temp;

	  	temp = NULL;
	  	history[x] = tempX;
	  	history[y] = tempY;
	  	tempY = NULL;
	  	tempX = NULL;
	  }
	  else if (curr == "QUERY") {
	  	int x, n = 0;
	  	ss >> x;
	  	ss >> n;

	  	if(openFlag == 0)
	  	{
	  	   //output.open();
	  	   openFlag = 1;
	  	}
	  	output << history[x][n] << endl;

	  }
	  else {
	    if(startFlag == 0)
	    {
	  	  output << "Error - no subjects yet: " << line << endl;
	    }
	    else
	    {
		  output << "Error - Command does not exist!" << endl;
		  output << "Valid commands are: START, ADD, MOVE, QUERY" << endl;
	    }
	  }
  }

  input.close();
  output.close();

  for(int i = 0; i < experiments; i++)
  {
  	delete[] history[i];
  }
  delete[] history;
  history = NULL;

  delete[] numsubjects;
  numsubjects = NULL;

  return 0;
}
