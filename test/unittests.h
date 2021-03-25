#ifndef __UNITTESTS_H__
#define __UNITTESTS_H__

#include "RooUnfoldResponse.h"
#include "TVector.h"

void RooUnfoldGenerate();
RooUnfoldResponse BuildRooUnfoldResponse();
TVector BuildRooUnfoldBayes();
void WriteRooUnfoldBayes();
TVector BuildRooUnfoldSVD();
void WriteRooUnfoldSVD();
TVector BuildRooUnfoldTUnfold();
void WriteRooUnfoldTUnfold();
TVector BuildRooUnfoldInvert();
void WriteRooUnfoldInvert();
TVector BuildRooUnfoldBinByBin();
void WriteRooUnfoldBinByBin();

#endif
