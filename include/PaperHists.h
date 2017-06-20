#pragma once

#include "UHH2/core/include/Hists.h"
#include "UHH2/core/include/Event.h"
#include "UHH2/core/include/PuppiParticle.h"
#include "TH1F.h"
#include "TH2F.h"

using namespace std;
using namespace uhh2;

namespace uhh2examples {


class PaperHists: public uhh2::Hists {
public:
    // use the same constructor arguments as Hists for forwarding:
    PaperHists(uhh2::Context & ctx, const std::string & dirname,const std::string & collection = "packedPFCandidates");

    virtual void fill(const uhh2::Event & ev) override;
    virtual ~PaperHists();
  protected:
    bool berror;

    //General
    Event::Handle<vector<PuppiParticle>> h_myParticles;
    std::string collection;

    //Hists
    TH1F *Alpha,*AlphaMED,*AlphaRMS, *heta, *hpt, *Weight;
    TH2F *alphaMED_eta,*alphaRMS_eta;

};

}
