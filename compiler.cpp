#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

char operators[] = {'+', '*', '<', ';', '=', '(', ')', '{', '}'};

bool lexical_analyzer(ifstream& read_file, vector<vector<string>> token);
//bool syntax_analyzer(vector<vector<string>> token);
//bool code_generator(vector<vector<string>> token);

int main(int argc, char** argv)
{
    if(argc != 2){
        cout << "Input File Error!" << endl;
        return 0;
    }

    string input_file_name(argv[1]);
    
    ifstream target_file;
    ofstream instruction_file;
    ofstream symbol_file;

    target_file.open(input_file_name);
    instruction_file.open(input_file_name + ".code");
    symbol_file.open(input_file_name + ".symbol");

    vector<vector<string>> tokens;
    bool is_error = -1;

    is_error = lexical_analyzer(target_file, tokens);
    //is_error = syntax_analyzer(tokens);
    //is_error = code_generator(tokens);
 


    target_file.close();
    instruction_file.close();
    symbol_file.close();
}
