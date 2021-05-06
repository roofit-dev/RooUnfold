#include "src/unittests.h"
#include <iostream>
using std::cout;
using std::endl;

int main(){
    RooUnfoldGenerate();
    RooUnfoldGenerateVariable();
    WriteRooUnfoldBayes(0);
    WriteRooUnfoldBayes(1);
    WriteRooUnfoldSVD(0);
    WriteRooUnfoldSVD(1);
    //WriteRooUnfoldTUnfold(0);
    //WriteRooUnfoldTUnfold(1);
    WriteRooUnfoldInvert(0);
    WriteRooUnfoldInvert(1);
    WriteRooUnfoldBinByBin(0);
    WriteRooUnfoldBinByBin(1);
}
