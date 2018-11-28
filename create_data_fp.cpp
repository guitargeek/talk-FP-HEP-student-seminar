#include "TFile.h"
#include "TRandom.h"
#include "EventTree.h"

#include <vector>
#include <cmath>


class MySimulator {

  public:

    MySimulator() : tree_("tree", "tree") {}
    ~MySimulator() { tree_.write(); }

    void simulate(int iEvent) const
    {
        // how many electrons?
        const unsigned int nElectrons {4 + rng_.Integer(4)};

        std::vector<float> etaVec(nElectrons);
        std::vector<float> phiVec(nElectrons);
        std::vector<float> ptVec(nElectrons);

        for (auto& x : etaVec) x = rng_.Uniform() * 5.0 - 2.5;
        for (auto& x : phiVec) x = rng_.Uniform() * 2.*M_PI - M_PI;
        for (auto& x : ptVec)  x = rng_.Exp(10.) + 20.;

        tree_.fill({ .nElectrons = nElectrons,
                     .etaVec     = etaVec,
                     .phiVec     = phiVec,
                     .ptVec      = ptVec       });
    }

  private:

    EventTree tree_;
    mutable TRandom rng_;
};

int main()
{
    const int nEvents {10000}; // number of events to simulate

    TFile file {"data.root", "RECREATE"};

    MySimulator simulator{};

    for(int iEvent = 0; iEvent < nEvents; ++iEvent) simulator.simulate(iEvent);
}
