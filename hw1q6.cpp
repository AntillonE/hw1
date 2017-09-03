#include <iostream>
#include <stdlib.h>
#include <cstring>
#include <fstream>
#include <string>

using namespace std;

string reverseString(string text, int start, int end)
{
  if(start >= end)
  {
  	return text;
  }
  else
  {
  	char temp = text[start];
  	text[start] = text[end];
  	text[end] = temp;
  	return reverseString(text, ++start, --end);
  }
}
// Make sure to check the seg fault

int main (int argc, char* argv[])
{
  if(argc < 2){
    cerr << "Please enter the name of the file:" << endl;
    return 1;
  }
  
  
  ifstream fileIn(argv[1]);
  int amountLetters = 0;
  string text;
  
  if (!fileIn.is_open() || fileIn.bad())
  {
  	cout << "Error! Unable to open file" << endl;
  	return 0;
  }

  //cerr << "Opened!" << endl;
  fileIn >> amountLetters;
  //cerr << amountLetters << endl;
  while(getline(fileIn, text)){}
  cerr << text << endl;

  fileIn.close();

  string revString;
  revString = reverseString(text, 0, amountLetters-1);
  cout << revString << endl;

  return 0;
}
