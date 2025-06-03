#ifndef COMPAREWORDS_H
#define COMPAREWORDS_H
#include "Word.h"

struct CompareWords
{
    bool operator()(const Word* a, const Word* b) const
    {
        return a->getPriority() < b->getPriority();
    }
};

#endif //COMPAREWORDS_H