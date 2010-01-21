//=====================================================================-*-C++-*-
// File and Version Information:
//      $Id: RooUnfoldTestHarness3D.h,v 1.7 2010-01-21 20:05:14 adye Exp $
//
// Description:
//      Harness class to test the RooUnfold package using 3D toy MC generated
//      according to PDFs defined in RooUnfoldTestPdf.icc or RooUnfoldTestPdfRooFit.icc.
//
// Author: Tim Adye <T.J.Adye@rl.ac.uk>
//
//==============================================================================

#ifndef ROOUNFOLDTESTHARNESS3D_HH
#define ROOUNFOLDTESTHARNESS3D_HH

#include "RooUnfoldTestHarness2D.h"

#if !defined(__CINT__) || defined(__MAKECINT__)
#include "TH3.h"
#endif

class TH1;
class TH1D;

class RooUnfoldTestHarness3D : public RooUnfoldTestHarness2D {
public:
  // Parameters
  Int_t    ftrainz, ftestz, ntz, nmz;
  Double_t zlo, zhi, mtrainz, wtrainz, btrainz, mtestz, wtestz, btestz, effzlo, effzhi, rotxz, rotyz, zbias, zsmear;

  TH1D *hTrainZ, *hTrainTrueZ, *hTrueZ, *hMeasZ, *hRecoZ, *hPDFz, *hTestPDFz;

  // Constructors
  RooUnfoldTestHarness3D (const char* name= "RooUnfoldTest3D");
  RooUnfoldTestHarness3D (const char* name, const char* args);
  RooUnfoldTestHarness3D (const char* name, int argc, const char* const* argv);
  virtual ~RooUnfoldTestHarness3D() {}

  virtual void  Reset();
  virtual void  Init();
  virtual Int_t Train();
  virtual Int_t Test();
  virtual void  ShowTest();
  virtual void  Results();
  virtual Int_t CheckParms();
  virtual void  Parms (ArgVars& args);

  void Smear3D (Double_t& xt, Double_t& yt, Double_t& zt) const;
  bool Eff3D   (Double_t  xt, Double_t  yt, Double_t  zt) const;

  Int_t Fill (TH1* h, Double_t x, Double_t y, Double_t z) {TH3* h3= dynamic_cast<TH3*>(h); return h3->Fill (x, y, z);}
  static TH1D* Projection3D (const TH1* h, Option_t* xyz, const char* name, const char* title, Option_t* opt);
  static TH1D* ProjectionX (const TH1* h, const char* name=0, const char* title=0, Option_t* opt="") {return Projection3D(h,"x",name,title,opt);}
  static TH1D* ProjectionY (const TH1* h, const char* name=0, const char* title=0, Option_t* opt="") {return Projection3D(h,"y",name,title,opt);}
  static TH1D* ProjectionZ (const TH1* h, const char* name=0, const char* title=0, Option_t* opt="") {return Projection3D(h,"z",name,title,opt);}
};

#ifndef NOINLINE
#include "RooUnfoldTestHarness3D.icc"
#endif

#endif