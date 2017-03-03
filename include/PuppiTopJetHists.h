#pragma once

#include "UHH2/core/include/Event.h"
#include "UHH2/core/include/Hists.h"
#include "TH2F.h"

using namespace std;
using namespace uhh2;
namespace uhh2examples {


class PuppiTopJetHists: public uhh2::Hists {
public:
    // use the same constructor arguments as Hists for forwarding:
    PuppiTopJetHists(uhh2::Context & ctx, const std::string & dirname);

    virtual void fill(const uhh2::Event & ev) override;
    virtual ~PuppiTopJetHists();

  protected:
    bool berror;

    //TopJet pT scale
    TH2F *TopJetPtScale_Eta0to1p3,*TopJetPtScale_Eta1p3to2,*TopJetPtScale_Eta2to2p5,*TopJetPtScale_Eta2p5to3,*TopJetPtScale_Eta3to10;

    //TopJet mass scale
    TH2F *TopJetMassScale_Eta0to1p3,*TopJetMassScale_Eta1p3to2,*TopJetMassScale_Eta2to2p5,*TopJetMassScale_Eta2p5to3,*TopJetMassScale_Eta3to10;

    //TopJet mass scale GeV Scale
    TH2F *TopJetMassScale_GEV_Eta0to1p3,*TopJetMassScale_GEV_Eta1p3to2,*TopJetMassScale_GEV_Eta2to2p5,*TopJetMassScale_GEV_Eta2p5to3,*TopJetMassScale_GEV_Eta3to10;

    //TopJet Efficiency
    TH1F *TopJetEfficiency_GenTopJetEta,*TopJetEfficiency_GenTopJetPt, *TopJetEfficiency_GenTopJetNPV,*TopJetEfficiency_GenTopJetEta_matchedTopJet,*TopJetEfficiency_GenTopJetPt_matchedTopJet, *TopJetEfficiency_GenTopJetNPV_matchedTopJet;

    //TopJet Purity
    TH1F *TopJetPurity_RecoTopJetEta,*TopJetPurity_RecoTopJetPt, *TopJetPurity_RecoTopJetNPV,*TopJetPurity_RecoTopJetEta_matchedTopJet,*TopJetPurity_RecoTopJetPt_matchedTopJet, *TopJetPurity_RecoTopJetNPV_matchedTopJet;

    //General
    TH1F *TopJetRecoPT,*TopJetGenPT;
    //AK8 jets without precut in n-tuples
    Event::Handle<vector<Jet>> h_myAK8jets;

  };

}
