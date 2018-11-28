#include "TFile.h"
#include "TRandom.h"
#include "TFile.h"
#include "TTree.h"

#include <vector>
#include <cmath>

class MySimulator {
  public:

    MySimulator() {
        tree_ = new TTree("tree", "tree");

        tree_->Branch("n"    , &nElectrons_, "n/i");
        tree_->Branch("eta"  , &etaVec_);
        tree_->Branch("phi"  , &phiVec_);
        tree_->Branch("pt"   , &ptVec_);

        rng_ = new TRandom(); // random number generator
    }

    ~MySimulator() {
        tree_->Write();
        delete rng_;
    }

    void simulate(int iEvent) {
        etaVec_.clear(); // don't forget to clear vectors at each event
        phiVec_.clear();
        ptVec_.clear();

        nElectrons_ = 4 + rng_->Integer(4); // how many electrons?
        for(int iElectron = 0; iElectron < nElectrons_; ++iElectron) {
            phiVec_.push_back( rng_->Uniform() * 2.*M_PI - M_PI );
            etaVec_.push_back( rng_->Uniform() * 5.0 - 2.5      );
            ptVec_ .push_back( rng_->Exp(10.) + 20.             );
        }
        tree_->Fill(); // fill the TTree with event information
    }

  private:

    TTree* tree_;
    TRandom* rng_;

    unsigned int nElectrons_; // variables for TTree branches
    std::vector<float> etaVec_;
    std::vector<float> phiVec_;
    std::vector<float> ptVec_;

};

int main() {
    int nEvents = 10000; // number of events to simulate

    TFile* file = TFile::Open("data.root", "RECREATE");

    {
        MySimulator simulator{};

        for(int iEvent = 0; iEvent < nEvents; ++iEvent) {
            simulator.simulate(iEvent);
        }
    }

    delete file;
}
