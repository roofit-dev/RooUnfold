//=====================================================================-*-C++-*-
// File and Version Information:
//      $Id$
//
// Description:
//      Unit tests for RooUnfoldBinByBin
//
// Authors: Vincent Croft <vincent.croft@cern.ch>
//
//==============================================================================

#include "RooUnfoldResponse.h"
#include "RooUnfoldBinByBin.h"
#include "TFile.h"
#include "TVector.h"
#include "unittests.h"

#include <iostream>
#include <fstream>

TVector BuildRooUnfoldBinByBin()
{
  TFile* f = new TFile("response.root","OPEN");  
  TH1D* h_meas = (TH1D*)f->Get("meas");
  RooUnfoldResponse response = BuildRooUnfoldResponse();
  RooUnfoldBinByBin unfold(&response, h_meas);
  TH1D* h_unfolded = (TH1D*)unfold.Hreco();
  TVector u(h_unfolded->GetNbinsX());
  for (int i=0; i<h_unfolded->GetNbinsX(); i++){
    u[i] = h_unfolded->GetBinContent(i+1);
  }
  return u;
}

void WriteRooUnfoldBinByBin()
{
  TVector u = BuildRooUnfoldBinByBin();
  std::ofstream ref;
  ref.open("../ref/bbb.ref");
  for (int i=0;i<u.GetNrows();i++){
    ref << u[i]<<std::endl;
  }
  ref.close();
}
