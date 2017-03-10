#include <iostream>
#include <memory>

#include "UHH2/core/include/AnalysisModule.h"
#include "UHH2/core/include/Event.h"
#include "UHH2/common/include/CommonModules.h"
#include "UHH2/common/include/CleaningModules.h"
#include <UHH2/common/include/EventHists.h>
#include <UHH2/common/include/MuonHists.h>
#include <UHH2/common/include/ElectronHists.h>
#include <UHH2/common/include/JetHists.h>
#include "UHH2/common/include/NSelections.h"

#include "UHH2/common/include/PrintingModules.h"


#include "UHH2/Puppi/include/PuppiSelections.h"
#include "UHH2/Puppi/include/PuppiJetHists.h"
#include "UHH2/Puppi/include/PuppiTopJetHists.h"


using namespace std;
using namespace uhh2;

namespace uhh2examples {

  class PuppiModule: public AnalysisModule {
  public:
    
    explicit PuppiModule(Context & ctx);
    virtual bool process(Event & event) override;

  private:
    bool berror; 
    Event::Handle<vector<Jet>> h_myAK8jets;
    Event::Handle<vector<Jet>> h_myAK8jets_uncorrected;

    std::unique_ptr<AnalysisModule> printer;

    ///////////////////////////    Selections    /////////////////////////////////  

    std::unique_ptr<JetCleaner> jet_pt_30to40_sel;
    std::unique_ptr<JetCleaner> jet_pt_100to150_sel;

    std::unique_ptr<TopJetCleaner> topjet_pt_30to40_sel;
    std::unique_ptr<TopJetCleaner> topjet_pt_100to150_sel;

    ///////////////////////////    Hists    /////////////////////////////////  
    
    std::unique_ptr<uhh2::Hists> uncorrected_h_jet;
    std::unique_ptr<uhh2::Hists> uncorrected_h_topjet;

    //default histogramms
    std::unique_ptr<uhh2::Hists> input_h_jet;
    std::unique_ptr<uhh2::Hists>input_h_topjet;
    std::unique_ptr<uhh2::Hists>input_h_event;


    std::unique_ptr<PuppiJetHists> h_jet_input; 
    std::unique_ptr<PuppiTopJetHists> h_topjet_input;

    std::unique_ptr<PuppiJetHists> h_jet_pt_30to40; 
    std::unique_ptr<PuppiJetHists> h_jet_pt_100to150;
    std::unique_ptr<PuppiJetHists> h_jet_pt_25;

    std::unique_ptr<uhh2::Hists> pt_30to40_h_jet;
    std::unique_ptr<uhh2::Hists>pt_30to40_h_topjet;
    std::unique_ptr<uhh2::Hists>pt_30to40_h_event;

    std::unique_ptr<uhh2::Hists> pt_25_h_jet;
    std::unique_ptr<uhh2::Hists>pt_25_h_topjet;
    std::unique_ptr<uhh2::Hists>pt_25_h_event;

    std::unique_ptr<uhh2::Hists> pt_100to150_h_jet;
    std::unique_ptr<uhh2::Hists>pt_100to150_h_topjet;
    std::unique_ptr<uhh2::Hists>pt_100to150_h_event;


    std::unique_ptr<PuppiTopJetHists> h_topjet_pt_30to40; 
    std::unique_ptr<PuppiTopJetHists> h_topjet_pt_100to150; 
    std::unique_ptr<PuppiTopJetHists> h_topjet_pt_25; 
  };


  PuppiModule::PuppiModule(Context & ctx){
    berror=(ctx.get("debug") == "true");
    if(ctx.get("mode")=="Puppi")  h_myAK8jets = ctx.get_handle<vector<Jet>>("patJetsAK8PFPUPPI");
    else h_myAK8jets = ctx.get_handle<vector<Jet>>("patJetsAK8PFCHS");
    h_myAK8jets_uncorrected =ctx.declare_event_output< std::vector<Jet> > ("myAK8jets_uncorrected");
    printer.reset(new GenParticlesPrinter(ctx));

    ///////////////////////////    Selections    /////////////////////////////////  

    jet_pt_30to40_sel.reset(new JetCleaner(ctx,PtEtaCut( 30., 11,40.)));
    jet_pt_100to150_sel.reset(new JetCleaner(ctx,PtEtaCut( 100., 11,150)));

    topjet_pt_30to40_sel.reset(new TopJetCleaner(ctx,PtEtaCut( 30., 11,40.)));
    topjet_pt_100to150_sel.reset(new TopJetCleaner(ctx,PtEtaCut( 100., 11,150)));

    ///////////////////////////    Hists    /////////////////////////////////  

    uncorrected_h_jet.reset(new JetHists     (ctx, "uncorrected_Jets"));
    if(ctx.get("mode")=="Puppi")  uncorrected_h_topjet.reset(new JetHists (ctx, "uncorrected_TopJets",4,"patJetsAK8PFPUPPI"));
    else uncorrected_h_topjet.reset(new JetHists (ctx, "uncorrected_TopJets",4,"patJetsAK8PFCHS"));

    input_h_jet.reset(new JetHists     (ctx, "input_Jets"));
    input_h_topjet.reset(new JetHists (ctx, "input_TopJets",4,"myAK8jets_uncorrected"));
    input_h_event.reset(new EventHists (ctx, "input_Event"));

    pt_30to40_h_jet.reset(new JetHists     (ctx, "pt_30to40_Jets"));
    pt_30to40_h_topjet.reset(new JetHists (ctx, "pt_30to40_TopJets",4,"myAK8jets_uncorrected"));
    pt_30to40_h_event.reset(new EventHists (ctx, "pt_30to40_Event"));

    pt_25_h_jet.reset(new JetHists     (ctx, "pt_25_Jets"));
    pt_25_h_topjet.reset(new JetHists (ctx, "pt_25_TopJets",4,""));
    pt_25_h_event.reset(new EventHists (ctx, "pt_25_Event"));


    pt_100to150_h_jet.reset(new JetHists     (ctx, "pt_100to150_Jets"));
    pt_100to150_h_topjet.reset(new JetHists (ctx, "pt_100to150_TopJets",4,"myAK8jets_uncorrected"));
    pt_100to150_h_event.reset(new EventHists (ctx, "pt_100to150_Event"));
    
    h_jet_input.reset(new PuppiJetHists(ctx, "jet_input"));
    h_topjet_input.reset(new PuppiTopJetHists(ctx, "topjet_input"));

    h_jet_pt_30to40.reset(new PuppiJetHists(ctx, "jet_pt_30to40"));
    h_jet_pt_100to150.reset(new PuppiJetHists(ctx, "jet_pt_100to150"));
    h_jet_pt_25.reset(new PuppiJetHists(ctx, "jet_pt_25"));

    h_topjet_pt_30to40.reset(new PuppiTopJetHists(ctx, "topjet_pt_30to40"));
    h_topjet_pt_100to150.reset(new PuppiTopJetHists(ctx, "topjet_pt_100to150"));
    h_topjet_pt_25.reset(new PuppiTopJetHists(ctx, "topjet_pt_25"));
  }


  bool PuppiModule::process(Event & event) {
    if(berror) std::cout<<" ====================    New Event   ===================="<<std::endl;
    if(berror) printer->process(event);
    vector<Jet>  myAK8jets = event.get(h_myAK8jets);
   

    uncorrected_h_jet   ->fill(event);
    uncorrected_h_topjet ->fill(event);

    if(berror)  std::cout<<"-------- PuppiModul::Jec_factor_raw -------"<<std::endl;
    ///////////////////////////   Jets and topjets back correcting  ///////////////////////////////// 
    for (auto & jet:*event.jets)  jet.set_v4(jet.v4() * jet.JEC_factor_raw() );
    if(berror) std::cout<<"myAK8jets first jet mass  "<<myAK8jets.at(0).v4().M()<<std::endl;
    for (auto & jet:myAK8jets)   jet.set_v4(jet.v4() * jet.JEC_factor_raw() );
    if(berror) std::cout<<"after JEC raw corrected myAK8jets first jet mass  "<<myAK8jets.at(0).v4().M()<<std::endl;
    sort_by_pt<Jet>(*event.jets);
    event.set(h_myAK8jets_uncorrected,myAK8jets);

    input_h_jet   ->fill(event);
    input_h_event   ->fill(event);
    input_h_topjet ->fill(event);


    h_jet_input->fill(event);
    h_topjet_input->fill(event);

    if(berror)  std::cout<<"-------- PuppiModul::JetPTScale 30 to 40 -------"<<std::endl;
    ///////////////////////////    Jet PT Scale  30 to 40  ///////////////////////////////// 
    std::unique_ptr< std::vector<Jet> > uncleaned_jets (new std::vector<Jet> (*event.jets));
    jet_pt_30to40_sel->process(event);
    h_jet_pt_30to40->fill(event);
    pt_30to40_h_jet   ->fill(event);
    pt_30to40_h_event   ->fill(event);
   
 
    event.jets->clear();
    event.jets->reserve(uncleaned_jets->size());
    for(const auto & j : *uncleaned_jets) event.jets->push_back(j); 
    sort_by_pt<Jet>(*event.jets);

    if(berror)  std::cout<<"-------- PuppiModul::JetPTScale 100 to 150 -------"<<std::endl;
    ///////////////////////////    Jet PT Scale  100 to 150  ///////////////////////////////// 
    jet_pt_100to150_sel->process(event);
    h_jet_pt_100to150->fill(event);
    pt_100to150_h_jet   ->fill(event);
    pt_100to150_h_event   ->fill(event);

    event.jets->clear();
    event.jets->reserve(uncleaned_jets->size());
    for(const auto & j : *uncleaned_jets) event.jets->push_back(j); 
    sort_by_pt<Jet>(*event.jets);


    if(berror)  std::cout<<"-------- PuppiModul::TopJetPTScale 30 to 40 -------"<<std::endl;
    ///////////////////////////    TopJet PT Scale  30 to 40  ///////////////////////////////// 
    std::unique_ptr< std::vector<TopJet> > uncleaned_topjets (new std::vector<TopJet> (*event.topjets));
    topjet_pt_30to40_sel->process(event);
    h_topjet_pt_30to40->fill(event);
    pt_30to40_h_topjet ->fill(event);

    event.topjets->clear();
    event.topjets->reserve(uncleaned_topjets->size());
    for(const auto & j : *uncleaned_topjets) event.topjets->push_back(j); 
    sort_by_pt<TopJet>(*event.topjets);

    if(berror)  std::cout<<"-------- PuppiModul::TopJetPTScale 100 to 150 -------"<<std::endl;
    ///////////////////////////    TopJet PT Scale  100 to 150  ///////////////////////////////// 
    topjet_pt_100to150_sel->process(event);
    h_topjet_pt_100to150->fill(event); 
    pt_100to150_h_topjet ->fill(event);

    event.topjets->clear();
    event.topjets->reserve(uncleaned_topjets->size());
    for(const auto & j : *uncleaned_topjets) event.topjets->push_back(j); 
    sort_by_pt<TopJet>(*event.topjets);

    if(berror)  std::cout<<"-------- PuppiModul::Jet Efficiency and Purity -------"<<std::endl;
    ///////////////////////////  Jet Efficiency and Purity   ///////////////////////////////// 
    h_jet_pt_25->fill(event);
    pt_25_h_jet   ->fill(event);
    pt_25_h_event   ->fill(event);

    event.jets->clear();
    event.jets->reserve(uncleaned_jets->size());
    for(const auto & j : *uncleaned_jets) event.jets->push_back(j); 
    sort_by_pt<Jet>(*event.jets);

    if(berror)  std::cout<<"-------- PuppiModul::TopJet Efficiency and Purity -------"<<std::endl;
    ///////////////////////////  TopJet Efficiency and Purity   ///////////////////////////////// 
    h_topjet_pt_25->fill(event);
    pt_25_h_topjet   ->fill(event);

    event.jets->clear();
    event.jets->reserve(uncleaned_jets->size());
    for(const auto & j : *uncleaned_jets) event.jets->push_back(j); 
    sort_by_pt<Jet>(*event.jets);


    return true;
  }


  UHH2_REGISTER_ANALYSIS_MODULE(PuppiModule)

}
