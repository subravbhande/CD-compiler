#include "Compiler.h"

#include <iostream>
#include <cstdlib>

using namespace std;


Compiler::Compiler(
    const string& source,
    const string& executable
) : sourceFile(source), executableFile(executable) {}


// ==========================================
// G++ COMPILATION
// ==========================================

bool Compiler::compile() {

    cout << "\n========== G++ COMPILATION ==========\n";

    string command =
        "g++ -std=c++17 \"" +
        sourceFile +
        "\" -o \"" +
        executableFile +
        "\"";


    cout << "\nExecuting:\n";

    cout << command << "\n\n";


    int result =
        system(command.c_str());


    if (result != 0) {

        cout << "\nCompilation Failed!\n";

        return false;
    }


    cout << "\nCompilation Successful!\n";

    cout << "Executable created: "
         << executableFile
         << "\n";

    return true;
}


// ==========================================
// EXECUTION
// ==========================================

bool Compiler::execute() {

    cout << "\n========== PROGRAM EXECUTION ==========\n";

    cout << "\nOutput:\n\n";


    string command =
        "\"" +
        executableFile +
        "\"";


    int result =
        system(command.c_str());


    if (result != 0) {

        cout << "\nProgram execution failed.\n";

        return false;
    }


    cout << "\n\nProgram executed successfully.\n";

    return true;
}