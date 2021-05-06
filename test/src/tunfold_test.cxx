//=====================================================================-*-C++-*-
// File and Version Information:
//      $Id$
//
// Description:
//      Unit tests for RooUnfoldTUnfold
//
// Authors: Vincent Croft <vincent.croft@cern.ch>
//
//==============================================================================

#include "RooUnfoldResponse.h"
#include "RooUnfoldTUnfold.h"
#include "TFile.h"
#include "TVector.h"
#include "unittests.h"

#include <iostream>
#include <fstream>

TVector BuildRooUnfoldTUnfold(int mode = 0)
{
    char* filename;
    if (mode==0)
        filename = "response.root";
    else if (mode==1)
        filename = "response_var.root";
    TFile* f = new TFile(filename,"OPEN");
    TH1D* h_meas = (TH1D*)f->Get("meas");
    RooUnfoldResponse response = BuildRooUnfoldResponse(filename);
    RooUnfoldTUnfold unfold(&response, h_meas);
    TH1D* h_unfolded = (TH1D*)unfold.Hreco();
    TVector u(h_unfolded->GetNbinsX());
    for (int i=0; i<h_unfolded->GetNbinsX(); i++){
        u[i] = h_unfolded->GetBinContent(i+1);
    }
    return u;
}

void WriteRooUnfoldTUnfold(int mode = 0)
{
    TVector u = BuildRooUnfoldTUnfold(mode);
    std::ofstream ref;
    char* filename;
    if (mode==0)
        filename = "../ref/tunfold.ref";
    else if (mode==1)
        filename = "../ref/tunfold_var.ref";
    ref.open(filename);
    for (int i=0;i<u.GetNrows();i++){
        ref << u[i]<<std::endl;
    }
    ref.close();
}
