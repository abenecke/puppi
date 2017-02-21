#pragma once

#include "UHH2/core/include/Hists.h"
#include "TH2F.h"

namespace uhh2examples {


class PuppiJetHists: public uhh2::Hists {
public:
    // use the same constructor arguments as Hists for forwarding:
    PuppiJetHists(uhh2::Context & ctx, const std::string & dirname);

    virtual void fill(const uhh2::Event & ev) override;
    virtual ~PuppiJetHists();
  protected:
    bool berror;

    //Jet pT scale
    TH2F *JetPtScale_Eta0to1p3,*JetPtScale_Eta1p3to2,*JetPtScale_Eta2to2p5,*JetPtScale_Eta2p5to3,*JetPtScale_Eta3to10;

    //Jet Efficiency
    TH1F *JetEfficiency_GenJetEta,*JetEfficiency_GenJetPt, *JetEfficiency_GenJetNPV,*JetEfficiency_GenJetEta_matchedjet,*JetEfficiency_GenJetPt_matchedjet, *JetEfficiency_GenJetNPV_matchedjet;

    //Jet Purity
    TH2F *JetPurity_GenJetEta, *JetPurity_GenJetPt, *JetPurity_GenJetNPV;
};

}
