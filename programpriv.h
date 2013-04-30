/*
 * File: programpriv.h
 * -------------------
 * This file contains the private section of the Program class.
 */

private:

// Fill this in with whatever types and instance variables you need
struct StrStmt {
    string str;
    Statement *stmt;
    int indx;
};
HashMap<int, StrStmt * > stmtMap;

Vector<int> lineNumVec;