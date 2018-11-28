#ifndef __S_TREE__
#define __S_TREE__

#include "TTree.h"

#include <mutex>
#include <iostream>

template<class T>
void addTreeBranch(TTree* tree, const char* name,  T& variable) {
    tree->Branch(name, &variable);
}

#define TYPES_WITH_SUFFIX \
     X(char          , "/B") X(unsigned char , "/b") \
     X(short         , "/S") X(unsigned short, "/s") \
     X(int           , "/I") X(unsigned int  , "/i") \
     X(long          , "/L") X(unsigned long , "/l") \
     X(float         , "/F") X(double        , "/D") \
     X(char *        , "/C") X(bool , "/O")

#define X(Type, suffix) \
template<> \
void addTreeBranch<Type>(TTree* tree, const char* name, Type& variable) { \
    tree->Branch(name, &variable, (std::string(name) + suffix).c_str()); \
}
TYPES_WITH_SUFFIX
#undef X

#undef TYPES_WITH_SUFFIX

template <typename T>
class STree {

  public:

    STree(const char* name, const char* title)
        : tree_(new TTree(name, title))
    { init(); }

    void init();

    void write() const { tree_->Write(); }
    void print() const { tree_->Print(); }

    void fill(T && structure) const {
        std::lock_guard<std::mutex> lock {mutex_};
        structure_ = std::move(structure);
        tree_->Fill();
    }

  private:

    template<class S>
    void addBranch(const char* name, S foo) {
        addTreeBranch(tree_, name, structure_.*foo);
    }

    TTree * tree_;
    mutable T structure_;
    mutable std::mutex mutex_;

};

#endif
