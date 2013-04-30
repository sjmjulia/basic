/*
 * File: Basic.cpp
 * ---------------
 * Name: Xin Qiu
 * Section: Daniel Colon
 * This program simulates the minimal BASIC interpreter
 * 
 */

#include <cctype>
#include <iostream>
#include <string>
#include "console.h"
#include "exp.h"
#include "parser.h"
#include "program.h"
#include "tokenscanner.h"
#include "simpio.h"
#include "strlib.h"
using namespace std;

/* Function prototypes */

void processLine(string line, Program & program, EvalState & state);

/* Main program */

int main() {
	EvalState state;
	Program program;
	cout << "Minimal BASIC -- Type HELP for help\n" << endl;
	while (true) {
		try {
			processLine(getLine(), program, state);
		} catch (ErrorException & ex) {
			cerr << "Error: " << ex.getMessage() << endl;
		}
	}
	return 0;
}

/*
 * Function: processLine
 * Usage: processLine(line, program, state);
 * -----------------------------------------
 * Processes a single line entered by the user.  In this version,
 * the implementation does exactly what the interpreter program
 * does in Chapter 17: read a line, parse it as an expression,
 * and then print the result.  In your implementation, you will
 * need to replace this method with one that can respond correctly
 * when the user enters a program line (which begins with a number)
 * or one of the BASIC commands, such as LIST or RUN.
 */

void processLine(string line, Program & program, EvalState & state) {
	TokenScanner scanner;
	scanner.ignoreWhitespace();
	scanner.scanNumbers();
	scanner.setInput(line);
    string str=scanner.nextToken();
    if (scanner.getTokenType(str)==NUMBER) {
		
        int lineNumber=stringToInteger(str);
        string token=scanner.nextToken();
        scanner.saveToken(token);
        if (token!="") {
            program.addSourceLine(lineNumber, line);
            program.setParsedStatement(lineNumber, parseStatement(scanner));
        }
        else {
            program.removeSourceLine(lineNumber);
        }
		
		
    }
	
    else if (str=="LIST") {
        for (int i=program.getFirstLineNumber(); i!=-1; i=program.getNextLineNumber(i)) {
            cout << program.getSourceLine(i)<<endl;
        }
    }
    else if (str=="CLEAR") {
        program.clear();
    }
    else if(str=="QUIT") exit(0);
    else if (str=="HELP") cout<<"This is a minimal BASIC interpreter."<<endl;
	
    else if (str=="RUN") {
        int currentLine=program.getFirstLineNumber();
        state.setCurrentLine(currentLine);
        while (currentLine!=-1) {                       
            program.getParsedStatement(currentLine)->execute(state);
			
            if(currentLine!=state.getCurrentLine()) {
                currentLine=state.getCurrentLine();
            }
            else {
                currentLine=program.getNextLineNumber(currentLine);
                state.setCurrentLine(currentLine);
            }
        }
    }
	
	
}
