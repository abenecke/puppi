#include "UHH2/Puppi/include/PuppiJetHists.h"
#include "UHH2/core/include/Event.h"
#include "UHH2/core/include/GenParticle.h"
#include "UHH2/core/include/LorentzVector.h"


#include <iostream>

using namespace std;
using namespace uhh2;
using namespace uhh2examples;

PuppiJetHists::PuppiJetHists(Context & ctx, const string & dirname): Hists(ctx, dirname){
  berror=(ctx.get("debug") == "true");
  ////////////////////////////////////////////////////////////////       Jet PT Scale       /////////////////////////////////////////////////////////
  JetPtScale_Eta0to1p3 = book<TH2F>("JetPtScale_Eta0to1p3", "Jet p_{T} scale (0<eta<1p3)", 100, 0, 100,200,-1,1); 
  JetPtScale_Eta1p3to2 = book<TH2F>("JetPtScale_Eta1p3to2", "Jet p_{T} scale (1p3<eta<2)", 100, 0, 100,200,-1,1); 
  JetPtScale_Eta2to2p5 = book<TH2F>("JetPtScale_Eta2to2p5", "Jet p_{T} scale (2<eta<2p5)", 100, 0, 100,200,-1,1); 
  JetPtScale_Eta2p5to3 = book<TH2F>("JetPtScale_Eta2p5to3", "Jet p_{T} scale (2p5<eta<3)", 100, 0, 100,200,-1,1); 
  JetPtScale_Eta3to10 = book<TH2F>("JetPtScale_Eta3to10", "Jet p_{T} scale (3<eta<10)", 100, 0, 100,200,-1,1); 

  ////////////////////////////////////////////////////////////////       Jet Efficiency       /////////////////////////////////////////////////////////
  JetEfficiency_GenJetEta = book<TH1F>("JetEfficiency_GenJetEta", "Jet Efficiency GenJetEta", 100,-5,5); 
  JetEfficiency_GenJetEta_matchedjet = book<TH1F>("JetEfficiency_GenJetEta_matchedjet", "Jet Efficiency GenJetEta",100,-5,5); 
  JetEfficiency_GenJetPt = book<TH1F>("JetEfficiency_GenJetPt", "Jet Efficiency GenJetPt", 500,0,500); 
  JetEfficiency_GenJetPt_matchedjet = book<TH1F>("JetEfficiency_GenJetPt_matchedjet", "Jet Efficiency GenJetPt", 500,0,500); 
  JetEfficiency_GenJetNPV = book<TH1F>("JetEfficiency_GenJetNPV", "Jet Efficiency NPV",80,0,80); 
  JetEfficiency_GenJetNPV_matchedjet = book<TH1F>("JetEfficiency_GenJetNPV_matchedjet", "Jet Efficiency NPV",80,0,80 ); 

  // ////////////////////////////////////////////////////////////////       Jet Purity       /////////////////////////////////////////////////////////
  JetPurity_RecoJetEta = book<TH1F>("JetPurity_RecoJetEta", "Jet Purity RecoJetEta", 100,-5,5); 
  JetPurity_RecoJetEta_matchedjet = book<TH1F>("JetPurity_RecoJetEta_matchedjet", "Jet Purity RecoJetEta",100,-5,5); 
  JetPurity_RecoJetPt = book<TH1F>("JetPurity_RecoJetPt", "Jet Purity RecoJetPt", 500,0,500); 
  JetPurity_RecoJetPt_matchedjet = book<TH1F>("JetPurity_RecoJetPt_matchedjet", "Jet Purity RecoJetPt", 500,0,500); 
  JetPurity_RecoJetNPV = book<TH1F>("JetPurity_RecoJetNPV", "Jet Purity NPV",80,0,80); 
  JetPurity_RecoJetNPV_matchedjet = book<TH1F>("JetPurity_RecoJetNPV_matchedjet", "Jet Purity NPV",80,0,80 ); 

  /////////////////////////////////////////////////////////////     General Hists             //////////////////////////////////////////////////////////
  JetRecoPT= book <TH1F>("JetRecoPT", "Jet Reco PT",500,0,500);
  JetGenPT= book <TH1F>("JetGenPT", "Jet Gen PT",500,0,500);
  MET = book<TH1F>("MET", "uncorrected MET",500,0,500);

}


void PuppiJetHists::fill(const Event & event){

  assert(event.met);
  assert(event.pvs);
  assert(event.jets);
  

  //  double weight = event.weight;
  double weight = 1;
  if(berror) std::cout<<"weight  "<<weight<<std::endl;
 


  std::vector<Jet>* jets = event.jets;
  std::vector<Particle>* genparticles = event.genjets;
  double npvs = event.pvs->size();

  if(berror)std::cout<<"Number of PV  "<<npvs<<std::endl;
  if(berror)std::cout<<"Number of Jets  "<<jets->size()<<std::endl;
 if(berror)std::cout<<"Number of GenJets  "<<genparticles->size()<<std::endl;
  ////////////////////////////////////////   Jet pt scale    /////////////////////////////////////////
  double genp_pt=0;
  //for each jet in the event calculate eta and do matching to GenParticles

  for(unsigned int i=0;i<jets->size();i++){

    double jet_eta = jets->at(i).eta();
    double jet_pt = jets->at(i).pt();
    if(berror) std::cout<<"---------"<<"Jet "<<i<<" ----------"<<std::endl;
    if(berror)   std::cout<<"Eta Jet  "<<jet_eta<<std::endl;
    if(berror)   std::cout<<"PT Jet  "<<jet_pt<<std::endl;


    //do matching to calculate jet pt scale
    for(unsigned int j=0;j<genparticles->size();j++){
      double deltaR_gen_jet = deltaR(genparticles->at(j),jets->at(i));
      if(berror)   std::cout<<"Delta R Genparticle Jet "<<j<<"  "<<deltaR_gen_jet<<std::endl;
      if(deltaR_gen_jet<0.2) genp_pt = genparticles->at(j).pt();
    }//for-loop over all genparticles

    if(berror)  std::cout<<"Pt Genparticle  "<< genp_pt <<std::endl;

    double jet_pt_scale = (jet_pt - genp_pt)/genp_pt;
    if(0<= jet_eta && jet_eta <=1.3){
      JetPtScale_Eta0to1p3->Fill(npvs,jet_pt_scale, weight);
    }else if(1.3<= jet_eta && jet_eta <=2.0){
      JetPtScale_Eta1p3to2->Fill(npvs,jet_pt_scale, weight);
    }else if(2.0<= jet_eta && jet_eta <=2.5){
      JetPtScale_Eta2to2p5->Fill(npvs,jet_pt_scale, weight);
    }else if(2.5<= jet_eta && jet_eta <=3.0){
      JetPtScale_Eta2p5to3->Fill(npvs,jet_pt_scale, weight);
    }else if(3.0<= jet_eta){
      JetPtScale_Eta1p3to2->Fill(npvs,jet_pt_scale, weight);
    }

  }//for-loop over all jets
 
  if(berror) std::cout<<"PuppiJetHists::JetEfficiency"<<std::endl;
  ////////////////////////////////////////   Jet Efficiency   /////////////////////////////////////////
  double genp_eta_matched=0;
  double genp_pt_matched=0;
  //cleaning of the GenJetcollection to 25 GeV
  std::unique_ptr< std::vector<Particle> > genjets_pt25 (new std::vector<Particle> (*event.genjets));
  if(berror)std::cout<<"genjets_pt25 vorher  "<<genjets_pt25->size() <<std::endl;
  genjets_pt25->clear();
  genjets_pt25->reserve(event.genjets->size());
  if(berror)std::cout<<"event.genjets vorher  "<<event.genjets->size() <<std::endl;
  for(auto j:*event.genjets){
    genp_pt = j.pt();
    if(berror)std::cout<<"pt der genjets  "<<genp_pt<<std::endl;
    if(genp_pt>25)genjets_pt25->push_back(j);
  }

  if(berror) std::cout<<"genjets_pt25 hinterher  "<<genjets_pt25->size() <<std::endl;


  for(unsigned int j=0;j<genjets_pt25->size();j++){
    double genp_eta = genjets_pt25->at(j).eta();
    genp_pt = genjets_pt25->at(j).pt();

    JetEfficiency_GenJetEta->Fill(genp_eta,weight);
    JetEfficiency_GenJetPt->Fill(genp_pt,weight);
  }//over all genjets_pt25

  for(unsigned int i=0;i<jets->size();i++){
    double reco_pt = jets->at(i).pt();
    JetRecoPT->Fill(reco_pt,weight);
    //do matching 
    for(unsigned int j=0;j<genjets_pt25->size();j++){
      double deltaR_gen_jet = deltaR(genjets_pt25->at(j),jets->at(i));
      if(deltaR_gen_jet<0.2){
	genp_eta_matched = genjets_pt25->at(j).eta();
	genp_pt_matched = genjets_pt25->at(j).pt();
	JetEfficiency_GenJetEta_matchedjet->Fill(genp_eta_matched,weight);
	JetEfficiency_GenJetPt_matchedjet->Fill(genp_pt_matched,weight);
      }
    }//for-loop over all genjets_pt25
   

  }//for-loop over all jets


  if(berror) std::cout<<"PuppiJetHists::JetPurity"<<std::endl;
 ////////////////////////////////////////   Jet Purity   /////////////////////////////////////////
  double reco_eta_matched=0;
  double reco_pt_matched=0;

  //cleaning of the Jetcollection to 25 GeV
  std::unique_ptr< std::vector<Jet> > jets_pt25 (new std::vector<Jet> (*event.jets));
  jets_pt25->clear();
  jets_pt25->reserve(event.jets->size());
  for(auto j:*event.jets){
    double reco_pt = j.pt();
    if(reco_pt>25)jets_pt25->push_back(j);
  }

  for(unsigned int j=0;j<jets_pt25->size();j++){
    double reco_eta = jets_pt25->at(j).eta();
    double reco_pt = jets_pt25->at(j).pt();
    
    JetPurity_RecoJetEta->Fill(reco_eta,weight);
    JetPurity_RecoJetPt->Fill(reco_pt,weight);
  }//over all jets_pt25

  for(unsigned int i=0;i<jets_pt25->size();i++){
    //do matching 
    for(unsigned int j=0;j<genparticles->size();j++){
      genp_pt = genparticles->at(j).pt();
      JetGenPT->Fill(genp_pt,weight);
      double deltaR_gen_jet = deltaR(genparticles->at(j),jets_pt25->at(i));
      if(deltaR_gen_jet<0.2){
	reco_eta_matched = jets_pt25->at(i).eta();
	reco_pt_matched = jets_pt25->at(i).pt();
	JetPurity_RecoJetEta_matchedjet->Fill(reco_eta_matched,weight);
	JetPurity_RecoJetPt_matchedjet->Fill(reco_pt_matched,weight);
      }
    }//for-loop over all genparticles
   

  }//for-loop over all jets_pt25

  MET->Fill(event.met->uncorr_pt(),weight);
}

PuppiJetHists::~PuppiJetHists(){}
