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

  root->resistor = 0;
  root->label = 0;
  root->scope = 0;
  check_tree.push_back(root);

	while(check_tree.size() !=0) {
    vector<string> buf;
    
    Node* topnode = check_tree[0];
    check_tree.erase(check_tree.begin());

		if(topnode-> data == "block0") {	//block management : to seperate scope
			symbol_table_scopes.push_back(symbol_table);
			symbol_table.clear();
			blockid++;
      
      topnode->scope = blockid;
		}

    cout << "1\n";
		if(topnode->data == "decl0" && topnode->childn == 3){ //declare : put declared to symbol table
			buf.push_back(topnode->child[1]->child[0]->data);	//name
			buf.push_back(topnode->child[0]->child[0]->data);	//type
			if(topnode -> child[0]->child[0]->data == "int"){
				buf.push_back("4");
			}
			else if(topnode->child[0]->child[0]->data == "char"){
				buf.push_back("1");
			}

      int addr = 0;
      if(symbol_table.size() == 0) {
        int c_scope = topnode->scope;
        Node* c_node = topnode;

        while(c_node->parent != NULL) {
          if(c_node->scope != c_scope && symbol_table_scopes[c_node->scope].size() != 0)
            break;
          c_node = c_node->parent;
        }
        c_scope = c_node->scope;

	      vector <vector <string>> c_symbol_table = symbol_table_scopes[c_scope];
        addr = stoi(c_symbol_table[c_symbol_table.size() - 1][3]) + stoi(c_symbol_table[c_symbol_table.size() - 1][2]);
      }
      else
        addr = stoi(symbol_table[symbol_table.size() - 1][3]) + stoi(symbol_table[symbol_table.size() - 1][2]);

      buf.push_back(to_string(addr));
		}
		if(topnode->data == "prog0"){	//add function to symbol table
			buf.push_back(topnode->child[0]->child[0]->data); //name
			buf.push_back("func"); //type
      buf.push_back("0"); //size
      buf.push_back("1000");
		}

    //cout << "data : " << topnode->data << "  child num: " << topnode->childn << endl;
    //cout << "\t child : ";
    for(int i = 0; i < topnode->childn; i++) {
      Node* tmpnode = topnode->child[i];
      tmpnode->scope = topnode->scope;
      tmpnode->resistor = topnode->resistor;
      tmpnode->label = topnode->label;

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
