#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "class.h"
#include "extern.h"
#include <stdio.h>
#include <iomanip>

using namespace std;

//build the symbol table
void build_symbol_table(ofstream& symbol_file, Node*& root){

  //init
	int blockid = 0;
  int labelid = 0;

	vector <vector <string>> symbol_table;
	vector <Node*> check_tree;

  root->reg = 0;
  root->label = 0;
  root->scope = 0;

  //queue structure
  check_tree.push_back(root);
  //dfs
	while(check_tree.size() !=0) {
    vector<string> buf;
    
    //pop
    Node* topnode = check_tree[0];
    check_tree.erase(check_tree.begin());

    //block management : to seperate scope
		if(topnode-> data == "block0") {
			symbol_table_scopes.push_back(symbol_table);
			symbol_table.clear();
			blockid++;

      topnode->scope = blockid;
		}

    //declare : put declared to symbol table
		if(topnode->data == "decl0" && topnode->childn == 3) {
			buf.push_back(topnode->child[1]->child[0]->data);	//name
			buf.push_back(topnode->child[0]->child[0]->data);	//type
      //size
			if(topnode -> child[0]->child[0]->data == "int"){
				buf.push_back("4");
			}
			else if(topnode->child[0]->child[0]->data == "char"){
				buf.push_back("1");
			}

      int addr = 0;

      //find used registor addr in the other scope (find at parent node)
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
      //find at current symbol table
      else
        addr = stoi(symbol_table[symbol_table.size() - 1][3]) + stoi(symbol_table[symbol_table.size() - 1][2]);

      //addr
      buf.push_back(to_string(addr));
      //target code's line number
      buf.push_back(to_string(topnode->line_num));
		}
    //add function to symbol table
		if(topnode->data == "prog0"){
			buf.push_back(topnode->child[0]->child[0]->data); //name
			buf.push_back("func"); //type
      buf.push_back("0"); //size
      buf.push_back("1000"); //init addr
      buf.push_back(to_string(topnode->line_num)); //target code's line number
		}

    //enqueue
    for(int i = 0; i < topnode->childn; i++) {
      Node* tmpnode = topnode->child[i];
      tmpnode->scope = topnode->scope;
      tmpnode->registor = topnode->reg;
      //Sethi-Ullman
      if(topnode->data == "cond0" && i == 2)
        tmpnode->reg++;
      if(topnode->data == "expr0" && i == 1)
        tmpnode->reg++;
      if(topnode->data == "T0" && tmpnode->childn != 0 && i == 1)
        tmpnode->reg++;

      //put label in IF instruction
      tmpnode->label = topnode->label;
      if(topnode->data == "stat0" && i == 2 && tmpnode->data == "THEN")
        tmpnode->label = labelid;
      if(topnode->data == "stat0" && i == 4 && tmpnode->data == "ELSE")
        tmpnode->label = labelid;
      
      if(topnode->data == "stat0" && i == 3 && tmpnode->data == "block0")
        tmpnode->label = labelid + 1;
      if(topnode->data == "stat0" && i == 5 && tmpnode->data == "block0") {
        tmpnode->label = labelid + 1;
        labelid += 2;
      }

      //enqueue
      check_tree.insert(check_tree.begin()+i, tmpnode);
    }
    //buf put in current symbol table
		if(buf.size() > 0){
			symbol_table.push_back(buf);
			buf.clear();
		}
  }

  //put symbol table when finish function
	symbol_table_scopes.push_back(symbol_table);
	symbol_table.clear();
	blockid++;


  // print symbol_table in symbol_file

  symbol_file << "======================================================================================\n";
	symbol_file << setw(6) <<"scope" << setw(8) << "line" << setw(18) << "Symbol name";
	symbol_file << setw(18) <<"type" << setw(18) << "size" << setw(18) << "address" << "\n";
  symbol_file << "======================================================================================\n";

	for(unsigned int b=0;b<symbol_table_scopes.size();b++) {
		symbol_file << setw(6) << b;
		symbol_table.clear();
		symbol_table = symbol_table_scopes[b];
		for(unsigned int i=0;i<symbol_table.size();i++){
      if(i!=0)
        symbol_file << setw(6) << " ";
			for(unsigned int j=0;j<symbol_table[i].size() - 1;j++){
        if(j == 0) 
				  symbol_file << setw(8) << symbol_table[i][4];
        if(j == 1 && symbol_table[i][j] == "func") {
				  symbol_file << setw(18) << symbol_table[i][j];
          break;
        }
				symbol_file << setw(18) << symbol_table[i][j];
			}
			symbol_file << endl;	
		}
		symbol_file << endl;
	}
  symbol_file << "======================================================================================\n";


/*
  // print tree
    cout << "\n\n";
    check_tree.clear();
    check_tree.push_back(root);
    while(check_tree.size() !=0)
    {
        Node* topnode = check_tree[0];
        check_tree.erase(check_tree.begin());
        cout << "data: " << topnode->data << "  child num: " << topnode->childn << endl;
        cout << topnode->reg << " " << topnode->label << " " << topnode->scope << "\n";
        
        cout << "\t child: ";
        for(int i = 0; i < topnode->childn; i++)
        {
            Node* tmpnode = topnode->child[i];
            cout << tmpnode->data << " ";
            check_tree.insert(check_tree.begin()+i, tmpnode);
        }
        cout << endl;
        
    }
*/
}
