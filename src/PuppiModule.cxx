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
    
    std::unique_ptr<AnalysisModule> printer;

    ///////////////////////////    Selections    /////////////////////////////////  

    std::unique_ptr<JetCleaner> jet_pt_30to40_sel;
    std::unique_ptr<JetCleaner> jet_pt_100to150_sel;

    std::unique_ptr<TopJetCleaner> topjet_pt_30to40_sel;
    std::unique_ptr<TopJetCleaner> topjet_pt_100to150_sel;

    ///////////////////////////    Hists    /////////////////////////////////  

    //default histogramms
    std::unique_ptr<uhh2::Hists> input_h_jet;
    std::unique_ptr<uhh2::Hists>input_h_topjet;
    std::unique_ptr<uhh2::Hists>input_h_event;


    std::unique_ptr<PuppiJetHists> h_jet_input; 
    std::unique_ptr<PuppiTopJetHists> h_topjet_input;

    std::unique_ptr<PuppiJetHists> h_jet_pt_30to40; 
    std::unique_ptr<PuppiJetHists> h_jet_pt_100to150;

    std::unique_ptr<PuppiTopJetHists> h_topjet_pt_30to40; 
    std::unique_ptr<PuppiTopJetHists> h_topjet_pt_100to150; 
  };


  PuppiModule::PuppiModule(Context & ctx){
    berror=false;

    printer.reset(new GenParticlesPrinter(ctx));

    ///////////////////////////    Selections    /////////////////////////////////  

    jet_pt_30to40_sel.reset(new JetCleaner(ctx,PtEtaCut( 30., 11,40.)));
    jet_pt_100to150_sel.reset(new JetCleaner(ctx,PtEtaCut( 100., 11,150)));

    topjet_pt_30to40_sel.reset(new TopJetCleaner(ctx,PtEtaCut( 30., 11,40.)));
    topjet_pt_100to150_sel.reset(new TopJetCleaner(ctx,PtEtaCut( 100., 11,150)));

    ///////////////////////////    Hists    /////////////////////////////////  

    input_h_jet.reset(new JetHists     (ctx, "input_Jets"));
    input_h_topjet.reset(new TopJetHists (ctx, "input_TopJets"));
    input_h_event.reset(new EventHists (ctx, "input_Event"));


    h_jet_input.reset(new PuppiJetHists(ctx, "jet_input"));
    h_topjet_input.reset(new PuppiTopJetHists(ctx, "topjet_input"));

    h_jet_pt_30to40.reset(new PuppiJetHists(ctx, "jet_pt_30to40"));
    h_jet_pt_100to150.reset(new PuppiJetHists(ctx, "jet_pt_100to150"));

    h_topjet_pt_30to40.reset(new PuppiTopJetHists(ctx, "topjet_pt_30to40"));
    h_topjet_pt_100to150.reset(new PuppiTopJetHists(ctx, "topjet_pt_100to150"));
  }


  bool PuppiModule::process(Event & event) {
    if(berror) std::cout<<" ====================    New Event   ===================="<<std::endl;
    if(berror) printer->process(event);

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
 
    event.jets->clear();
    event.jets->reserve(uncleaned_jets->size());
    for(const auto & j : *uncleaned_jets) event.jets->push_back(j); 
    sort_by_pt<Jet>(*event.jets);

    if(berror)  std::cout<<"-------- PuppiModul::JetPTScale 100 to 150 -------"<<std::endl;
    ///////////////////////////    Jet PT Scale  100 to 150  ///////////////////////////////// 
    jet_pt_100to150_sel->process(event);
    h_jet_pt_100to150->fill(event);
 
    event.jets->clear();
    event.jets->reserve(uncleaned_jets->size());
    for(const auto & j : *uncleaned_jets) event.jets->push_back(j); 
    sort_by_pt<Jet>(*event.jets);


    if(berror)  std::cout<<"-------- PuppiModul::TopJetPTScale 30 to 40 -------"<<std::endl;
    ///////////////////////////    TopJet PT Scale  30 to 40  ///////////////////////////////// 
    std::unique_ptr< std::vector<TopJet> > uncleaned_topjets (new std::vector<TopJet> (*event.topjets));
    topjet_pt_30to40_sel->process(event);
    h_topjet_pt_30to40->fill(event);
 
    event.topjets->clear();
    event.topjets->reserve(uncleaned_topjets->size());
    for(const auto & j : *uncleaned_topjets) event.topjets->push_back(j); 
    sort_by_pt<TopJet>(*event.topjets);

    if(berror)  std::cout<<"-------- PuppiModul::TopJetPTScale 100 to 150 -------"<<std::endl;
    ///////////////////////////    TopJet PT Scale  100 to 150  ///////////////////////////////// 
    topjet_pt_100to150_sel->process(event);
    h_topjet_pt_100to150->fill(event);
 
    event.topjets->clear();
    event.topjets->reserve(uncleaned_topjets->size());
    for(const auto & j : *uncleaned_topjets) event.topjets->push_back(j); 
    sort_by_pt<TopJet>(*event.topjets);


    return true;
  }


  UHH2_REGISTER_ANALYSIS_MODULE(PuppiModule)

}
