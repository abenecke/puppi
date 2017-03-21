#include <iostream>
#include <memory>

#include "UHH2/core/include/AnalysisModule.h"
#include "UHH2/core/include/Event.h"
#include "UHH2/common/include/CommonModules.h"
#include "UHH2/common/include/CleaningModules.h"
#include <UHH2/common/include/MuonIds.h>
#include <UHH2/common/include/ElectronIds.h>
#include <UHH2/common/include/EventHists.h>
#include <UHH2/common/include/MuonHists.h>
#include <UHH2/common/include/ElectronHists.h>
#include <UHH2/common/include/JetHists.h>
#include "UHH2/common/include/NSelections.h"

#include "UHH2/common/include/PrintingModules.h"


#include "UHH2/Puppi/include/PuppiSelections.h"
#include "UHH2/Puppi/include/PuppiJetHists.h"
#include "UHH2/Puppi/include/DYHists.h"
#include "UHH2/Puppi/include/PuppiTopJetHists.h"


using namespace std;
using namespace uhh2;

namespace uhh2examples {

  class DYModule: public AnalysisModule {
  public:
    
    explicit DYModule(Context & ctx);
    virtual bool process(Event & event) override;

  private:
    bool berror; 
    Event::Handle<vector<Jet>> h_myAK8jets;
    Event::Handle<vector<Jet>> h_myAK8jets_uncorrected;

    enum lepton { muon, elec };
    lepton channel_;
    std::string channel;

    std::unique_ptr<AnalysisModule> printer;

    ///////////////////////////    cleaner    /////////////////////////////////  

    std::unique_ptr<MuonCleaner> muo_cleaner; 
    std::unique_ptr<ElectronCleaner> ele_cleaner;

    ///////////////////////////    Selections    /////////////////////////////////  

    std::unique_ptr<uhh2::AndSelection> lep1_sel; 
    std::unique_ptr<uhh2::Selection> Zmass_sel;
    std::unique_ptr<uhh2::Selection> Zptk50_sel;
    std::unique_ptr<uhh2::Selection> Zptg50_sel;

    ///////////////////////////    Hists    /////////////////////////////////  
    
    std::unique_ptr<uhh2::Hists> uncorrected_h_jet;
    std::unique_ptr<uhh2::Hists> uncorrected_h_topjet;

    ////////////////////////// uncorrected ///////////////////////
    //default histogramms
    std::unique_ptr<uhh2::Hists> uncorrected_input_h_jet;
    std::unique_ptr<uhh2::Hists>uncorrected_input_h_topjet;
    std::unique_ptr<uhh2::Hists>uncorrected_input_h_event;
    std::unique_ptr<uhh2::Hists>uncorrected_input_h_muon;
    std::unique_ptr<uhh2::Hists>uncorrected_input_h_electron;


    std::unique_ptr<PuppiJetHists> uncorrected_h_jet_input; 
    std::unique_ptr<PuppiTopJetHists> uncorrected_h_topjet_input;
    std::unique_ptr<DYHists> uncorrected_h_DY_input;

    //Zptk50 hist after selection
    std::unique_ptr<uhh2::Hists> uncorrected_Zptk50_h_jet;
    std::unique_ptr<uhh2::Hists>uncorrected_Zptk50_h_topjet;
    std::unique_ptr<uhh2::Hists>uncorrected_Zptk50_h_event;
    std::unique_ptr<uhh2::Hists>uncorrected_Zptk50_h_muon;
    std::unique_ptr<uhh2::Hists>uncorrected_Zptk50_h_electron;


    std::unique_ptr<PuppiJetHists> uncorrected_h_jet_Zptk50; 
    std::unique_ptr<PuppiTopJetHists>uncorrected_h_topjet_Zptk50;
    std::unique_ptr<DYHists> uncorrected_h_DY_Zptk50;
 
    //Zptg50 hist after selection
    std::unique_ptr<uhh2::Hists> uncorrected_Zptg50_h_jet;
    std::unique_ptr<uhh2::Hists>uncorrected_Zptg50_h_topjet;
    std::unique_ptr<uhh2::Hists>uncorrected_Zptg50_h_event;
    std::unique_ptr<uhh2::Hists>uncorrected_Zptg50_h_muon;
    std::unique_ptr<uhh2::Hists>uncorrected_Zptg50_h_electron;


    std::unique_ptr<PuppiJetHists> uncorrected_h_jet_Zptg50; 
    std::unique_ptr<PuppiTopJetHists>uncorrected_h_topjet_Zptg50;
    std::unique_ptr<DYHists> uncorrected_h_DY_Zptg50;

    //output hist after selection
    std::unique_ptr<uhh2::Hists> uncorrected_output_h_jet;
    std::unique_ptr<uhh2::Hists>uncorrected_output_h_topjet;
    std::unique_ptr<uhh2::Hists>uncorrected_output_h_event;
    std::unique_ptr<uhh2::Hists>uncorrected_output_h_muon;
    std::unique_ptr<uhh2::Hists>uncorrected_output_h_electron;


    std::unique_ptr<PuppiJetHists> uncorrected_h_jet_output; 
    std::unique_ptr<PuppiTopJetHists> uncorrected_h_topjet_output;
    std::unique_ptr<DYHists> uncorrected_h_DY_output;

    ////////////////////////// corrected ///////////////////////
    //default histogramms
    std::unique_ptr<uhh2::Hists> input_h_jet;
    std::unique_ptr<uhh2::Hists>input_h_topjet;
    std::unique_ptr<uhh2::Hists>input_h_event;
    std::unique_ptr<uhh2::Hists>input_h_muon;
    std::unique_ptr<uhh2::Hists>input_h_electron;


    std::unique_ptr<PuppiJetHists> h_jet_input; 
    std::unique_ptr<PuppiTopJetHists> h_topjet_input;
    std::unique_ptr<DYHists> h_DY_input;

    //Zptk50 hist after selection
    std::unique_ptr<uhh2::Hists> Zptk50_h_jet;
    std::unique_ptr<uhh2::Hists>Zptk50_h_topjet;
    std::unique_ptr<uhh2::Hists>Zptk50_h_event;
    std::unique_ptr<uhh2::Hists>Zptk50_h_muon;
    std::unique_ptr<uhh2::Hists>Zptk50_h_electron;


    std::unique_ptr<PuppiJetHists> h_jet_Zptk50; 
    std::unique_ptr<PuppiTopJetHists> h_topjet_Zptk50;
    std::unique_ptr<DYHists> h_DY_Zptk50;
 
    //Zptg50 hist after selection
    std::unique_ptr<uhh2::Hists> Zptg50_h_jet;
    std::unique_ptr<uhh2::Hists>Zptg50_h_topjet;
    std::unique_ptr<uhh2::Hists>Zptg50_h_event;
    std::unique_ptr<uhh2::Hists>Zptg50_h_muon;
    std::unique_ptr<uhh2::Hists>Zptg50_h_electron;


    std::unique_ptr<PuppiJetHists> h_jet_Zptg50; 
    std::unique_ptr<PuppiTopJetHists> h_topjet_Zptg50;
    std::unique_ptr<DYHists> h_DY_Zptg50;

    //output hist after selection
    std::unique_ptr<uhh2::Hists> output_h_jet;
    std::unique_ptr<uhh2::Hists>output_h_topjet;
    std::unique_ptr<uhh2::Hists>output_h_event;
    std::unique_ptr<uhh2::Hists>output_h_muon;
    std::unique_ptr<uhh2::Hists>output_h_electron;


    std::unique_ptr<PuppiJetHists> h_jet_output; 
    std::unique_ptr<PuppiTopJetHists> h_topjet_output;
    std::unique_ptr<DYHists> h_DY_output;
  
  };


  DYModule::DYModule(Context & ctx){
    berror=(ctx.get("debug") == "true");
    if(ctx.get("mode")=="Puppi")  h_myAK8jets = ctx.get_handle<vector<Jet>>("patJetsAK8PFPUPPI");
    else h_myAK8jets = ctx.get_handle<vector<Jet>>("patJetsAK8PFCHS");
    h_myAK8jets_uncorrected =ctx.declare_event_output< std::vector<Jet> > ("myAK8jets_uncorrected");
    printer.reset(new GenParticlesPrinter(ctx));

   
    channel = ctx.get("channel", "");
    if     (channel == "muon") channel_ = muon;
    else if(channel == "elec") channel_ = elec;
    else throw std::runtime_error("ZprimeSelectionModule -- undefined argument for 'channel' key in xml file (must be 'muon' or 'elec'): "+channel);


    ///////////////////////////    Cleaner    /////////////////////////////////  
    muo_cleaner.reset(new MuonCleaner    (AndId<Muon>    (PtEtaCut  (20., 11), MuonIDTight(),MuonIso(0.15))));
    ele_cleaner.reset(new ElectronCleaner(AndId<Electron>(PtEtaSCCut(20., 11),Electron_MINIIso(0.15,"delta-beta"))));
  


    ///////////////////////////    Selections    /////////////////////////////////  
    lep1_sel.reset(new uhh2::AndSelection(ctx));

    if(channel_ == muon){

      lep1_sel->add<NMuonSelection>    ("muoN == 2", 2);
      lep1_sel->add<NElectronSelection>("eleN == 0", 0, 0);
    }
    else if(channel_ == elec){

      lep1_sel->add<NMuonSelection>    ("muoN == 0", 0, 0);
      lep1_sel->add<NElectronSelection>("eleN == 2", 2);
    }

    Zmass_sel.reset(new ZmassCut(10));
    Zptk50_sel.reset(new ZptCut(50,"max"));
    Zptg50_sel.reset(new ZptCut(50,"min"));

    ///////////////////////////    Hists    /////////////////////////////////  

    uncorrected_h_jet.reset(new JetHists     (ctx, "uncorrected_Jets"));
    if(ctx.get("mode")=="Puppi")  uncorrected_h_topjet.reset(new JetHists (ctx, "uncorrected_TopJets",4,"patJetsAK8PFPUPPI"));
    else uncorrected_h_topjet.reset(new JetHists (ctx, "uncorrected_TopJets",4,"patJetsAK8PFCHS"));

    ////////////////// uncorrected  ///////////////////////////
    uncorrected_input_h_jet.reset(new JetHists     (ctx, "uncorrected_input_Jets"));
    uncorrected_input_h_topjet.reset(new JetHists (ctx, "uncorrected_input_TopJets",4,"patJetsAK8PFCHS"));
    uncorrected_input_h_event.reset(new EventHists (ctx, "uncorrected_input_Event"));
    uncorrected_input_h_muon.reset(new MuonHists (ctx, "uncorrected_input_Muon"));
    uncorrected_input_h_electron.reset(new ElectronHists (ctx, "uncorrected_input_Electron"));

   
    uncorrected_h_jet_input.reset(new PuppiJetHists(ctx, "uncorrected_jet_input"));
    uncorrected_h_topjet_input.reset(new PuppiTopJetHists(ctx, "uncorrected_topjet_input"));
    uncorrected_h_DY_input.reset(new DYHists(ctx, "uncorrected_DY_input"));

    //Zptk50 hist after selection
    uncorrected_Zptk50_h_jet.reset(new JetHists     (ctx, "uncorrected_Zptk50_Jets"));
    uncorrected_Zptk50_h_topjet.reset(new JetHists (ctx, "uncorrected_Zptk50_TopJets",4,"patJetsAK8PFCHS"));
    uncorrected_Zptk50_h_event.reset(new EventHists (ctx, "uncorrected_Zptk50_Event"));
    uncorrected_Zptk50_h_muon.reset(new MuonHists (ctx, "uncorrected_Zptk50_Muon"));
    uncorrected_Zptk50_h_electron.reset(new ElectronHists (ctx, "uncorrected_Zptk50_Electron"));

   
    uncorrected_h_jet_Zptk50.reset(new PuppiJetHists(ctx, "uncorrected_jet_Zptk50"));
    uncorrected_h_topjet_Zptk50.reset(new PuppiTopJetHists(ctx, "uncorrected_topjet_Zptk50"));
    uncorrected_h_DY_Zptk50.reset(new DYHists(ctx, "uncorrected_DY_Zptk50"));

    //Zptg50 hist after selection
    uncorrected_Zptg50_h_jet.reset(new JetHists     (ctx, "uncorrected_Zptg50_Jets"));
    uncorrected_Zptg50_h_topjet.reset(new JetHists (ctx, "uncorrected_Zptg50_TopJets",4,"patJetsAK8PFCHS"));
    uncorrected_Zptg50_h_event.reset(new EventHists (ctx, "uncorrected_Zptg50_Event"));
    uncorrected_Zptg50_h_muon.reset(new MuonHists (ctx, "uncorrected_Zptg50_Muon"));
    uncorrected_Zptg50_h_electron.reset(new ElectronHists (ctx, "uncorrected_Zptg50_Electron"));

   
    uncorrected_h_jet_Zptg50.reset(new PuppiJetHists(ctx, "uncorrected_jet_Zptg50"));
    uncorrected_h_topjet_Zptg50.reset(new PuppiTopJetHists(ctx, "uncorrected_topjet_Zptg50"));
    uncorrected_h_DY_Zptg50.reset(new DYHists(ctx, "uncorrected_DY_Zptg50"));


    //output hist after selection
    uncorrected_output_h_jet.reset(new JetHists     (ctx, "uncorrected_output_Jets"));
    uncorrected_output_h_topjet.reset(new JetHists (ctx, "uncorrected_output_TopJets",4,"patJetsAK8PFCHS"));
    uncorrected_output_h_event.reset(new EventHists (ctx, "uncorrected_output_Event"));
    uncorrected_output_h_muon.reset(new MuonHists (ctx, "uncorrected_output_Muon"));
    uncorrected_output_h_electron.reset(new ElectronHists (ctx, "uncorrected_output_Electron"));

   
    uncorrected_h_jet_output.reset(new PuppiJetHists(ctx, "uncorrected_jet_output"));
    uncorrected_h_topjet_output.reset(new PuppiTopJetHists(ctx, "uncorrected_topjet_output"));
    uncorrected_h_DY_output.reset(new DYHists(ctx, "uncorrected_DY_output"));


    /////////////////////////////////////  corrected  ///////////////////////////
    input_h_jet.reset(new JetHists     (ctx, "input_Jets"));
    input_h_topjet.reset(new JetHists (ctx, "input_TopJets",4,"myAK8jets_uncorrected"));
    input_h_event.reset(new EventHists (ctx, "input_Event"));
    input_h_muon.reset(new MuonHists (ctx, "input_Muon"));
    input_h_electron.reset(new ElectronHists (ctx, "input_Electron"));

   
    h_jet_input.reset(new PuppiJetHists(ctx, "jet_input"));
    h_topjet_input.reset(new PuppiTopJetHists(ctx, "topjet_input"));
    h_DY_input.reset(new DYHists(ctx, "DY_input"));

    //Zptk50 hist after selection
    Zptk50_h_jet.reset(new JetHists     (ctx, "Zptk50_Jets"));
    Zptk50_h_topjet.reset(new JetHists (ctx, "Zptk50_TopJets",4,"myAK8jets_uncorrected"));
    Zptk50_h_event.reset(new EventHists (ctx, "Zptk50_Event"));
    Zptk50_h_muon.reset(new MuonHists (ctx, "Zptk50_Muon"));
    Zptk50_h_electron.reset(new ElectronHists (ctx, "Zptk50_Electron"));

   
    h_jet_Zptk50.reset(new PuppiJetHists(ctx, "jet_Zptk50"));
    h_topjet_Zptk50.reset(new PuppiTopJetHists(ctx, "topjet_Zptk50"));
    h_DY_Zptk50.reset(new DYHists(ctx, "DY_Zptk50"));

    //Zptg50 hist after selection
    Zptg50_h_jet.reset(new JetHists     (ctx, "Zptg50_Jets"));
    Zptg50_h_topjet.reset(new JetHists (ctx, "Zptg50_TopJets",4,"myAK8jets_uncorrected"));
    Zptg50_h_event.reset(new EventHists (ctx, "Zptg50_Event"));
    Zptg50_h_muon.reset(new MuonHists (ctx, "Zptg50_Muon"));
    Zptg50_h_electron.reset(new ElectronHists (ctx, "Zptg50_Electron"));

   
    h_jet_Zptg50.reset(new PuppiJetHists(ctx, "jet_Zptg50"));
    h_topjet_Zptg50.reset(new PuppiTopJetHists(ctx, "topjet_Zptg50"));
    h_DY_Zptg50.reset(new DYHists(ctx, "DY_Zptg50"));


    //output hist after selection
    output_h_jet.reset(new JetHists     (ctx, "output_Jets"));
    output_h_topjet.reset(new JetHists (ctx, "output_TopJets",4,"myAK8jets_uncorrected"));
    output_h_event.reset(new EventHists (ctx, "output_Event"));
    output_h_muon.reset(new MuonHists (ctx, "output_Muon"));
    output_h_electron.reset(new ElectronHists (ctx, "output_Electron"));

   
    h_jet_output.reset(new PuppiJetHists(ctx, "jet_output"));
    h_topjet_output.reset(new PuppiTopJetHists(ctx, "topjet_output"));
    h_DY_output.reset(new DYHists(ctx, "DY_output"));
   
  }


  bool DYModule::process(Event & event) {
    if(berror) std::cout<<" ====================    New Event   ===================="<<std::endl;
    if(berror) printer->process(event);
    vector<Jet>  myAK8jets = event.get(h_myAK8jets);
   
    event.set(h_myAK8jets_uncorrected,myAK8jets);

    uncorrected_h_jet   ->fill(event);
    uncorrected_h_topjet ->fill(event);

    uncorrected_input_h_jet   ->fill(event);
    uncorrected_input_h_event   ->fill(event);
    uncorrected_input_h_topjet ->fill(event);
    uncorrected_input_h_muon   ->fill(event);
    uncorrected_input_h_electron ->fill(event);


    uncorrected_h_jet_input->fill(event);
    uncorrected_h_topjet_input->fill(event);
    uncorrected_h_DY_input->fill(event);

    if(berror)  std::cout<<"-------- DYModul::uncorrected Selection -------"<<std::endl;
    ///////////////////////////////////////////////////          Selection    //////////////////////////////////////////
    if(channel=="muon")muo_cleaner->process(event);
    else ele_cleaner->process(event);
    bool pass_lep1 = lep1_sel->passes(event);
    if(!pass_lep1)return false;

    bool pass_ZmassCut = Zmass_sel->passes(event);
    if(!pass_ZmassCut)return false;


    if(berror)  std::cout<<"-------- DYModul::uncorrected ZPt <50 -------"<<std::endl;
    ///////////////////////////////////////////////////          ZPt <50     //////////////////////////////////////////
    bool pass_Zptk50 = Zptk50_sel->passes(event);
    if(pass_Zptk50){
    //Zptk50 hist after selection
    uncorrected_Zptk50_h_jet   ->fill(event);
    uncorrected_Zptk50_h_event   ->fill(event);
    uncorrected_Zptk50_h_topjet ->fill(event);
    uncorrected_Zptk50_h_muon   ->fill(event);
    uncorrected_Zptk50_h_electron ->fill(event);


    uncorrected_h_jet_Zptk50->fill(event);
    uncorrected_h_topjet_Zptk50->fill(event);
    uncorrected_h_DY_Zptk50->fill(event);
    }

    if(berror)  std::cout<<"-------- DYModul::uncorrected ZPt >50 -------"<<std::endl;
    ///////////////////////////////////////////////////          ZPt >50     //////////////////////////////////////////
    bool pass_Zptg50 = Zptg50_sel->passes(event);
    if(pass_Zptg50){
    //Zptg50 hist after selection
    uncorrected_Zptg50_h_jet   ->fill(event);
    uncorrected_Zptg50_h_event   ->fill(event);
    uncorrected_Zptg50_h_topjet ->fill(event);
    uncorrected_Zptg50_h_muon   ->fill(event);
    uncorrected_Zptg50_h_electron ->fill(event);


    uncorrected_h_jet_Zptg50->fill(event);
    uncorrected_h_topjet_Zptg50->fill(event);
    uncorrected_h_DY_Zptg50->fill(event);
    }

    if(berror)  std::cout<<"-------- DYModul::uncorrected Output -------"<<std::endl;
    ///////////////////////////////////////////////////          output     //////////////////////////////////////////
    //output hist after selection
    uncorrected_output_h_jet   ->fill(event);
    uncorrected_output_h_event   ->fill(event);
    uncorrected_output_h_topjet ->fill(event);
    uncorrected_output_h_muon   ->fill(event);
    uncorrected_output_h_electron ->fill(event);


    uncorrected_h_jet_output->fill(event);
    uncorrected_h_topjet_output->fill(event);
    uncorrected_h_DY_output->fill(event);


    if(berror)  std::cout<<"-------- DYModul::Jec_factor_raw -------"<<std::endl;
    ////////////////////////////////////////////////////////////////////////////////////   Jets and topjets back correcting  ///////////////////////////////////////////////////////////////////////////////////////// 
    for (auto & jet:*event.jets)  jet.set_v4(jet.v4() * jet.JEC_factor_raw() );
    if(berror) std::cout<<"myAK8jets first jet mass  "<<myAK8jets.at(0).v4().M()<<std::endl;
    for (auto & jet:myAK8jets)   jet.set_v4(jet.v4() * jet.JEC_factor_raw() );
    if(berror) std::cout<<"after JEC raw corrected myAK8jets first jet mass  "<<myAK8jets.at(0).v4().M()<<std::endl;
    sort_by_pt<Jet>(*event.jets);
    event.set(h_myAK8jets_uncorrected,myAK8jets);

    input_h_jet   ->fill(event);
    input_h_event   ->fill(event);
    input_h_topjet ->fill(event);
    input_h_muon   ->fill(event);
    input_h_electron ->fill(event);


    h_jet_input->fill(event);
    h_topjet_input->fill(event);
    h_DY_input->fill(event);

    if(berror)  std::cout<<"-------- DYModul::Selection -------"<<std::endl;
    ///////////////////////////////////////////////////          Selection    //////////////////////////////////////////
    if(channel=="muon")muo_cleaner->process(event);
    else ele_cleaner->process(event);
    pass_lep1 = lep1_sel->passes(event);
    if(!pass_lep1)return false;

    pass_ZmassCut = Zmass_sel->passes(event);
    if(!pass_ZmassCut)return false;


    if(berror)  std::cout<<"-------- DYModul::ZPt <50 -------"<<std::endl;
    ///////////////////////////////////////////////////          ZPt <50     //////////////////////////////////////////
    pass_Zptk50 = Zptk50_sel->passes(event);
    if(pass_Zptk50){
    //Zptk50 hist after selection
    Zptk50_h_jet   ->fill(event);
    Zptk50_h_event   ->fill(event);
    Zptk50_h_topjet ->fill(event);
    Zptk50_h_muon   ->fill(event);
    Zptk50_h_electron ->fill(event);


    h_jet_Zptk50->fill(event);
    h_topjet_Zptk50->fill(event);
    h_DY_Zptk50->fill(event);
    }

    if(berror)  std::cout<<"-------- DYModul::ZPt >50 -------"<<std::endl;
    ///////////////////////////////////////////////////          ZPt >50     //////////////////////////////////////////
    pass_Zptg50 = Zptg50_sel->passes(event);
    if(pass_Zptg50){
    //Zptg50 hist after selection
    Zptg50_h_jet   ->fill(event);
    Zptg50_h_event   ->fill(event);
    Zptg50_h_topjet ->fill(event);
    Zptg50_h_muon   ->fill(event);
    Zptg50_h_electron ->fill(event);


    h_jet_Zptg50->fill(event);
    h_topjet_Zptg50->fill(event);
    h_DY_Zptg50->fill(event);
    }

    if(berror)  std::cout<<"-------- DYModul::Output -------"<<std::endl;
    ///////////////////////////////////////////////////          output     //////////////////////////////////////////
    //output hist after selection
    output_h_jet   ->fill(event);
    output_h_event   ->fill(event);
    output_h_topjet ->fill(event);
    output_h_muon   ->fill(event);
    output_h_electron ->fill(event);


    h_jet_output->fill(event);
    h_topjet_output->fill(event);
    h_DY_output->fill(event);

    return true;
  }


  UHH2_REGISTER_ANALYSIS_MODULE(DYModule)

}
