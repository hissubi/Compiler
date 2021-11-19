#include "compiler.h"

using namespace std;

int main(int argc, string* argv)
{
    if(argc != 2){
        cout << "Input File Error!" << endl;
        return 0;
    }

    string input_file_name = argv[1];
    
    ifstream target_file;
    ofstream instruction_file;
    ofstream symbol_file;

    target_file.open(input_file_name);
    instruction_file.open(input_file_name + ".code");
    symbol_file.open(input_file_name + ".symbol");

    vector<vector<string>> tokens;
    bool is_error = -1;

    is_error = lexical_analyzer(target_file, tokens);
    is_error = syntax_analyzer();
    is_error = code_generator();
 


    target_file.close();
    instruction_file.close();
    symbol_file.close();
}
