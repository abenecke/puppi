#include "UHH2/Puppi/include/PuppiJetHists.h"
#include "UHH2/core/include/Event.h"
#include "UHH2/core/include/GenParticle.h"
#include "UHH2/core/include/LorentzVector.h"


#include <iostream>

using namespace std;
using namespace uhh2;
using namespace uhh2examples;

PuppiJetHists::PuppiJetHists(Context & ctx, const string & dirname): Hists(ctx, dirname){
  berror=false;
  ////////////////////////////////////////////////////////////////       Jet PT Scale       /////////////////////////////////////////////////////////
  JetPtScale_Eta0to1p3 = book<TH2F>("JetPtScale_Eta0to1p3", "Jet p_{T} scale (0<eta<1p3)", 100, 0, 100,20,-1,1); 
  JetPtScale_Eta1p3to2 = book<TH2F>("JetPtScale_Eta1p3to2", "Jet p_{T} scale (1p3<eta<2)", 100, 0, 100,20,-1,1); 
  JetPtScale_Eta2to2p5 = book<TH2F>("JetPtScale_Eta2to2p5", "Jet p_{T} scale (2<eta<2p5)", 100, 0, 100,20,-1,1); 
  JetPtScale_Eta2p5to3 = book<TH2F>("JetPtScale_Eta2p5to3", "Jet p_{T} scale (2p5<eta<3)", 100, 0, 100,20,-1,1); 
  JetPtScale_Eta3to10 = book<TH2F>("JetPtScale_Eta3to10", "Jet p_{T} scale (3<eta<10)", 100, 0, 100,20,-1,1); 

  ////////////////////////////////////////////////////////////////       Jet Efficiency       /////////////////////////////////////////////////////////
  JetEfficiency_GenJetEta = book<TH1F>("JetEfficiency_GenJetEta", "Jet Efficiency GenJetEta", 100,-5,5); 
  JetEfficiency_GenJetEta_matchedjet = book<TH1F>("JetEfficiency_GenJetEta_matchedjet", "Jet Efficiency GenJetEta",100,-5,5); 
  JetEfficiency_GenJetPt = book<TH1F>("JetEfficiency_GenJetPt", "Jet Efficiency GenJetPt", 500,0,500); 
  JetEfficiency_GenJetPt_matchedjet = book<TH1F>("JetEfficiency_GenJetPt_matchedjet", "Jet Efficiency GenJetPt", 500,0,500); 
  JetEfficiency_GenJetNPV = book<TH1F>("JetEfficiency_GenJetNPV", "Jet Efficiency NPV",80,0,80); 
  JetEfficiency_GenJetNPV_matchedjet = book<TH1F>("JetEfficiency_GenJetNPV_matchedjet", "Jet Efficiency NPV",80,0,80 ); 

  // ////////////////////////////////////////////////////////////////       Jet Purity       /////////////////////////////////////////////////////////
  // JetPurity_GenJetEta = book<TH2F>("JetPurity_GenJetEta", "Jet Purity GenJetEta", 100, 0, 100,10,0.8,1); 
  // JetPurity_GenJetPt = book<TH2F>("JetPurity_GenJetPt", "Jet Purity GenJetPt", 100, 0, 100,10,0.9,1); 
  // JetPurity_GenJetNPV = book<TH2F>("JetPurity_GenJetNPV", "Jet Purity NPV", 100, 0, 100,10,0.9,1); 

}


void PuppiJetHists::fill(const Event & event){

  assert(event.met);
  assert(event.pvs);
  assert(event.jets);
  

  double weight = event.weight;
  if(berror) std::cout<<"weight  "<<weight<<std::endl;
 


  std::vector<Jet>* jets = event.jets;
  std::vector<GenParticle>* genparticles = event.genparticles;
  double npvs = event.pvs->size();

  if(berror)std::cout<<"Number of PV  "<<npvs<<std::endl;
  if(berror)std::cout<<"Number of Jets  "<<jets->size()<<std::endl;

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
      if(berror)   std::cout<<"Delta R Genparticle Jet  "<<deltaR_gen_jet<<std::endl;
      if(deltaR_gen_jet<0.09) genp_pt = genparticles->at(j).pt();
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
 

  ////////////////////////////////////////   Jet Efficiency   /////////////////////////////////////////
  double genp_eta_matched=0;
  double genp_pt_matched=0;


  for(unsigned int j=0;j<genparticles->size();j++){
    double genp_eta = genparticles->at(j).eta();
    genp_pt = genparticles->at(j).pt();

    JetEfficiency_GenJetEta->Fill(genp_eta,weight);
    JetEfficiency_GenJetPt->Fill(genp_pt,weight);
  }//over all genparticles

  for(unsigned int i=0;i<jets->size();i++){
    //do matching 
    for(unsigned int j=0;j<genparticles->size();j++){
      double deltaR_gen_jet = deltaR(genparticles->at(j),jets->at(i));
      if(deltaR_gen_jet<0.09){
	genp_eta_matched = genparticles->at(j).eta();
	genp_pt_matched = genparticles->at(j).pt();
      }
    }//for-loop over all genparticles
    JetEfficiency_GenJetEta_matchedjet->Fill(genp_eta_matched,weight);
    JetEfficiency_GenJetPt_matchedjet->Fill(genp_pt_matched,weight);

  }//for-loop over all jets

}

PuppiJetHists::~PuppiJetHists(){}
