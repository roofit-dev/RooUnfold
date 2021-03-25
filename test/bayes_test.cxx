//=====================================================================-*-C++-*-
// File and Version Information:
//      $Id$
//
// Description:
//      Unit tests for RooUnfoldBayes
//
// Authors: Vincent Croft <vincent.croft@cern.ch>
//
//==============================================================================

#include "RooUnfoldResponse.h"
#include "RooUnfoldBayes.h"
#include "TFile.h"
#include "TVector.h"
#include "unittests.h"

#include <iostream>
#include <fstream>

TVector BuildRooUnfoldBayes()
{
  TFile* f = new TFile("response.root","OPEN");  
  TH1D* h_meas = (TH1D*)f->Get("meas");
  RooUnfoldResponse response = BuildRooUnfoldResponse();
  RooUnfoldBayes unfold(&response, h_meas, 4);
  TH1D* h_unfolded = (TH1D*)unfold.Hreco();
  TVector u(h_unfolded->GetNbinsX());
  for (int i=0; i<h_unfolded->GetNbinsX(); i++){
    u[i] = h_unfolded->GetBinContent(i+1);
  }
  return u;
}

void WriteRooUnfoldBayes()
{
  TVector u = BuildRooUnfoldBayes();
  std::ofstream ref;
  ref.open("../ref/bayes.ref");
  for (int i=0;i<u.GetNrows();i++){
    ref << u[i]<<std::endl;
  }
  ref.close();
}
