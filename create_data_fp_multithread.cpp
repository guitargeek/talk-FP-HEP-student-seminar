#include "TFile.h"
#include "TRandom.h"
#include "EventTree.h"

#include <vector>
#include <cmath>
#include <thread>

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
    const int nEvents {100000}; // number of events to simulate
    const int nThreads {8};

    TFile file {"data.root", "RECREATE"};

    MySimulator simulator{};

    auto simulateEvents = [&]() {
        for(int iEvent = 0; iEvent < nEvents/nThreads; ++iEvent)
            simulator.simulate(iEvent);
    };

    std::vector<std::thread> threads;
    for(int i = 0; i < nThreads; ++i) threads.emplace_back(simulateEvents);
    for(auto& thread : threads) thread.join();
}
