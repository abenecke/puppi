#pragma once

#include "UHH2/core/include/Hists.h"
#include "TH2F.h"

namespace uhh2examples {


class DYHists: public uhh2::Hists {
public:
    // use the same constructor arguments as Hists for forwarding:
    DYHists(uhh2::Context & ctx, const std::string & dirname);

    virtual void fill(const uhh2::Event & ev) override;
    virtual ~DYHists();
  protected:
    bool berror;

    //General
    TH1F *MET;

    //Response
    TH2F *response_ZP, *response_NPV,*rms_ZP,*rms_uper_ZP,*rms_uper_NPV;
};

}
