#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include <string>
#include <map>

class SymbolTable {

private:

    std::map<std::string, std::string> table;

public:

    void insert(
        const std::string& name,
        const std::string& type
    );

    bool exists(const std::string& name);

    void display();
};

#endif