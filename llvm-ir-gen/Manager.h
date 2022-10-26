//
// Created by yufoo1 on 2022/10/26.
//

#ifndef TAYILER_MANAGER_H
#define TAYILER_MANAGER_H


#include "Symble/SymbleTable.h"

class Manager {
public:
    Manager() {

    }

    SymbleTable getSymbleTable() {
        return symbleTable;
    }

private:
    SymbleTable symbleTable;
};
#endif //TAYILER_MANAGER_H
