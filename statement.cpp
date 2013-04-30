/*
 * File: statement.cpp
 * -------------------
 * This file implements the constructor and destructor for
 * the Statement class itself.  Your implementation must do
 * the same for the subclasses you define for each of the
 * BASIC statements.
 */

#include <string>
#include "statement.h"
#include "exp.h"
#include "parser.h"
#include "simpio.h"
#include "strlib.h"
using namespace std;

/* Implementation of the Statement class */

Statement::Statement() {
	/* Empty */
}

Statement::~Statement() {
	/* Empty */
}


RemStmt::RemStmt(TokenScanner & scanner) {
	
}

RemStmt::~RemStmt() {
	
}

void RemStmt::execute(EvalState & state){
	
}


PrintStmt::PrintStmt(TokenScanner & scanner) {
    exp=parseExp (scanner);
    if (scanner.hasMoreTokens()) {
        error("Extraneous token " + scanner.nextToken());
    }   
}

PrintStmt::~PrintStmt() {
    delete exp;
}

void PrintStmt::execute(EvalState & state) {
    cout << exp->eval(state)<<endl;
}

LetStmt::LetStmt(TokenScanner & scanner) {
    name=scanner.nextToken();
    if(scanner.nextToken()!="=") error("Invalid LET statement!");
    rhs=readE(scanner);
}

LetStmt::~LetStmt() {
    delete rhs;
}

void LetStmt::execute(EvalState &state){
    state.setValue(name,rhs->eval(state));
}

InputStmt::InputStmt(TokenScanner &scanner) {
    name=scanner.nextToken();
}

InputStmt::~InputStmt(){
	
}

void InputStmt::execute(EvalState &state) {
    string str;
    str=getLine("?");
    state.setValue(name,stringToInteger(str));
}

GotoStmt::GotoStmt(TokenScanner &scanner) {
    string str=scanner.nextToken();
    gotoLine=stringToInteger(str);
}

GotoStmt::~GotoStmt() {
	
}

void GotoStmt::execute(EvalState &state) {
    state.setCurrentLine(gotoLine);
}

EndStmt::EndStmt(TokenScanner &scanner) {
	
}

EndStmt::~EndStmt() {
	
}

void EndStmt::execute(EvalState &state) {
    state.setCurrentLine(-1);
}

IfStmt::IfStmt(TokenScanner &scanner) {
    string strExpOne,strExpTwo,next;
    strExpOne="";
    strExpTwo="";
    while (true) {
        next=scanner.nextToken();
        if (next=="=" || next=="<" || next==">") break;
        strExpOne += next;
    }
    TokenScanner scannerOne(strExpOne);
    scannerOne.ignoreWhitespace();
    scannerOne.scanNumbers();
    expOne=parseExp(scannerOne);
    op=next;
    while (true) {
        next=scanner.nextToken();
        if(next=="THEN") break;
        strExpTwo+=next;
    }
    TokenScanner scannerTwo(strExpTwo);
    scannerTwo.ignoreWhitespace();
    scannerTwo.scanNumbers();
    expTwo=parseExp(scannerTwo);
    thenLine=stringToInteger(scanner.nextToken());
	
}

IfStmt::~IfStmt() {
    delete expOne;
    delete expTwo;
}

void IfStmt::execute(EvalState &state) {
    int eOne=expOne->eval(state);
    int eTwo=expTwo->eval(state);
    if((op=="=" && eOne==eTwo) || (op==">" && eOne>eTwo) || (op=="<" && eOne<eTwo))
        state.setCurrentLine(thenLine); 
}