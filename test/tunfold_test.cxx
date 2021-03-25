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

TVector BuildRooUnfoldTUnfold()
{
  TFile* f = new TFile("response.root","OPEN");  
  TH1D* h_meas = (TH1D*)f->Get("meas");
  RooUnfoldResponse response = BuildRooUnfoldResponse();
  RooUnfoldTUnfold unfold(&response, h_meas);
  TH1D* h_unfolded = (TH1D*)unfold.Hreco();
  TVector u(h_unfolded->GetNbinsX());
  for (int i=0; i<h_unfolded->GetNbinsX(); i++){
    u[i] = h_unfolded->GetBinContent(i+1);
  }
  return u;
}

void WriteRooUnfoldTUnfold()
{
  TVector u = BuildRooUnfoldTUnfold();
  std::ofstream ref;
  ref.open("../ref/tunfold.ref");
  for (int i=0;i<u.GetNrows();i++){
    ref << u[i]<<std::endl;
  }
  ref.close();
}
