#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "class.h"
#include "extern.h"
#include <stdio.h>

using namespace std;

bool flag;
int error_line_number;
void search_tree(ofstream& file, Node* topnode);
string find_addr(Node* tmpnode, string target, int c_scope);

bool code_generator(ofstream& code_file, Node* topnode) {
  //init flag
  flag = true;
  
  //print shape
  code_file << "\n\n****************************\n";
  code_file <<"       Psuedo Code "<< endl;
  code_file << "****************************\n\n\n";

  //print with recursion function
  search_tree(code_file, topnode);

  //ERROR
  if(flag == false) {
    code_file << "\nError: check error message\n";
    cout << "Semantic Error (Line " << error_line_number << "): Undeclared variable" << endl;
    return true;
  }

  //print shape
  code_file << "\n\n****************************\n";
  code_file <<"    Using Register : " << use_register << endl;
  code_file << "****************************\n";

  return false;
}

void search_tree(ofstream& file, Node* topnode) {
  for(int i = 0; i < topnode->childn; i++) {
    Node* tmpnode = topnode->child[i];
    search_tree(file, tmpnode);
  }

  //modify here------------------------------------------------------
  
  //error
  if(flag == false)
    return;

  //print EXIT
  if(topnode->data == "stat0" && topnode->childn == 3) {
    if(topnode->child[0]->data == "EXIT") {
      file << "        LD RR, R" << topnode->register << "\n";
      file << "        JUMP END\n";
    }
  }

  //print BEGIN
  if(topnode->data == "(")
    file << "BEGIN " << topnode->parent->child[0]->child[0]->data << "\n";

  //print "="
  if(topnode->data == "stat0" && topnode->childn == 4) {
    file << "        ST R" << topnode->register << ", ";
    if(find_addr(topnode, topnode->child[0]->child[0]->data, topnode->scope) == "-1") {
      flag = false;
      error_line_number = topnode->line_num;
      return;
    }
    file << "(" << find_addr(topnode, topnode->child[0]->child[0]->data, topnode->scope) << ")\n";
  }
  //print LD
  if(topnode->data == "fact0") {
    file << "        LD R" << topnode->register << ", ";
    Node* tmpnode = topnode->child[0];
    if(tmpnode->data == "num")
      file << tmpnode->child[0]->data << "\n";
    else {
      if(find_addr(topnode, topnode->child[0]->child[0]->data, topnode->scope) == "-1") {
        error_line_number = topnode->line_num;
        flag = false;
        return;
      }
      file << "(" << find_addr(tmpnode, tmpnode->child[0]->data, tmpnode->scope) << ")\n";
    }
  }
  //print LT
  if(topnode->data == "cond0") {
    file << "        LT R" << topnode->register << ", R";
    file << topnode->child[0]->register << ", R" << topnode->child[2]->register << "\n";
  }
  //print THEN
  if(topnode->data == "THEN") {
    file << "        JUMPF L" << topnode->label << "\n";
  }
  //print END or JUMP or LABEL at block0
  if(topnode->data == "block0") {
    Node* parentnode = topnode->parent;

    if(parentnode->data == "prog0")
      file << "END " << parentnode->child[0]->child[0]->data << "\n";
    
    if(parentnode->childn == 6) {
      if(parentnode->child[3] == topnode) // #3 block in IF
        file << "        JUMP L" << topnode->label << "\n";
      else if(parentnode->child[5] == topnode) // #5 block in IF
        file << "L" << topnode->label << "\n";
    }
  }
  //print ELSE (LABEL)
  if(topnode->data == "ELSE") {
    file << "L" << topnode->label << "\n";
  }
  //print "+"
  if(topnode->data == "expr0") {
    if(topnode->childn >= 2)
      if(topnode->child[1]->childn >= 1) {
        if(topnode->child[1]->child[0]->data == "+") {
          file << "        ADD R" << topnode->register << ", R" << topnode->child[0]->register << ", R";
          file << topnode->child[1]->register <<"\n";
        }
      }
  }
  //print "*"
  if(topnode->data == "T0" && topnode->child[1]->childn != 0) {
    file << "        MUL R" << topnode->register << ", R" << topnode->child[0]->register << ", R";
    file << topnode->child[1]->register <<"\n";
  }
  //-----------------------------------------------------------------
}

//find word's addr in symbol table
string find_addr(Node* tmpnode, string target, int c_scope) {
  //If we can't word's addr in symbol table, return -1
  string addr = "-1";
  vector <vector <string>> symbol_table;
  int talchul = 0;

  //find addr in parent scope
  while(1) {
    symbol_table = symbol_table_scopes[c_scope];

    //at current table
    for(unsigned int i = 0; i < symbol_table.size(); i++)
    if(symbol_table[i][0] == target) {
      addr = symbol_table[i][3];
      talchul = 1;
    }
    if(talchul == 1)
      break;

    //node change to parent node when current scope do not same parent scope
    while(tmpnode != NULL) {
      if(tmpnode->scope != c_scope)
        break;
      tmpnode = tmpnode->parent;
    }
    if(tmpnode == NULL)
      break;
    c_scope = tmpnode->scope;
  }
  return addr;
}
