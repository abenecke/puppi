#include <iostream>
#include <memory>

#include "UHH2/core/include/AnalysisModule.h"
#include "UHH2/core/include/Event.h"
#include "UHH2/common/include/CommonModules.h"
#include "UHH2/common/include/CleaningModules.h"
#include <UHH2/common/include/EventHists.h>
#include <UHH2/common/include/MuonHists.h>
#include <UHH2/common/include/ElectronHists.h>
#include <UHH2/common/include/MCWeight.h>
#include <UHH2/common/include/JetHists.h>
#include "UHH2/common/include/NSelections.h"
#include <UHH2/common/include/LumiSelection.h>

#include "UHH2/common/include/PrintingModules.h"
#include "UHH2/Puppi/include/PaperHists.h"
#include "UHH2/Puppi/include/PuppiSelections.h"

#include "UHH2/common/include/EventVariables.h"
#include "UHH2/common/include/PrimaryLepton.h"

using namespace std;
using namespace uhh2;

namespace uhh2examples {

  class PaperModule: public AnalysisModule {
  public:
    
    explicit PaperModule(Context & ctx);
    virtual bool process(Event & event) override;

  private:
    bool berror; 
   
    //   std::unique_ptr<AnalysisModule> printer;
    std::unique_ptr<uhh2::Selection> ht_sel; //Ht,jets >1000
    std::unique_ptr<uhh2::Selection> lumi_sel;
    std::unique_ptr<uhh2::AnalysisModule> pileup_SF;

    //Defining new Collections
    Event::Handle<vector<PuppiParticle>> h_myParticles;
    Event::Handle<vector<PuppiParticle>> h_p_charged_pu;
    Event::Handle<vector<PuppiParticle>> h_p_charged_pv;
    Event::Handle<vector<PuppiParticle>> h_p_not_charged;
    Event::Handle<vector<PuppiParticle>> h_p_not_charged_pv;
    Event::Handle<vector<PuppiParticle>> h_p_not_charged_pu;
    Event::Handle<vector<PuppiParticle>> h_p_not_charged_forward;
    Event::Handle<vector<PuppiParticle>> h_p_not_charged_central;
    ///////////////////////////    Selections    /////////////////////////////////  

    std::vector<std::unique_ptr<AnalysisModule>> htcalc;

    ///////////////////////////    Hists    /////////////////////////////////  
    std::unique_ptr<uhh2::Hists> alpha_p_charged_pu;
    std::unique_ptr<uhh2::Hists> alpha_p_charged_pv;
    std::unique_ptr<uhh2::Hists> alpha_p_not_charged;
    std::unique_ptr<uhh2::Hists> alpha_p_not_charged_pu;
    std::unique_ptr<uhh2::Hists> alpha_p_not_charged_pv;
    std::unique_ptr<uhh2::Hists> alpha_p_not_charged_forward;
    std::unique_ptr<uhh2::Hists> alpha_p_not_charged_central;
    std::unique_ptr<uhh2::Hists> alpha_p;

    std::unique_ptr<uhh2::Hists> h_jet;
    std::unique_ptr<uhh2::Hists> h_event;

    bool isMC;
  };


  PaperModule::PaperModule(Context & ctx){
    berror=(ctx.get("debug") == "true");
  
    //  printer.reset(new GenParticlesPrinter(ctx));

    ht_sel.reset(new HtSelection(1000,-1));

    isMC = (ctx.get("dataset_type") == "MC");
    if(!isMC)lumi_sel.reset(new LumiSelection(ctx));
    else   pileup_SF.reset(new MCPileupReweight(ctx)); 

    //Defining new Collections
    h_myParticles = ctx.get_handle<vector<PuppiParticle>>("packedPFCandidates");
    h_p_charged_pu=ctx.declare_event_output< std::vector<PuppiParticle> > ("p_charged_pu");
    h_p_charged_pv=ctx.declare_event_output< std::vector<PuppiParticle> > ("p_charged_pv");
    h_p_not_charged=ctx.declare_event_output< std::vector<PuppiParticle> > ("p_not_charged");
    h_p_not_charged_pv=ctx.declare_event_output< std::vector<PuppiParticle> > ("p_not_charged_pv");
    h_p_not_charged_pu=ctx.declare_event_output< std::vector<PuppiParticle> > ("p_not_charged_pu");

    h_p_not_charged_forward=ctx.declare_event_output< std::vector<PuppiParticle> > ("p_not_charged_forward");
    h_p_not_charged_central=ctx.declare_event_output< std::vector<PuppiParticle> > ("p_not_charged_central");
   
    
    ///////////////////////////    Selections    /////////////////////////////////  
    //calculator
    htcalc.push_back(std::unique_ptr<AnalysisModule>(new HTCalculator(ctx)));
    htcalc.push_back(std::unique_ptr<AnalysisModule>(new PrimaryLepton(ctx)));
    htcalc.push_back(std::unique_ptr<AnalysisModule>(new HTlepCalculator(ctx)));
  

    ///////////////////////////    Hists    /////////////////////////////////  
    alpha_p_charged_pu.reset(new PaperHists(ctx, "alpha_p_charged_pu", "p_charged_pu"));
    alpha_p_charged_pv.reset(new PaperHists(ctx, "alpha_p_charged_pv", "p_charged_pv"));
    alpha_p_not_charged.reset(new PaperHists(ctx, "alpha_p_not_charged", "p_not_charged"));
    alpha_p_not_charged_pv.reset(new PaperHists(ctx, "alpha_p_not_charged_pv", "p_not_charged_pv"));
    alpha_p_not_charged_pu.reset(new PaperHists(ctx, "alpha_p_not_charged_pu", "p_not_charged_pu"));
    alpha_p_not_charged_forward.reset(new PaperHists(ctx, "alpha_p_not_charged_forward", "p_not_charged_forward"));
    alpha_p_not_charged_central.reset(new PaperHists(ctx, "alpha_p_not_charged_central", "p_not_charged_central"));
    alpha_p.reset(new PaperHists(ctx, "alpha_p", "packedPFCandidates"));
   
    h_jet.reset(new JetHists(ctx, "h_jets"));
    h_event.reset(new EventHists(ctx, "h_event"));
  }


  bool PaperModule::process(Event & event) {
    if(berror) std::cout<<" ====================    New Event   ===================="<<std::endl;
    //   if(berror) printer->process(event);
 
    if(berror) std::cout<<"PaperModule::Defining new Collections   "<<std::endl;
    ///////////////////////////    new Collections    /////////////////////////////////  
    // //x,y,z componet od the PV
    // double pvx = event.pvs->at(0).x();
    // double pvy = event.pvs->at(0).y();
    // double pvz = event.pvs->at(0).z();
    // if(berror)std::cout<<"PV  pvx  "<<pvx <<"  pvy  "<<pvy<<"  pvz  "<<pvz<<std::endl;
    

    for (auto & mod : htcalc) {
      mod->process(event);
    }

    if(event.isRealData && !lumi_sel->passes(event)) return false;
    if(!event.isRealData){ pileup_SF->process(event);}
    uhh2::Event::TriggerIndex ti_HT;
    ti_HT=event.get_trigger_index("HLT_PFHT900_v*");
    bool HT_trigger = event.passes_trigger(ti_HT);
    if(!HT_trigger) return false;

    if(berror) std::cout<<"PaperModule:: ht selection   "<<std::endl;
    bool pass_ht = ht_sel->passes(event);
    if(!pass_ht)return false;
    //  std::cout<<"Durch HT Selection"<<std::endl;
    //declare all needed particle collections
    vector<PuppiParticle> myParticles = event.get(h_myParticles);
    vector<PuppiParticle> p_charged_pu;
    vector<PuppiParticle> p_charged_pv; 
    vector<PuppiParticle> p_not_charged;
    vector<PuppiParticle> p_not_charged_pu;
    vector<PuppiParticle> p_not_charged_pv;
    vector<PuppiParticle> p_not_charged_forward;
    vector<PuppiParticle> p_not_charged_central;
    if(berror) std::cout<<"PaperModule:: deviding particles   "<<std::endl;
    //Divide myParticles in charged, not charged and from PV and from PU
    for(unsigned int i=0; i<myParticles.size();i++){
      //check eta requirement
      double eta =  myParticles.at(i).eta();
      double pt = myParticles.at(i).pt();
      if(pt > 1){

    	//x,y,z componet od the Vertex
    	double frompv = myParticles.at(i).fromPV();
    	double fdzcut = 0.3;//myParticles.at(i).fdzcut();
    	double dz =myParticles.at(i).dz();
      
    	if(myParticles.at(i).charge()==0){
    	  p_not_charged.push_back(myParticles.at(i));
	  if(myParticles.at(i).puppiweight()<0.5)  p_not_charged_pu.push_back(myParticles.at(i));
	  else  p_not_charged_pv.push_back(myParticles.at(i));
	  if(abs(myParticles.at(i).eta())<2.5) p_not_charged_central.push_back(myParticles.at(i));
	  else p_not_charged_forward.push_back(myParticles.at(i));
    	}else{
    	  if(frompv==3){
    	    p_charged_pv.push_back(myParticles.at(i));
    	  }else if((frompv>0)&&(std::abs(dz) < fdzcut)){
    	    p_charged_pv.push_back(myParticles.at(i));
    	  }else if((frompv>0)&&(std::abs(dz) > fdzcut)){
    	    p_charged_pu.push_back(myParticles.at(i));
    	  }
    	}//end divided into charge and non charged
      }//end eta requirement
    }//end for loop myParticles
   
    //Set new Collections
    event.set(h_p_charged_pu, p_charged_pu);
    event.set(h_p_charged_pv, p_charged_pv);
    event.set(h_p_not_charged, p_not_charged);
    event.set(h_p_not_charged_pu, p_not_charged_pu);
    event.set(h_p_not_charged_pv, p_not_charged_pv);
    event.set(h_p_not_charged_central, p_not_charged_central);
    event.set(h_p_not_charged_forward, p_not_charged_forward);

    if(berror) std::cout<<"PaperModule::Filling ALphahists   "<<std::endl;
    ///////////////////////////    Hists    /////////////////////////////////  
    alpha_p_charged_pu->fill(event);
    alpha_p_charged_pv->fill(event);
    alpha_p_not_charged->fill(event);
    alpha_p_not_charged_pu->fill(event);
    alpha_p_not_charged_pv->fill(event);
    alpha_p_not_charged_central->fill(event);
    alpha_p_not_charged_forward->fill(event);
    alpha_p->fill(event);
    h_jet->fill(event);
    h_event->fill(event);
    return true;
  }


  UHH2_REGISTER_ANALYSIS_MODULE(PaperModule)

}
