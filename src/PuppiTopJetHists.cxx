#include "UHH2/Puppi/include/PuppiTopJetHists.h"
#include "UHH2/core/include/Event.h"
#include "UHH2/core/include/GenTopJet.h"

#include <iostream>

using namespace std;
using namespace uhh2;
using namespace uhh2examples;

PuppiTopJetHists::PuppiTopJetHists(Context & ctx, const string & dirname): Hists(ctx, dirname){
  berror=(ctx.get("debug") == "true");
  // berror=false;
  ////////////////////////////////////////////////////////////////       TopJet PT Scale       /////////////////////////////////////////////////////////
  TopJetPtScale_Eta0to1p3 = book<TH2F>("TopJetPtScale_Eta0to1p3", "TopJet p_{T} scale (0<eta<1p3)", 100, 0, 100,20,-1,1); 
  TopJetPtScale_Eta1p3to2 = book<TH2F>("TopJetPtScale_Eta1p3to2", "TopJet p_{T} scale (1p3<eta<2)", 100, 0, 100,20,-1,1); 
  TopJetPtScale_Eta2to2p5 = book<TH2F>("TopJetPtScale_Eta2to2p5", "TopJet p_{T} scale (2<eta<2p5)", 100, 0, 100,20,-1,1); 
  TopJetPtScale_Eta2p5to3 = book<TH2F>("TopJetPtScale_Eta2p5to3", "TopJet p_{T} scale (2p5<eta<3)", 100, 0, 100,20,-1,1); 
  TopJetPtScale_Eta3to10 = book<TH2F>("TopJetPtScale_Eta3to10", "TopJet p_{T} scale (3<eta<10)", 100, 0, 100,20,-1,1); 


  ////////////////////////////////////////////////////////////////       TopJet MASS Scale       /////////////////////////////////////////////////////////
  TopJetMassScale_Eta0to1p3 = book<TH2F>("TopJetMassScale_Eta0to1p3", "TopJet mass scale (0<eta<1p3)", 100, 0, 100,80,-20,20); 
  TopJetMassScale_Eta1p3to2 = book<TH2F>("TopJetMassScale_Eta1p3to2", "TopJet mass scale (1p3<eta<2)", 100, 0, 100,80,-20,20); 
  TopJetMassScale_Eta2to2p5 = book<TH2F>("TopJetMassScale_Eta2to2p5", "TopJet mass scale (2<eta<2p5)", 100, 0, 100,80,-20,20); 
  TopJetMassScale_Eta2p5to3 = book<TH2F>("TopJetMassScale_Eta2p5to3", "TopJet mass scale (2p5<eta<3)", 100, 0, 100,80,-20,20); 
  TopJetMassScale_Eta3to10 = book<TH2F>("TopJetMassScale_Eta3to10", "TopJet mass scale (3<eta<10)", 100, 0, 100,80,-20,20); 

  ////////////////////////////////////////////////////////////////       TopJet MASS Scale       /////////////////////////////////////////////////////////
  TopJetMassScale_GEV_Eta0to1p3 = book<TH2F>("TopJetMassScale_GEV_Eta0to1p3", "TopJet mass scale (0<eta<1p3)", 100, 0, 100,80,-20,20); 
  TopJetMassScale_GEV_Eta1p3to2 = book<TH2F>("TopJetMassScale_GEV_Eta1p3to2", "TopJet mass scale (1p3<eta<2)", 100, 0, 100,80,-20,20); 
  TopJetMassScale_GEV_Eta2to2p5 = book<TH2F>("TopJetMassScale_GEV_Eta2to2p5", "TopJet mass scale (2<eta<2p5)", 100, 0, 100,80,-20,20); 
  TopJetMassScale_GEV_Eta2p5to3 = book<TH2F>("TopJetMassScale_GEV_Eta2p5to3", "TopJet mass scale (2p5<eta<3)", 100, 0, 100,80,-20,20); 
  TopJetMassScale_GEV_Eta3to10 = book<TH2F>("TopJetMassScale_GEV_Eta3to10", "TopJet mass scale (3<eta<10)", 100, 0, 100,80,-20,20); 

  ////////////////////////////////////////////////////////////////       TopJet Efficiency       /////////////////////////////////////////////////////////
  TopJetEfficiency_GenTopJetEta = book<TH1F>("TopJetEfficiency_GenTopJetEta", "TopJet Efficiency GenTopJetEta", 100,-5,5); 
  TopJetEfficiency_GenTopJetEta_matchedTopJet = book<TH1F>("TopJetEfficiency_GenTopJetEta_matchedTopJet", "TopJet Efficiency GenTopJetEta",100,-5,5); 
  TopJetEfficiency_GenTopJetPt = book<TH1F>("TopJetEfficiency_GenTopJetPt", "TopJet Efficiency GenTopJetPt", 500,0,500); 
  TopJetEfficiency_GenTopJetPt_matchedTopJet = book<TH1F>("TopJetEfficiency_GenTopJetPt_matchedTopJet", "TopJet Efficiency GenTopJetPt", 500,0,500); 
  TopJetEfficiency_GenTopJetNPV = book<TH1F>("TopJetEfficiency_GenTopJetNPV", "TopJet Efficiency NPV",80,0,80); 
  TopJetEfficiency_GenTopJetNPV_matchedTopJet = book<TH1F>("TopJetEfficiency_GenTopJetNPV_matchedTopJet", "TopJet Efficiency NPV",80,0,80 ); 

  ////////////////////////////////////////////////////////////////       TopJet Purity       /////////////////////////////////////////////////////////
  TopJetPurity_RecoTopJetEta = book<TH1F>("TopJetPurity_RecoTopJetEta", "TopJet Purity RecoTopJetEta", 100,-5,5); 
  TopJetPurity_RecoTopJetEta_matchedTopJet = book<TH1F>("TopJetPurity_RecoTopJetEta_matchedTopJet", "TopJet Purity RecoTopJetEta",100,-5,5); 
  TopJetPurity_RecoTopJetPt = book<TH1F>("TopJetPurity_RecoTopJetPt", "TopJet Purity RecoTopJetPt", 500,0,500); 
  TopJetPurity_RecoTopJetPt_matchedTopJet = book<TH1F>("TopJetPurity_RecoTopJetPt_matchedTopJet", "TopJet Purity RecoTopJetPt", 500,0,500); 
  TopJetPurity_RecoTopJetNPV = book<TH1F>("TopJetPurity_RecoTopJetNPV", "TopJet Purity NPV",80,0,80); 
  TopJetPurity_RecoTopJetNPV_matchedTopJet = book<TH1F>("TopJetPurity_RecoTopJetNPV_matchedTopJet", "TopJet Purity NPV",80,0,80 ); 

  /////////////////////////////////////////////////////////////     General Hists             //////////////////////////////////////////////////////////
  TopJetRecoPT= book <TH1F>("TopJetRecoPT", "Jet Reco PT",500,0,500);
  TopJetGenPT= book <TH1F>("TopJetGenPT", "Jet Gen PT",500,0,500);
  

  //handle on AK8 jets without precuts in n-tuples
  h_myAK8jets = ctx.get_handle<vector<Jet>>("myAK8jets_uncorrected");

}


void PuppiTopJetHists::fill(const Event & event){

  assert(event.met);
  assert(event.pvs);
  assert(event.jets);
  

  double weight =1;
  if(berror) std::cout<<"weight  "<<weight<<std::endl;


  std::vector<Jet> topjets = event.get(h_myAK8jets);
  std::vector<GenTopJet>* genparticles = event.gentopjets;
  double npvs = event.pvs->size();

  // if(berror) std::cout<<"new jet collection myAK8jets_uncorrected first jet mass  "<<topjets.at(0).v4().mass()<<std::endl;
  if(berror) if(topjets.size())std::cout<<"new jet collection myAK8jets_uncorrected first jet mass  "<<topjets.at(0).v4().mass()<<std::endl;
  if(berror)std::cout<<"Number of PV  "<<npvs<<std::endl;
  if(berror)std::cout<<"Number of Topjets  "<<topjets.size()<<std::endl;
  if(berror)std::cout<<"Number of GenTopjets  "<<genparticles->size()<<std::endl;

  ////////////////////////////////////////   TopJet pt scale    /////////////////////////////////////////
  double genp_pt=0;
  //for each jet in the event calculate eta and do matching to GenParticles
  for(unsigned int i=0;i<topjets.size();i++){

    double topjet_eta = topjets.at(i).eta();
    double topjet_pt = topjets.at(i).pt();
    if(berror) std::cout<<"---------"<<"TopJet "<<i<<" ----------"<<std::endl;
    if(berror)   std::cout<<"Eta TopJet  "<<topjet_eta<<std::endl;
    if(berror)   std::cout<<"PT TopJet  "<<topjet_pt<<std::endl;

    
   
    //do matching to calculate topjet pt scale
    for(unsigned int j=0;j<genparticles->size();j++){
    double  deltaR_gen_topjet = deltaR(genparticles->at(j),topjets.at(i));
      // if(berror)   std::cout<<"Delta R Genparticle TopJet  "<<deltaR_gen_topjet<<std::endl;
      //  std::cout<<j<<" "<<genp_pt<<std::endl;
      if(deltaR_gen_topjet<0.4) genp_pt = genparticles->at(j).pt();
    }//for-loop over all genparticles

    if(berror)  std::cout<<"Pt Genparticle  "<< genp_pt <<std::endl;
    
    double topjet_pt_scale = (topjet_pt - genp_pt)/genp_pt;
    if(0<= topjet_eta && topjet_eta <=1.3){
      TopJetPtScale_Eta0to1p3->Fill(npvs,topjet_pt_scale, weight);
    }else if(1.3<= topjet_eta && topjet_eta <=2.0){
      TopJetPtScale_Eta1p3to2->Fill(npvs,topjet_pt_scale, weight);
    }else if(2.0<= topjet_eta && topjet_eta <=2.5){
      TopJetPtScale_Eta2to2p5->Fill(npvs,topjet_pt_scale, weight);
    }else if(2.5<= topjet_eta && topjet_eta <=3.0){
      TopJetPtScale_Eta2p5to3->Fill(npvs,topjet_pt_scale, weight);
    }else if(3.0<= topjet_eta){
      TopJetPtScale_Eta1p3to2->Fill(npvs,topjet_pt_scale, weight);
    }

  }//for-loop over all topjets
 

////////////////////////////////////////   TopJet mass scale    /////////////////////////////////////////
  double genp_mass=0;
  //for each jet in the event calculate eta and do matching to GenParticles

  for(unsigned int i=0;i<topjets.size();i++){

    double topjet_eta = topjets.at(i).eta();
    double topjet_mass = topjets.at(i).v4().M();
    if(berror) std::cout<<"---------"<<"TopJet "<<i<<" ----------"<<std::endl;
    if(berror)   std::cout<<"Eta TopJet  "<<topjet_eta<<std::endl;
    if(berror)   std::cout<<"PT TopJet  "<<topjet_mass<<std::endl;
  

    //do matching to calculate topjet mass scale
    for(unsigned int j=0;j<genparticles->size();j++){
      double deltaR_gen_topjet = deltaR(genparticles->at(j),topjets.at(i));
      // if(berror)   std::cout<<"Delta R Genparticle TopJet  "<<deltaR_gen_topjet<<std::endl;
      if(deltaR_gen_topjet<0.4){
	genp_mass = genparticles->at(j).v4().M();
	if(berror)	std::cout<<"mass gen  "<<genp_mass <<std::endl;
      }
    }//for-loop over all genparticles

    if(berror)  std::cout<<"Mass Genparticle  "<< genp_mass <<std::endl;

    double topjet_mass_scale = (topjet_mass - genp_mass)/genp_mass;
    if(0<= topjet_eta && topjet_eta <=1.3){
      TopJetMassScale_Eta0to1p3->Fill(npvs,topjet_mass_scale, weight);
    }else if(1.3<= topjet_eta && topjet_eta <=2.0){
      TopJetMassScale_Eta1p3to2->Fill(npvs,topjet_mass_scale, weight);
    }else if(2.0<= topjet_eta && topjet_eta <=2.5){
      TopJetMassScale_Eta2to2p5->Fill(npvs,topjet_mass_scale, weight);
    }else if(2.5<= topjet_eta && topjet_eta <=3.0){
      TopJetMassScale_Eta2p5to3->Fill(npvs,topjet_mass_scale, weight);
    }else if(3.0<= topjet_eta){
      TopJetMassScale_Eta1p3to2->Fill(npvs,topjet_mass_scale, weight);
    }

  }//for-loop over all topjets
 
////////////////////////////////////////   TopJet mass scale GEV   /////////////////////////////////////////
  genp_mass=0;
  //for each jet in the event calculate eta and do matching to GenParticles

  for(unsigned int i=0;i<topjets.size();i++){

    double topjet_eta = topjets.at(i).eta();
    double topjet_mass = topjets.at(i).v4().M();
    if(berror) std::cout<<"---------"<<"TopJet "<<i<<" ----------"<<std::endl;
    if(berror)   std::cout<<"Eta TopJet  "<<topjet_eta<<std::endl;
    if(berror)   std::cout<<"PT TopJet  "<<topjet_mass<<std::endl;
  

    //do matching to calculate topjet mass scale
    for(unsigned int j=0;j<genparticles->size();j++){
      double deltaR_gen_topjet = deltaR(genparticles->at(j),topjets.at(i));
      if(berror)   std::cout<<"Delta R Genparticle TopJet  "<<deltaR_gen_topjet<<std::endl;
      if(deltaR_gen_topjet<0.4){
	genp_mass = genparticles->at(j).v4().M();
	if(berror)	std::cout<<"mass gen  "<<genp_mass <<std::endl;
      }
    }//for-loop over all genparticles

    if(berror)  std::cout<<"Mass Genparticle  "<< genp_mass <<std::endl;

    double topjet_mass_scale_GEV = (topjet_mass - genp_mass);
    if(0<= topjet_eta && topjet_eta <=1.3){
      TopJetMassScale_GEV_Eta0to1p3->Fill(npvs,topjet_mass_scale_GEV, weight);
    }else if(1.3<= topjet_eta && topjet_eta <=2.0){
      TopJetMassScale_GEV_Eta1p3to2->Fill(npvs,topjet_mass_scale_GEV, weight);
    }else if(2.0<= topjet_eta && topjet_eta <=2.5){
      TopJetMassScale_GEV_Eta2to2p5->Fill(npvs,topjet_mass_scale_GEV, weight);
    }else if(2.5<= topjet_eta && topjet_eta <=3.0){
      TopJetMassScale_GEV_Eta2p5to3->Fill(npvs,topjet_mass_scale_GEV, weight);
    }else if(3.0<= topjet_eta){
      TopJetMassScale_GEV_Eta1p3to2->Fill(npvs,topjet_mass_scale_GEV, weight);
    }

  }//for-loop over all topjets
 
 ////////////////////////////////////////   TopJet Efficiency   /////////////////////////////////////////
  double genp_eta_matched=0;
  double genp_pt_matched=0;

  //cleaning of the GenJetcollection to 25 GeV
  std::unique_ptr< std::vector<GenTopJet> > genjets_pt25 (new std::vector<GenTopJet> (*event.gentopjets));
  if(berror)std::cout<<"genjets_pt25 vorher  "<<genjets_pt25->size() <<std::endl;
  genjets_pt25->clear();
  genjets_pt25->reserve(event.gentopjets->size());
  if(berror)std::cout<<"event.genjets vorher  "<<event.gentopjets->size() <<std::endl;
  for(auto j:*event.gentopjets){
    genp_pt = j.pt();
    if(berror)std::cout<<"pt der genjets  "<<genp_pt<<std::endl;
    if(genp_pt>25)genjets_pt25->push_back(j);
  }

  if(berror) std::cout<<"genjets_pt25 hinterher  "<<genjets_pt25->size() <<std::endl;

  for(unsigned int j=0;j<genjets_pt25->size();j++){
    double genp_eta = genjets_pt25->at(j).eta();
    genp_pt = genjets_pt25->at(j).pt();

    TopJetEfficiency_GenTopJetEta->Fill(genp_eta,weight);
    TopJetEfficiency_GenTopJetPt->Fill(genp_pt,weight);
  }//over all genjets_pt25

  for(unsigned int i=0;i<topjets.size();i++){
    double reco_pt = topjets.at(i).pt();
    TopJetRecoPT->Fill(reco_pt,weight);
    //do matching 
    for(unsigned int j=0;j<genjets_pt25->size();j++){
      double deltaR_gen_TopJet = deltaR(genjets_pt25->at(j),topjets.at(i));
      if(deltaR_gen_TopJet<0.4){
	genp_eta_matched = genjets_pt25->at(j).eta();
	genp_pt_matched = genjets_pt25->at(j).pt();
	TopJetEfficiency_GenTopJetEta_matchedTopJet->Fill(genp_eta_matched,weight);
	TopJetEfficiency_GenTopJetPt_matchedTopJet->Fill(genp_pt_matched,weight);
      }
    }//for-loop over all genjets_pt25
   

  }//for-loop over all TopJets

 ////////////////////////////////////////   TopJet Purity   /////////////////////////////////////////
  double reco_eta_matched=0;
  double reco_pt_matched=0;

  //cleaning of the Jetcollection to 25 GeV
  std::unique_ptr< std::vector<Jet> > jets_pt25 (new std::vector<Jet> (topjets));
  jets_pt25->clear();
  jets_pt25->reserve(event.jets->size());
  for(auto j:topjets){
    double reco_pt = j.pt();
    if(reco_pt>25)jets_pt25->push_back(j);
  }


  for(unsigned int j=0;j<jets_pt25->size();j++){
    double reco_eta = jets_pt25->at(j).eta();
    double reco_pt = jets_pt25->at(j).pt();

    TopJetPurity_RecoTopJetEta->Fill(reco_eta,weight);
    TopJetPurity_RecoTopJetPt->Fill(reco_pt,weight);
  }//over all genparticles

  for(unsigned int i=0;i<jets_pt25->size();i++){
    //do matching 
    for(unsigned int j=0;j<genparticles->size();j++){
      genp_pt = genparticles->at(j).pt();
      TopJetGenPT->Fill(genp_pt,weight);
      double deltaR_gen_TopJet = deltaR(genparticles->at(j),jets_pt25->at(i));
      if(deltaR_gen_TopJet<0.4){
	reco_eta_matched = jets_pt25->at(i).eta();
	reco_pt_matched = jets_pt25->at(i).pt();
	TopJetPurity_RecoTopJetEta_matchedTopJet->Fill(reco_eta_matched,weight);
	TopJetPurity_RecoTopJetPt_matchedTopJet->Fill(reco_pt_matched,weight);
      }
    }//for-loop over all genparticles
    

  }//for-loop over all Jets_Pt25


 
}

PuppiTopJetHists::~PuppiTopJetHists(){}
