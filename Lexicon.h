#include <string>
using std::string;

#include <fstream>

#ifndef LEXICON_H
#define LEXICON_H


class Lexicon
{
  public:
    Lexicon(const string);
    string getSymbol();
    void setSymbol(string);
    string getTypeSymbol();
    void setTypeSymbol(string);
    string getLine();
    void setLine(string); 
    bool nextSymbol();
  protected:
  private:
    ifstream file;
    string line;
    string symbol;
    string typeSymbol;
    void resetLexiconAttributes();
    void backPointer();
    int classifyChar(const char);
    string classifySymbol(const int);
    void lexiconError(const char);
    int getNextState(const int, const int);
};

#endif // LEXICON_H
