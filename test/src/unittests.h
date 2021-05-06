#ifndef __UNITTESTS_H__
#define __UNITTESTS_H__

#include "RooUnfoldResponse.h"
#include "TVector.h"
#include <string>

void RooUnfoldGenerate();
void RooUnfoldGenerateVariable();
RooUnfoldResponse BuildRooUnfoldResponse(std::string);
TVector BuildRooUnfoldBayes(int);
void WriteRooUnfoldBayes(int);
TVector BuildRooUnfoldSVD(int);
void WriteRooUnfoldSVD(int);
TVector BuildRooUnfoldTUnfold(int);
void WriteRooUnfoldTUnfold(int);
TVector BuildRooUnfoldInvert(int);
void WriteRooUnfoldInvert(int);
TVector BuildRooUnfoldBinByBin(int);
void WriteRooUnfoldBinByBin(int);
int TestBayes(int);
int TestSVD(int);
int TestInvert(int);
int TestBinByBin(int);
char *test_algs();
char *test_bayes();
char *test_svd();
char *test_invert();
char *test_bbb();
char *all_tests();

#endif
