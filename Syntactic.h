#include "Lexicon.h"

#ifndef SYNTACTIC_H
#define SYNTACTIC_H


class Syntactic
{
    public:
        Syntactic();
        void startSyntacticAnalysis();
    protected:
    private:
        void statement();
        void identifiersList();
        void syntacticError(const int, const string);
        bool isDataType(const string);
        bool inArray(string*, const int, const string);
        void finishedSyntacticAnalysis();
        void successSyntacticAnalysis();
};

#endif // SYNTACTIC_H
