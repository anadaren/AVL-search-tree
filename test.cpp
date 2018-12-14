#include <iostream>
#include "AVLTree.h"
using namespace std;

int main(){
  AVLTree temp;
  temp.insert("05", "a");
  temp.insert("08", "b");
  temp.insert("09", "c");
  temp.insert("03", "d");
  temp.insert("06", "d");
  temp.insert("07", "d");
  temp.insert("02", "d");

  temp.print();

 }
