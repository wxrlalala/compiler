#ifndef PARSER_H
#define PARSER_H
#include"component.h"

#include<vector>
#include<string>
#include<unordered_map>
#include<map>
#include<assert.h>
#include<set>
#include<stack>
#include<tuple>
#include<stdlib.h>

//struct my_less {
    //bool operator()(const std::tuple<int, std::string>& s1,const std::tuple<int, std::string>&s2)const {
        //return std::get<0>(s1) < std::get<0>(s2) && std::get<1>(s1) < std::get<1>(s2);
    //}
//};
class Parser {
public:
    //std::vector<GrammarEntry> grammar;
    std::unordered_map<std::string, std::vector<GrammarEntry*>> grammar;

    std::set < std::string > grammarSymbols;
    GrammarEntry* startEntry;
    //std::unordered_map<Symbol, std::set<Symbol>, Symbol_hash> firstMap;
    std::unordered_map<std::string, std::set<std::string>,std::hash<std::string>> firstVN;
    std::vector<std::set<Item>> cluster;

    //std::vector<Action> actions;
    std::map<std::tuple<int, std::string>, TableEntry> table;
    //std::vector<Goto> gotos;
    //std::unordered_map<std::tuple<int, std::string>, Action> gotos;

    // 
    std::stack<int> stateStack;
    std::stack<Symbol> symbolStack;
    int inputPos; // inputString position
public:
    ~Parser();
    void readGrammar(const std::string& filename);
    void printGrammar(const std::string& filename);
    void printVNFirst(const std::string& filename);
    void printCluster(const std::string& filename);
    void printTable(const std::string& filename);
    // zyw 
    //void calFirst();
    //std::set<Item> calClosure(const std::set<Item>& itemSet);
    std::set<Item> GO(const std::set<Item>& itemSet, const std::string& x);
    void constructCluster();
    void constructTable();
    void constructDFA(const std::string& filename);

	//wtc
    std::set<std::string> calFirst(const std::vector<Symbol> &rhs, size_t ofst, const Symbol &peek);
    void closure(std::set<Item> &itemSet);
    void calFirstVN();

    // analyze
    //Action* findAction(int s,std::string in);
    //Goto* findGoto(int s, std::string sym);
    void analyze(const std::vector<std::string>& symbols, const std::string& filename);
};

class Loader{
public:
    static Symbol loadSymbol(const string& s){
        assert(s[0]=='<' || s[0] == '$' || s[0] == '@');
        if(s[0] == '<'){
            assert(s[s.length()-1]=='>');
            return Symbol(s,false);
        }
        else if (s[0] == '$'){
            return Symbol(s,true);
        }
        else if (s[0] == '@') {
            return Symbol(s, true, true);
        }
        assert(0);
    }
    static Symbol loadSymbolYacc(const string& s) {
        if (s[0] >= 'A' && s[0] <= 'Z' || s[0] == '\'') {
            // is terminal
            return Symbol(s, true);
        }
        else if (s[0] >= 'a' && s[0] <= 'z') {
            // not terminal
            return Symbol(s, false);
        }
    }
};

#endif // PARSER_H
