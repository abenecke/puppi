#include "UHH2/Puppi/include/PaperHists.h"
#include "UHH2/core/include/Event.h"
#include "UHH2/core/include/GenParticle.h"
#include "UHH2/core/include/LorentzVector.h"


#include <iostream>

using namespace std;
using namespace uhh2;
using namespace uhh2examples;

PaperHists::PaperHists(Context & ctx, const string & dirname, const std::string & collection ): Hists(ctx, dirname){
  berror=(ctx.get("debug") == "true");
  berror=false;

  if(!collection.empty()){
    h_myParticles = ctx.get_handle<std::vector<PuppiParticle> >(collection);
  }
 
  ////////////////////////////////////////////////////////////////      Alpha      /////////////////////////////////////////////////////////
  Alpha = book<TH1F>("Alpha", "Alpha", 100, 0, 25); 
  AlphaMED = book<TH1F>("AlphaMED", "Alpha Median", 100, 0, 10); 
  AlphaRMS = book<TH1F>("AlphaRMS", "Alpha RMS", 100, -10, 10); 
  Weight = book<TH1F>("Weight", "Weight", 100, -1, 2); 

  ////////////////////////////////////////////////////////////////      Alpha      /////////////////////////////////////////////////////////
  heta =  book<TH1F>("eta", "eta", 100, -5, 5); 
  hpt =  book<TH1F>("pt", "pt", 1000, 0, 1000); 
 
  alphaMED_eta = book<TH2F>("alphaMED_eta", "Alpha MED as function of eta",100,-5,5,100,0,25);
  alphaRMS_eta = book<TH2F>("alphaRMS_eta", "Alpha RMS as function of eta",100,-5,5,100,0,25);



}


void PaperHists::fill(const Event & event){
  if(berror) std::cout<<"in PaperHists  "<<std::endl;
  assert(event.pvs);

  

  //  double weight = event.weight;
  double weight = 1;
  if(berror) std::cout<<"weight  "<<weight<<std::endl;

 
  //declare all needed particle collections
  vector<PuppiParticle> myParticles = event.get(h_myParticles);
 

 
  for(unsigned int i=0;i<myParticles.size();i++){
    double alpha = myParticles.at(i).alphas();
    double alphaMED = myParticles.at(i).alphasMed();
    double alphaRMS = myParticles.at(i).alphasRms();
    double eta = myParticles.at(i).eta();
    double pt = myParticles.at(i).pt();
    double puppi_weight=myParticles.at(i).puppiweight();

    //Fill histogramms 
    Alpha->Fill(alpha,weight);
    AlphaMED->Fill(alphaMED,weight);
    AlphaRMS->Fill(alphaRMS,weight);
    heta->Fill(eta,weight);
    hpt->Fill(pt,weight);
    alphaMED_eta->Fill(eta,alphaMED,weight);
    alphaRMS_eta->Fill(eta,alphaRMS,weight);
    Weight->Fill(puppi_weight,weight);
  }//end forloop myParticles


}



PaperHists::~PaperHists(){}
