#ifndef __EVENT_TREE__
#define __EVENT_TREE__

#include "STree.h"

struct EventRecord {
    unsigned int       nElectrons;
    std::vector<float> etaVec;
    std::vector<float> phiVec;
    std::vector<float> ptVec;
};

template<>
void STree<EventRecord>::init() {
    addBranch("n"    , &EventRecord::nElectrons);
    addBranch("eta"  , &EventRecord::etaVec);
    addBranch("phi"  , &EventRecord::phiVec);
    addBranch("pt"   , &EventRecord::ptVec);
}

using EventTree = STree<EventRecord>;

# endif
