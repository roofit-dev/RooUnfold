//=====================================================================-*-C++-*-
// File and Version Information:
//      $Id$
//
// Description:
//      Generate base information for unit tests
//
// Authors: Vincent Croft <vincent.croft@cern.ch>
//
//==============================================================================

#include "TRandom.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TFile.h"
#include "RooUnfoldResponse.h"

#include "unittests.h"

const Double_t cutdummy= -99999.0;
TRandom randy(666.);

Double_t smear (Double_t xt)
{
  Double_t xeff= 0.3 + (1.0-0.3)/20*(xt+10.0);  // efficiency
  Double_t x= randy.Rndm();
  if (x>xeff) return cutdummy;
  Double_t xsmear= randy.Gaus(-2.5,0.2);     // bias and smear
  return xt+xsmear;
}

void RooUnfoldGenerate()
{
  TH1D* h_gen= new TH1D ("gen", "Train Truth",    40, -10.0, 10.0);
  TH1D* h_sim= new TH1D ("sim", "Train Measured", 40, -10.0, 10.0);
  TH2D* h_response= new TH2D ("res", "Response Hist", 40, -10.0, 10.0, 40, -10.0, 10.0);
  RooUnfoldResponse response (40, -10.0, 10.0);

  // Train with a Breit-Wigner, mean 0.3 and width 2.5.
  for (Int_t i= 0; i<100000; i++) {
    Double_t xt= randy.BreitWigner (0.3, 2.5);
    Double_t x= smear (xt);
    h_gen->Fill(xt);
    if (x!=cutdummy){
      response.Fill(x, xt);
      h_response->Fill(x, xt);
      h_sim->Fill(x);
    }
    else {
      response.Miss (xt);
    }
  }

  TH1D* h_true= new TH1D ("true", "Test Truth",    40, -10.0, 10.0);
  TH1D* h_meas= new TH1D ("meas", "Test Measured", 40, -10.0, 10.0);
  // Test with a Gaussian, mean 0 and width 2.
  for (Int_t i=0; i<10000; i++) {
    Double_t xt= randy.Gaus (0.0, 2.0), x= smear (xt);
    h_true->Fill(xt);
    if (x!=cutdummy) h_meas->Fill(x);
  }

  // Save objects to file
  TFile* output = new TFile("response.root","RECREATE");
  output->cd();
  h_response->Write();
  h_true->Write();
  h_meas->Write();
  h_gen->Write();
  h_sim->Write();
  output->Write();
  
}
