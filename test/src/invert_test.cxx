//=====================================================================-*-C++-*-
// File and Version Information:
//      $Id$
//
// Description:
//      Unit tests for RooUnfoldInvert
//
// Authors: Vincent Croft <vincent.croft@cern.ch>
//
//==============================================================================

#include "RooUnfoldResponse.h"
#include "RooUnfoldInvert.h"
#include "TFile.h"
#include "TVector.h"
#include "unittests.h"

#include <iostream>
#include <fstream>

TVector BuildRooUnfoldInvert(int mode=0)
{
    char* filename;
    if (mode==0)
        filename = "response.root";
    else if (mode==1)
        filename = "response_var.root";
    TFile* f = new TFile(filename, "OPEN");
    TH1D* h_meas = (TH1D*)f->Get("meas");
    RooUnfoldResponse response = BuildRooUnfoldResponse(filename);
    RooUnfoldInvert unfold(&response, h_meas);
    TH1D* h_unfolded = (TH1D*)unfold.Hreco();
    TVector u(h_unfolded->GetNbinsX());
    for (int i=0; i<h_unfolded->GetNbinsX(); i++){
        u[i] = h_unfolded->GetBinContent(i+1);
    }
    return u;
}

void WriteRooUnfoldInvert(int mode = 0)
{
    TVector u = BuildRooUnfoldInvert(mode);
    std::ofstream ref;
    char* filename;
    if (mode==0)
        filename = "../ref/invert.ref";
    else if (mode==1)
        filename = "../ref/invert_var.ref";
    ref.open(filename);
    for (int i=0;i<u.GetNrows();i++){
        ref << u[i]<<std::endl;
    }
    ref.close();
}
