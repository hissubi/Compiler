#ifndef CLASS_H
#define CLASS_H
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#define N_TERMINAL 10
#define N_NONTERMINAL 10

using namespace std;

class Node{
    string token;
    int grammer_id;
    int childn;
    vector<Node*> child;
};

class Grammar{
    public:
    vector<string> rhs;
    int grammer_id;
};

class Nonterminal{
    string nonterminal;
    int nonterminal_id;
};

class Terminal{
    string terminal;
    int terminal_id;
};

#endif
