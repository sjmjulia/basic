/*
 * File: program.cpp
 * -----------------
 * This file is a stub implementation of the program.h interface
 * in which none of the methods do anything beyond returning a
 * value of the correct type.  Your job is to fill in the bodies
 * of each of these methods with an implementation that satisfies
 * the performance guarantees specified in the assignment.
 */

#include <string>
#include "program.h"
#include "statement.h"
#include "hashmap.h"
using namespace std;

Program::Program() {
	// Replace this stub with your own code
}

Program::~Program() {
    foreach (int lineNumber in stmtMap) {       
        delete stmtMap[lineNumber]->stmt;
        delete stmtMap[lineNumber];
    }
}

void Program::clear() {
    foreach (int lineNumber in stmtMap) {
        delete stmtMap[lineNumber]->stmt;
        delete stmtMap[lineNumber];
    }
    stmtMap.clear();    
    lineNumVec.clear(); 
}

void Program::addSourceLine(int lineNumber, string line) {
    if (!stmtMap.containsKey(lineNumber)) {
        stmtMap.put(lineNumber,new StrStmt);
        stmtMap[lineNumber]->stmt=NULL;
        if (lineNumVec.isEmpty() || lineNumber>lineNumVec[lineNumVec.size()-1]) {
            lineNumVec.add(lineNumber);
            stmtMap[lineNumber]->indx=lineNumVec.size()-1;
        }
        else {
            for (int i=0; i<lineNumVec.size(); i++) {
                if (lineNumber<lineNumVec[i]) {
                    lineNumVec.insertAt(i,lineNumber);
                    stmtMap[lineNumber]->indx=i;
                    for (int j=i+1;j<lineNumVec.size();j++) {
                        stmtMap[lineNumVec[j]]->indx++;
                    }
                    break;
                }
            }       
        }
    }
    stmtMap[lineNumber]->str=line;
}

void Program::removeSourceLine(int lineNumber) {
    if (stmtMap.containsKey(lineNumber)) {
        int idx=stmtMap[lineNumber]->indx;
        lineNumVec.removeAt(idx);
        for (int i=idx; i<lineNumVec.size(); i++) {
            stmtMap[lineNumVec[i]]->indx--;
        }
        delete stmtMap[lineNumber]->stmt;
        delete stmtMap[lineNumber];
        stmtMap.remove(lineNumber);
    }
	
}

string Program::getSourceLine(int lineNumber) {
    if (stmtMap.containsKey(lineNumber)) {
        return stmtMap[lineNumber]->str;
    }
    else return "";    
}

void Program::setParsedStatement(int lineNumber, Statement *stmt) {
    if (stmtMap.containsKey(lineNumber)) {
        if (stmtMap[lineNumber]->stmt!=NULL) delete stmtMap[lineNumber]->stmt;
        stmtMap[lineNumber]->stmt=stmt;
    }
    else error("No such line number exists!");
    
}

Statement *Program::getParsedStatement(int lineNumber) {
    if (stmtMap.containsKey(lineNumber)) {
        return stmtMap[lineNumber]->stmt;
    }
    else return NULL;
}

int Program::getFirstLineNumber() {
    if (!lineNumVec.isEmpty()) {
        return lineNumVec[0];
    }
    else return -1;
}

int Program::getNextLineNumber(int lineNumber) {
    if (stmtMap.containsKey(lineNumber)) {
        int idx=stmtMap[lineNumber]->indx;
        if (idx<lineNumVec.size()-1) {
            return lineNumVec[idx+1];
        }
        else return -1;
    }
    else if (lineNumVec[lineNumVec.size()-1]<=lineNumber) {
        return -1;
    }
    else {
        for (int i=0; i<lineNumVec.size();i++)
        {
            if (lineNumVec[i]>lineNumber) {
                return lineNumVec[i];
            }
        }
    }
	
}