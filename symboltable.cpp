#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "class.h"
#include "extern.h"

using namespace std;

void build_symbol_table(string input_file_name){
    ofstream symbol_file;
	symbol_file.open(input_file_name + ".symbol");
	vector <Node*> check_tree;
    check_tree.push_back(root);

	while(check_tree.size() !=0)
    {
        Node* topnode = check_tree[0];
        check_tree.erase(check_tree.begin());
        symbol_file << "data: " << topnode->data << "  child num: " << topnode->childn << endl;

        symbol_file << "\t child: ";
        for(int i = 0; i < topnode->childn; i++)
        {
            Node* tmpnode = topnode->child[i];
            symbol_file << tmpnode->data << " ";
            check_tree.insert(check_tree.begin()+i, tmpnode);
        }
        cout << endl;

    }
	symbol_file.close();
}
