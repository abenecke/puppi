#include "UHH2/Puppi/include/DYHists.h"
#include "UHH2/core/include/Event.h"
#include "UHH2/core/include/GenParticle.h"
#include "UHH2/core/include/LorentzVector.h"


#include <iostream>

using namespace std;
using namespace uhh2;
using namespace uhh2examples;

DYHists::DYHists(Context & ctx, const string & dirname): Hists(ctx, dirname){
  berror=(ctx.get("debug") == "true");
  ////////////////////////////////////          General Hist  ///////////////////////////////////////////
  MET = book<TH1F>("MET", "uncorrected MET",500,0,500);

  ////////////////////////////////////       Response Hist  ///////////////////////////////////////////
  response_ZP=book<TH2F>("response_ZP", "reponse as function of ZpT",200,0,200,100,0,2);
  response_NPV=book<TH2F>("response_NPV", "reponse as function of NVP",100,0,50,100,0,2);
  rms_ZP=book<TH2F>("rms_ZP", "rms_ZP",200,0,200,400,-100,100);
  rms_NPV=book<TH2F>("rms_NPV", "rms_NPV",100,0,50,400,-100,100);
  rms_uper_ZP=book<TH2F>("rms_uper_ZP", "rms_uper",200,0,200,200,0,100);
  rms_uper_NPV=book<TH2F>("rms_uper_NPV", "rms_uper",200,0,200,200,0,100);

}


void DYHists::fill(const Event & event){

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
 
   if(berror) std::cout<<"DYHists::Response hists"<<std::endl;
  /////////////////////////////////////    Response Hists  /////////////////////////////////////////////
   assert(event.muons); // if this fails, it probably means muons are not read in
   std::vector<Muon> *muons = event.muons;
 
    Muon muon_pos;
    Muon muon_neg;
   //find muons of the Z decay
   for(auto m:*muons){
     if(m.charge()==1){
       muon_pos=m;
       break;
     }
   }
   for(auto m:*muons){
     if(m.charge()==-1){
       muon_neg=m;
       break;
     }
   }
   //Pt of the reconstructed Z
   double Z_pt = (muon_pos.v4() + muon_neg.v4()).pt();

   //Pt of the recoiled jets
   LorentzVector jets_v4;
   for(auto j:*jets)    jets_v4 +=j.v4(); 
   
   //calculate the parallel component

   //unit vector
   double ZPx = (muon_pos.v4() + muon_neg.v4()).Px()/Z_pt;
   double ZPy = (muon_pos.v4() + muon_neg.v4()).Py()/Z_pt;
 

   if(berror) std::cout<<"DYHists:: unit vectors"<< "  ZPx "<<ZPx<<"  ZPy    "<< ZPy <<"  ZP  "<<Z_pt<<std::endl;
   if(berror)std::cout<<"upar2 " << ZPx * jets_v4.Px() + ZPy * jets_v4.Py()<<std::endl;
   double upar = ZPx * jets_v4.Px() + ZPy * jets_v4.Py();
   double uper= sqrt(jets_v4.pt()*jets_v4.pt() -upar * upar );
   if(berror) std::cout<<"DYHists::fill response"<<" -upar  " <<-upar<<" -upar/Z_pt  " <<-upar/Z_pt<<"  uper/Z_pt   "<<uper/Z_pt<<std::endl;


   response_ZP->Fill(Z_pt,-upar/Z_pt,weight);
   response_NPV->Fill(npvs,-upar/Z_pt,weight);
   rms_ZP->Fill(Z_pt,-upar-Z_pt,weight);
   rms_NPV->Fill(npvs,-upar-Z_pt,weight);
   rms_uper_ZP->Fill(Z_pt,uper,weight);
   rms_uper_NPV->Fill(npvs,uper,weight);

  if(berror) std::cout<<"DYHists::general hists"<<std::endl;
  /////////////////////////////////////    General Hists  /////////////////////////////////////////////

  MET->Fill(event.met->uncorr_pt(),weight);
}

DYHists::~DYHists(){}
