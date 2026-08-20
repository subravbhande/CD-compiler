#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Token.h"
#include "Lexer.h"
#include "Parser.h"
#include "Compiler.h"
using namespace std;

void displayTokens(
    const vector<Token>& tokens
) {

    cout << "\n========== LEXICAL ANALYSIS ==========\n\n";
    cout << "Token\t\tType\t\tLine\n";
    cout << "---------------------------------------------\n";


    for (const Token& token : tokens) {

        cout << token.value;

        if (token.value.length() < 8)
            cout << "\t\t";
        else
            cout << "\t";


        cout << tokenTypeToString(token.type);

        cout << "\t\t";

        cout << token.line;

        cout << "\n";
    }
}


// ==========================================
// MAIN
// ==========================================

int main(int argc, char* argv[]) {

    string source;
    string line;
    bool fromFile = false;

    // ========================================
    // INPUT SOURCE CODE
    // ========================================

    if (argc > 1) {
        string inputFileName = argv[1];
        ifstream inputFile(inputFileName);

        if (!inputFile) {
            cout << "\nError: Could not open input file "
                 << inputFileName << "\n";
            return 1;
        }

        while (getline(inputFile, line)) {
            source += line + "\n";
        }

        inputFile.close();
        fromFile = true;
        cout << "\nLoaded source code from: " << inputFileName << "\n";
    }
    else {
        cout << "=============================================\n";
        cout << "          MATH MINI G++ COMPILER             \n";
        cout << "=============================================\n";

        cout << "\nSupported Math Functions:\n";
        cout << "sqrt(), pow(), abs(), sin(), cos(), tan()\n";
        cout << "log(), log10(), ceil(), floor(), exp()\n";
        cout << "round(), fabs()\n";

        cout << "\n---------------------------------------------\n";
        cout << "Enter your C++ program.\n";
        cout << "Type END on a separate line when finished.\n";
        cout << "---------------------------------------------\n\n";

        while (getline(cin, line)) {
            if (line == "END")
                break;
            source += line + "\n";
        }
    }

    // ========================================
    // SAVE SOURCE CODE
    // ========================================

    string sourceFile = "program.cpp";


    ofstream file(sourceFile);


    if (!file) {

        cout << "\nError: "
             << "Could not create program.cpp\n";

        return 1;
    }


    file << source;

    file.close();


    cout << "\nSource code saved as: "
         << sourceFile
         << "\n";


    // ========================================
    // LEXICAL ANALYSIS
    // ========================================

    Lexer lexer(source);


    vector<Token> tokens =
        lexer.tokenize();


    displayTokens(tokens);


    // ========================================
    // SYNTAX ANALYSIS
    // ========================================

    Parser parser(tokens);


    if (!parser.displayResult()) {

        cout << "\nCompilation stopped.\n";

        return 1;
    }


    // ========================================
    // SYMBOL TABLE
    // ========================================

    parser.displaySymbolTable();


    // ========================================
    // G++ COMPILATION
    // ========================================

    Compiler compiler(
        sourceFile,
        "program.exe"
    );


    if (!compiler.compile()) {

        return 1;
    }


    // ========================================
    // EXECUTION
    // ========================================

    compiler.execute();


    cout << "\n=============================================\n";

    cout << "              COMPILATION DONE               \n";

    cout << "=============================================\n";


    return 0;
}