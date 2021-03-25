#include "unittests.h"
#include <iostream>
using std::cout;
using std::endl;

int main(){
  RooUnfoldGenerate();
  WriteRooUnfoldBayes();
  WriteRooUnfoldSVD();
  //WriteRooUnfoldTUnfold();
  WriteRooUnfoldInvert();
  WriteRooUnfoldBinByBin();
}
