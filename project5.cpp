#include <iostream>
#include <fstream>
#include "AVLTree.h"
#include <string>
#include <time.h>
#include <ctime>

using namespace std;

int main(int argc, char* argv[]) {
  clock_t start, end;
  double duration;

  start = clock();

  
  //defines variables for the leading char, ssn, and name                       
  char leadingChar;
  string ssn, first, last, name;

  //defines variables for number of insertions, deletions, and retrievals
  int ins = 0;
  int del = 0;
  int ret = 0;
  
  //defines tree
	AVLTree temp;
	
  //reads file values into array                                                
  fstream input(argv[1]);
  while(!input.eof()){
    //reads in data from file                                                   
    input >> leadingChar >> ssn >> first >> last;
    name = first + last;

	
	
    //checks to see what the leading char is telling the program to do, and calls the corresponding function
    switch(leadingChar) {
    case 'i':
		//adds the new value to array                           
		if(temp.insert(ssn, name) == true)
			ins++;
		break;
    case 'd':
		//checks for a match in the file                        
		if(temp.deleteNode(ssn) == true)
			del++;
		break;
	case 'r':
		if(temp.find(ssn) == true)
			ret++;
		break;
	default:
		break;
	}

	if(!input) break;
  }

  //closes file                                                                 
  input.close();

	//prints out results                                                          
	cout << "The number of valid Insertion: " << ins << endl;
	cout << "The number of valid Deletion: " << del << endl;
	cout << "The number of valid Retrieval: " << ret << endl;
	cout << "Height of AVL Tree: " << endl;

	end = clock();
	duration = ( end - start ) / (double) CLOCKS_PER_SEC;

	cout <<"Elapsed time: "<< duration <<'\n';
	cout << "Tree size: " << ins-del <<'\n';

}
