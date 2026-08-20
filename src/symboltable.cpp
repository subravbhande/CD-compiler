#include "SymbolTable.h"

#include <iostream>

using namespace std;


void SymbolTable::insert(
    const string& name,
    const string& type
) {

    table[name] = type;
}


bool SymbolTable::exists(const string& name) {

    return table.find(name) != table.end();
}


void SymbolTable::display() {

    cout << "\n========== SYMBOL TABLE ==========\n";

    cout << "Name\t\tType\n";

    cout << "--------------------------------\n";

    for (auto& item : table) {

        cout << item.first
             << "\t\t"
             << item.second
             << "\n";
    }
}