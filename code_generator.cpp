#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "class.h"
#include "extern.h"
#include <stdio.h>

using namespace std;

void search_tree(ofstream& code_file, Node* topnode);

void code_generator(string input_file_name, Node* topnode) {
  ofstream code_file;
  code_file.open(input_file_name + ".code");
  
  search_tree(code_file, topnode);

  code_file.close();
}

void search_tree(ofstream& code_file, Node* topnode) {
  for(int i = 0; i < topnode->childn; i++) {
    Node* tmpnode = topnode->child[i];
    search_tree(code_file, tmpnode);
  }


  //modify here------------------------------------------------------
  code_file << "data: " << topnode->data << "  child num: " << topnode->childn << endl;
  code_file << "\t child: ";
  for(int i = 0; i < topnode->childn; i++) {
    Node* tmpnode = topnode->child[i];
    code_file << tmpnode->data << " ";
  }
  code_file << endl;
}
