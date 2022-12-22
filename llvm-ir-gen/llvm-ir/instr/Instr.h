//
// Created by yufoo1 on 2022/10/27.
//

#ifndef TAYILER_INSTR_H
#define TAYILER_INSTR_H

#include "../Use.h"

static string LOCAL_PREFIX = "%";
static string LOCAL_NAME_PREFIX = "v";
static map<string, map<Value*, int>*> POSMAP;
static map<string, int> POSMAPSIZE;
static map<Value*, int>* MAINPOSMAP = new map<Value*, int>;
static int MAINPOSMAPSIZE = 0;

static void ALLOCSTACK(const string& label, Value* value, int size) {
    if(size != 0) {
        if(label.empty() || label == "main") {
            MAINPOSMAP->insert({value, -1 * MAINPOSMAPSIZE});
            MAINPOSMAPSIZE += size;
        } else {
            POSMAP.at(label)->insert({value, POSMAPSIZE.at(label)});
            POSMAPSIZE.at(label) += size;
        }
    }
}

static void GENMAP(const string& ident) {
    POSMAP.insert({ident, new map<Value *, int>()});
    POSMAPSIZE.insert({ident, 0});
}

static int GETPOS(const string& ident, Value* value) {
    if( POSMAP.count(ident) && POSMAP.at(ident)->count(value)) {
        return POSMAP.at(ident)->at(value);
    } else if(MAINPOSMAP->count(value)) {
        return MAINPOSMAP->at(value);
    }
    return 0;
}

static bool MAINPOSMAPHASPOS(Value* value) {
    return MAINPOSMAP->count(value);
}

static bool POSMAPHASPOS(const string& ident, Value* value) {
    return POSMAP.count(ident) && POSMAP.at(ident)->count(value);
}

class Instr: public Value {
private:
    int size = 0;
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

    void setSize(int size) {
        this->size = size;
    }

    int getSize() {
        return size;
    }
};

#endif //TAYILER_INSTR_H