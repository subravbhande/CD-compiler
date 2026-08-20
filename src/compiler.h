#ifndef COMPILER_H
#define COMPILER_H

#include <string>

class Compiler {

private:

    std::string sourceFile;

    std::string executableFile;

public:

    Compiler(
        const std::string& source,
        const std::string& executable
    );

    bool compile();

    bool execute();
};

#endif