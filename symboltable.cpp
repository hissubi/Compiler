#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "class.h"
#include "extern.h"
#include <stdio.h>

using namespace std;

void build_symbol_table(string input_file_name){
  ofstream symbol_file;
	symbol_file.open(input_file_name + ".symbol");

	int blockid = 0;

	vector <vector <string>> symbol_table;
	vector <vector <vector <string>>> symbol_table_scopes;
	vector <Node*> check_tree;

  root->resistor_num = 0;
  root->label_num = 0;
  root->scope_num = 0;
  check_tree.push_back(root);

	while(check_tree.size() !=0) {
    vector<string> buf;
    
    Node* topnode = check_tree[0];
    check_tree.erase(check_tree.begin());

		if(topnode-> data == "{") {	//block management : to seperate scope
			symbol_table_scopes.push_back(symbol_table);
			symbol_table.clear();
			blockid++;
		}

		if(topnode->data == "decl0" && topnode->childn == 3){ //declare : put declared to symbol table
			buf.push_back(topnode->child[1]->child[0]->data);	//name
			buf.push_back(topnode->child[0]->child[0]->data);	//type
			if(topnode -> child[0]->child[0]->data == "int"){
				buf.push_back("4");
			}
			else if(topnode->child[0]->child[0]->data == "char"){
				buf.push_back("1");
			}
		}
		if(topnode->data == "prog0"){	//add function to symbol table
			buf.push_back(topnode->child[0]->child[0]->data);
			buf.push_back("func");
		}

    //cout << "data : " << topnode->data << "  child num: " << topnode->childn << endl;
    //cout << "\t child : ";
    for(int i = 0; i < topnode->childn; i++) {
      Node* tmpnode = topnode->child[i];
      // set parent node
      tmpnode->parent = topnode;

      //cout << tmpnode->data << " ";
      check_tree.insert(check_tree.begin()+i, tmpnode);
    }
    //cout << endl;
		if(buf.size() > 0){
			symbol_table.push_back(buf);
			buf.clear();
		}
  }

	symbol_table_scopes.push_back(symbol_table);
	symbol_table.clear();
	blockid++;


  // print symbol_table
	for(unsigned int b=0;b<symbol_table_scopes.size();b++) {
		symbol_file << "scope " << b << endl;
		symbol_table.clear();
		symbol_table = symbol_table_scopes[b];
		for(unsigned int i=0;i<symbol_table.size();i++){
			for(unsigned int j=0;j<symbol_table[i].size();j++){
				symbol_file << symbol_table[i][j] << " ";
			}
			symbol_file << endl;	
		}
		symbol_file << endl;
	}
	symbol_file.close();
}
