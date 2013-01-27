#include <iostream>
using namespace std; 

#include <fstream>
#include <string>
using std::string;

#include <cstdlib>
#include "Lexicon.h"


const int STATES = 20;
const int ENTRIES = 16;

//states machine for lexicon analizier
static int statesTable[STATES][ENTRIES] = {
  /*        0    1    2    3    4    5    6    7    8    9   10   11   12   13   14   15    */
  /*     (let)(dig)(+,-)(*,/)(<,>)  (=)  (!)  (&)  (|)  (;)  (,)  (()  ())  ({)  (})  (.)   */
  /* 0*/    1,   2,   5,   6,   7,   9,  10,  11,  13,  14,  15,  16,  17,  18,  19,  -1,
  /* 1*/    1,   1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
  /* 2*/   -1,   2,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,   3,
  /* 3*/   -1,   4,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
  /* 4*/   -1,   4,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
  /* 5*/   -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
  /* 6*/   -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
  /* 7*/   -1,  -1,  -1,  -1,  -1,   8,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
  /* 8*/   -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
  /* 9*/   -1,  -1,  -1,  -1,  -1,   8,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
  /*10*/   -1,  -1,  -1,  -1,  -1,   8,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
  /*11*/   -1,  -1,  -1,  -1,  -1,  -1,  -1,  12,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
  /*12*/   -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
  /*13*/   -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  12,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
  /*14*/   -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
  /*15*/   -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
  /*16*/   -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
  /*17*/   -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
  /*18*/   -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
  /*19*/   -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1
};

//constructor
//open a txt file
Lexicon::Lexicon(const string fileName){
  Lexicon::file.open(fileName.c_str(), ifstream::in);
  setLine("");
}

//get method for acumulate expression
//return line variable
string Lexicon::getLine(){
  return Lexicon::line;
}

//set method for acumulate expression
//string param save a modified expression
void Lexicon::setLine(string line){
  Lexicon::line = line;
}

//get method for symbol
//return symbol variable  
string Lexicon::getSymbol(){
  return Lexicon::symbol;
}

//set method for symbol
//string param save a symbol 
void Lexicon::setSymbol(string symbol){
  Lexicon::symbol = symbol;
}

//get method for symbol type
//return typeSymbol variable
string Lexicon::getTypeSymbol(){
  return Lexicon::typeSymbol;
}

//set method for symbol type
//string param save symbol type 
void Lexicon::setTypeSymbol(string typeSymbol){
  Lexicon::typeSymbol = typeSymbol;
}

//reset the instance variables
void Lexicon::resetLexiconAttributes(){
  setSymbol("");
  setTypeSymbol(""); 
}

//return a position the file pointer
void Lexicon::backPointer(){
  int pointerPosition = Lexicon::file.tellg();
  Lexicon::file.seekg(pointerPosition-1); 
}

//It does a transition for next state
//int param receives the current state
//int param receives the number of classification for current symbol
//return the new state for states machine
int Lexicon::getNextState(const int state, const int typeSymbol)
{
  return statesTable[state][typeSymbol];
}

//it tries read a next token in file opened on constructor method
//read each character in file opened in constructor and searchs a new valid token. It uses the states machine
//if this method find a invalid character will finish the process alerting to user the error
//At final methos the file opened in constructor methos will be closed
//return false if file pointer is in EOF
//return true if lexicon analysis find a new valid token
bool Lexicon::nextSymbol(){
  char character;
  int state = 0;
  int typeChar = 0;
  resetLexiconAttributes();

  while(character = Lexicon::file.get()){
    typeChar = classifyChar(character);  
    if(typeChar == -1){
      if(character == EOF)
        return false;
      lexiconError(character);
    }else{
      if(typeChar != -2){
        state = getNextState(state, typeChar);
        if(state == -1){
          backPointer();
          setLine(getLine() +" "+ getSymbol());
          return true; //succefull symbol        
        }else{
            setTypeSymbol(classifySymbol(state));
            setSymbol(getSymbol() +""+ character);
        } 
      }else{
        if(getSymbol().length() > 0){
          setLine(getLine() +" "+ getSymbol());
          return true; //succefull symbol
        }
      }
    }    
  }  
  file.close();
}

//classify a character with a number because this character will be interpreted in the states machine
//the number for character has a direct relationship with de columns in the states machine
//you can see that all classification numbers in this method belongs to a column in the states machine
//if the given character doesn't belong to the lexicon snalyses return -1. It will be an error in the states machine transition
//char param receives the character that will be classificated
//return the classification number for the given character
int Lexicon::classifyChar(const char character){
  int typeChar;
  switch(character){
    case ' ':case '\0':case '\n':case '\t':case '\v':case '\r':case '\b':
      typeChar = -2;
    break;
    case '+':case '-':
      typeChar = 2;
    break;
    case '*':case '/':
      typeChar = 3;
    break;
    case '<':case '>':
      typeChar = 4;
    break;
    case '=':
      typeChar = 5;
    break;
    case '!':
      typeChar = 6;
    break;
    case '&':
      typeChar = 7;
    break;
    case '|':
      typeChar = 8;
    break;
    case ';':
      typeChar = 9;
    break;
    case ',':
      typeChar = 10;
    break;
    case '(':
      typeChar = 11;
    break;
    case ')':
      typeChar = 12;
    break;
    case '{':
      typeChar = 13;
    break;
    case '}':
      typeChar = 14;
    break;
    case '.':
      typeChar = 15;
    break;
    default:
      if(isalpha(character))
        typeChar = 0;
      else if(isdigit(character))
        typeChar = 1;
      else
        typeChar = -1;
    break;
  }
  return typeChar;
}

//classify a symbol in a type of token
//when the process is running the state determine where should be classified the symbol. This method make that homework
//int param reveives the current state given for the states machine in a new transition
//return a string classification for the current state. It will be notified to syntactic analizier
string Lexicon::classifySymbol(const int state){
  string type;
  switch(state){
    case 1:
      type = "identifier";
    break;
    case 2:
      type = "integer";
    break;
    case 4:
      type = "float";
    break;
    case 5:
      type = "addition - substraction";
    break;
    case 6:
      type = "multiplication - division";
    break;
    case 14:
      type = "colon";
    break;
    case 15:
      type = "comma";
    break;
  }
  return type;
}

//print an alert to inform the user that one symbol was not valid for lexicon analizier.
//just the characters written in the states machine will be accepted.
//char param receives the invalid character for ths analizier
void Lexicon::lexiconError(const char character){
  cout << "Error, the caracter '" << character << "' does't belong to this Lexicon analysis." << endl;
  abort(); //Abort process. In <cstdlib>.
}
