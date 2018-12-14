#include <iostream>
#include "AVLTree.h"
using namespace std;

int main(){
  AVLTree temp;
  temp.insert("12", "a");
  temp.insert("10", "b");
  temp.insert("09", "c");
  temp.insert("08", "d");
  temp.insert("06", "d");
  temp.insert("04", "d");
  temp.insert("02", "d");
  temp.print();
  cout << "insert 07 " << endl;
  temp.insert("07", "d");
  
  temp.print();
    
  cout << "Delete 12, 10, 09 06" << endl;
  temp.deleteNode("12");

  temp.deleteNode("10");
  temp.deleteNode("09");
  temp.deleteNode("06");
  temp.print();
}
