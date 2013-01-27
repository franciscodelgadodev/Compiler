#include <iostream>
using namespace std;

#include <cstdlib>

#include "Lexicon.h"
#include "Syntactic.h"


Lexicon lexico("test.txt");     

//constructor
Syntactic::Syntactic(){
}

//begin syntactic analysis process
void Syntactic::startSyntacticAnalysis(){
  if(lexico.nextSymbol())
    statement();
  else
    finishedSyntacticAnalysis();
}

//review if a token chain have a correct structure
//type:  <Statement>      ::= <dataType><identifier><IdentifierList>;
//       <IdentifierList> ::= <,><identifier><IdentifierList>
//       <IdentifierList> ::= <empty>
void Syntactic::statement(){
  if(isDataType(lexico.getSymbol())){
    if(lexico.nextSymbol() && lexico.getTypeSymbol() == "identifier"){
      lexico.nextSymbol();
      identifiersList();
      if(lexico.getSymbol() == ";"){
        successSyntacticAnalysis();
        lexico.setLine("");
        startSyntacticAnalysis();
      }else{
        syntacticError(2, "<;>");
      }
    }else{
      syntacticError(2, "<identifier>");
    }
  }else{ 
    syntacticError(3, "<dataType>");
  }
}

//recursive method for find each identifier in list of variables.
void Syntactic::identifiersList(){  
  if(lexico.getSymbol() == ","){
    if(lexico.nextSymbol() && lexico.getTypeSymbol() == "identifier"){
        lexico.nextSymbol();
        identifiersList();
    }else{
      syntacticError(2, "<identifier>");
    }
  }
}

//check if a symbol is a data type.
//string param receives a symbol that will be compared with all data types
//return true if symbol is a data type and false if isn't
bool Syntactic::isDataType(const string symbol){
  int TOTAL_DATA_TYPES = 11;
  string dataTypes[] = {"char","short int","int","long int","long","bool","float","double","long double","wchar_t","string"};
  return inArray(dataTypes, TOTAL_DATA_TYPES, symbol);
}

//check if an element belongs to an array of strings
//string array param receives a list to try find a element
//int param receives the array's size
//string param receives the element to find in array
bool Syntactic::inArray(string array[], const int length, const string element){
  for(int i = 0; i < length; i++){
    if(array[i] == element)
      return true;
  }    
  return false;
}

//print a message to notify the analysis was finished
void Syntactic::finishedSyntacticAnalysis(){
  cout << "Syntactic analysis finished."<< endl; 
}

//print a message to notify the analysis was finished successful
void Syntactic::successSyntacticAnalysis(){
  cout << "The expression '" << lexico.getLine() << " ' match with the grammar rules" << endl; 
}

//method for control errors
//print a message to alert the analysis was finished with errors
//int param receives the type of error ocurred
//string param receives a string for message complement. It will concat to type message
void Syntactic::syntacticError(const int type, const string missingTokens){
  switch(type){
    case 2:
      cout << "Expected a " << missingTokens << " after '" << lexico.getLine() << " '" << endl;
    break;
    case 3:
      cout << "Expected a " << missingTokens << " got a <" << lexico.getTypeSymbol() << ">" << endl;
    break;
  } 
  abort(); //Abort process. In <cstdlib>.
} 
