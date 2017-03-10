#include "UHH2/Puppi/include/PuppiSelections.h"
#include "UHH2/core/include/Event.h"

#include <stdexcept>

using namespace uhh2examples;
using namespace uhh2;





ZmassCut::ZmassCut(double threshold_): threshold(threshold_){}
    
bool ZmassCut::passes(const Event & event){
    assert(event.muons); // if this fails, it probably means muons are not read in
    std::vector<Muon> *muons = event.muons;
 

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


    inv_mass=(muon_pos.v4() + muon_neg.v4()).M();
    return inv_mass<threshold;

}

ZptCut::ZptCut(double threshold_, TString minmax_): threshold(threshold_),minmax(minmax_){}
    
bool ZptCut::passes(const Event & event){
    assert(event.muons); // if this fails, it probably means muons are not read in
    std::vector<Muon> *muons = event.muons;
 

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


    inv_pt=(muon_pos.v4() + muon_neg.v4()).pt();
    if(minmax=="max") return inv_pt<threshold;
    if(minmax=="min") return inv_pt>threshold;

}
