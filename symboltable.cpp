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

	vector <Node*> check_tree;
    check_tree.push_back(root);

	while(check_tree.size() !=0)
    {
        Node* topnode = check_tree[0];
        check_tree.erase(check_tree.begin());
		if(topnode-> data == "block0"){	//block management : to seperate scope
			blockid++;
			symbol_file << endl;
			symbol_file << "scope " << blockid << endl;
			symbol_file << endl;
		}
		if(topnode->data == "decl0" && topnode->childn == 3){ //declare : put declared to symbol table
			symbol_file << topnode->child[1]->child[0]->data << " ";	//name of the variable
			symbol_file << topnode->child[0]->child[0]->data << " ";	//type
			if(topnode -> child[0]->child[0]->data == "int"){
				symbol_file << "4 ";
			}
			else{
				symbol_file << "1 ";
			}
			symbol_file << endl;
		}
		if(topnode->data == "prog0"){	//add function to symbol table
			symbol_file << topnode->child[0]->child[0]->data << " ";
			symbol_file << "func";
			symbol_file << endl;
		}
        cout << "data : " << topnode->data << "  child num: " << topnode->childn << endl;
        cout << "\t child : ";
        for(int i = 0; i < topnode->childn; i++)
        {
            Node* tmpnode = topnode->child[i];
            cout << tmpnode->data << " ";
            check_tree.insert(check_tree.begin()+i, tmpnode);
        }
        cout << endl;

    }
	symbol_file.close();
}
