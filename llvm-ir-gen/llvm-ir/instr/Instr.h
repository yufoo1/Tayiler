//
// Created by yufoo1 on 2022/10/27.
//

#ifndef TAYILER_INSTR_H
#define TAYILER_INSTR_H

#include "../Use.h"

static string LOCAL_PREFIX = "%";
static string LOCAL_NAME_PREFIX = "v";
static map<string, map<Value*, int>*> POSMAP;
static map<Value*, int>* MAINPOSMAP = new map<Value*, int>;

static void ALLOCSTACK(const string& label, Value* value) {
    if(label.empty() || label == "main") {
        MAINPOSMAP->insert({value, MAINPOSMAP->size() * (-4)});
    } else {
        POSMAP.at(label)->insert({value, POSMAP.at(label)->size() * 4});
    }
}

static void GENMAP(const string& ident) {
    POSMAP.insert({ident, new map<Value *, int>()});
}

static int GETPOS(const string& ident, Value* value) {
    if(POSMAP.count(ident) && POSMAP.at(ident)->count(value)) {
        return POSMAP.at(ident)->at(value);
    } else {
        return MAINPOSMAP->at(value);
    }
    return POSMAP.count(ident) && POSMAP.at(ident)->count(value) ? POSMAP.at(ident)->at(value) : MAINPOSMAP->at(value);
}

static bool MAINPOSMAPHASPOS(Value* value) {
    return MAINPOSMAP->count(value);
}

static bool POSMAPHASPOS(const string& ident, Value* value) {
    return POSMAP.count(ident) && POSMAP.at(ident)->count(value);
}

class Instr: public Value {
public:
    Instr() = default;

    virtual string toLlvmString() override { return 0; }

    virtual string toMipsString_stack(string ident) override { return 0; }

    virtual bool hasValue() { return 0; }

protected:

    void genInstrVirtualReg(int idx) {
        setVal(LOCAL_PREFIX + LOCAL_NAME_PREFIX + to_string(idx));
    }
public:
    bool isInstr() override {
        return true;
    }
};

#endif //TAYILER_INSTR_H