#pragma once

#include "UHH2/core/include/fwd.h"
#include "UHH2/core/include/Selection.h"
#include "UHH2/core/include/Event.h"
#include "UHH2/core/include/Utils.h"

namespace uhh2examples {
    
/* Select events with at least two jets in which the leading two jets have deltaphi > 2.7 and the third jet pt is
 * below 20% of the average of the leading two jets, where the minimum deltaphi and
 * maximum third jet pt fraction can be changed in the constructor.
 * The jets are assumed to be sorted in pt.
 */

class ZmassCut: public uhh2::Selection {
public:
    ZmassCut(double threshold);
    virtual bool passes(const uhh2::Event & event) override;
private:
    double threshold;
    double inv_mass;  
    Muon muon_pos;
    Muon muon_neg;

};

class ZptCut: public uhh2::Selection {
public:
    ZptCut(double threshold, TString minmax);
    virtual bool passes(const uhh2::Event & event) override;
private:
    double threshold;
    double inv_pt;  
    Muon muon_pos;
    Muon muon_neg;
    TString minmax;

};
}
