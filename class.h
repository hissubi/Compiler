#ifndef CLASS_H
#define CLASS_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#define N_TERMINAL 18
#define N_NONTERMINAL 16
#define N_GRAMMAR 25

using namespace std;

class Node{
    public:
    string data;
    int childn;
    Node* parent;
    vector<Node*> child;
    int line_num;

    int resistor;
    int label;
    int scope;
};

class Grammar{
    public:
    vector<string> rhs;
    int grammar_id;
};

class Nonterminal{
    public:
    string nonterminal;
    int nonterminal_id;
};

class Terminal{
    public:
    string terminal;
    int terminal_id;
};

#endif
