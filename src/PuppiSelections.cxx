#include "UHH2/Puppi/include/PuppiSelections.h"
#include "UHH2/core/include/Event.h"

#include <stdexcept>

using namespace uhh2examples;
using namespace uhh2;





ZmassCut::ZmassCut(double threshold_): threshold(threshold_){}
    
bool ZmassCut::passes(const Event & event ){

    if(event.muons){
      for(auto m:*event.muons){
	if(m.charge()==1){
	  lep_pos=m;
	  break;
	}
      }
      for(auto m:*event.muons){
	if(m.charge()==-1){
	  lep_neg=m;
	  break;
	}
      }
    }else if(event.electrons){
      for(auto m:*event.electrons){
	if(m.charge()==1){
	  lep_pos=m;
	  break;
	}
      }
      for(auto m:*event.electrons){
	if(m.charge()==-1){
	  lep_neg=m;
	  break;
	}
      }
    }


    inv_mass=(lep_pos.v4() + lep_neg.v4()).M();
    return abs(inv_mass-91)<threshold;

}

ZptCut::ZptCut(double threshold_,TString minmax_): threshold(threshold_),minmax(minmax_){}
    
bool ZptCut::passes(const Event & event){
  // if(channel=="muon"){
  //   assert(event.muons); // if this fails, it probably means muons are not read in
  //   std::vector<Muon> *leptons = event.muons;
  // }else{
  //   assert(event.electrons); // if this fails, it probably means muons are not read in
  //   std::vector<Electron> *leptons = event.electrons;
  // }

  //   for(auto m:*leptons){
  //     if(m.charge()==1){
  // 	lep_pos=m;
  // 	break;
  //     }
  //   }
  //   for(auto m:*leptons){
  //     if(m.charge()==-1){
  // 	lep_neg=m;
  // 	break;
  //     }
  //   }
  if(event.muons){
      for(auto m:*event.muons){
	if(m.charge()==1){
	  lep_pos=m;
	  break;
	}
      }
      for(auto m:*event.muons){
	if(m.charge()==-1){
	  lep_neg=m;
	  break;
	}
      }
    }else if(event.electrons){
      for(auto m:*event.electrons){
	if(m.charge()==1){
	  lep_pos=m;
	  break;
	}
      }
      for(auto m:*event.electrons){
	if(m.charge()==-1){
	  lep_neg=m;
	  break;
	}
      }
    }

    inv_pt=(lep_pos.v4() + lep_neg.v4()).pt();
    if(minmax=="max") return inv_pt<threshold;
    if(minmax=="min") return inv_pt>threshold;
    return inv_pt<threshold;
}
