#include <iostream>
#include <fstream>
#include <string>
#include "dbg.h"
#include "minunit.h"
using std::cout;
using std::endl;

#include "unittests.h"

int TestBayes(int mode=0){
    auto u = BuildRooUnfoldBayes(mode);
    int n = u.GetNrows();

    std::vector<float> r;
    std::string ref_name;
    if (mode==0)
        ref_name = "../ref/bayes.ref";
    else if (mode==1)
        ref_name = "../ref/bayes_var.ref";
    std::ifstream ref(ref_name);
    if (ref.is_open()){
        std::string line;
        while (getline(ref,line)){
            r.push_back(std::stof(line));
        }
        ref.close();
    }

    for (int i=0; i<n; i++){
        check(EQ(u[i], r[i], 1), "error in bayes bin: %d as %f is not %f",i,u[i],r[i]);
    }

    return 1;
    error:
    return -1;
}


int TestSVD(int mode = 0){
    auto u = BuildRooUnfoldSVD(mode);
    int n = u.GetNrows();

    std::vector<float> r;
    std::string ref_name;
    if (mode==0)
        ref_name = "../ref/svd.ref";
    else if (mode==1)
        ref_name = "../ref/svd_var.ref";
    std::ifstream ref(ref_name);
    if (ref.is_open()) {
        std::string line;
        while (getline(ref, line)) {
            r.push_back(std::stof(line));
        }
        ref.close();
    }

    for (int i=0; i<n; i++){
        check(EQ(u[i], r[i], 1), "error in svd bin: %d as %f is not %f",i,u[i],r[i]);
    }
  
    return 1;
    error:
    return -1;
}

int TestInvert(int mode = 0){
    auto u = BuildRooUnfoldInvert(mode);
    int n = u.GetNrows();

    std::vector<float> r;
    std::string ref_name;
    if (mode==0)
        ref_name = "../ref/invert.ref";
    else if (mode==1)
        ref_name = "../ref/invert_var.ref";
    std::ifstream ref(ref_name);

    if (ref.is_open()){
        std::string line;
        while (getline(ref,line)){
            r.push_back(std::stof(line));
        }
        ref.close();
    }
    for (int i=0; i<n; i++){
        check(EQ(u[i], r[i], 0), "error in matrix invert bin: %d as %f is not %f",i,u[i],r[i]);
    }
  
    return 1;
    error:
    return -1;
}


int TestBinByBin(int mode = 0){
    auto u = BuildRooUnfoldBinByBin(mode);
    int n = u.GetNrows();

    std::vector<float> r;
    std::string ref_name;
    if (mode==0)
        ref_name = "../ref/bbb.ref";
    else if (mode==1)
        ref_name = "../ref/bbb_var.ref";
    std::ifstream ref(ref_name);
    if (ref.is_open()){
        std::string line;
        while (getline(ref,line)){
            r.push_back(std::stof(line));
        }
        ref.close();
    }
    for (int i=0; i<n; i++){
        check(EQ(u[i], r[i], 0), "error in binbybin bin: %d as %f is not %f",i,u[i],r[i]);
    }

    return 1;
    error:
    return -1;
}


char *test_algs(){
  mu_assert(TestBayes()==1, "binwise test of Bayes failed");
  mu_assert(TestSVD()==1, "binwise test of SVD failed");
  mu_assert(TestInvert()==1, "binwise test of Invert failed");
  mu_assert(TestBinByBin()==1, "binwise test of BinByBin failed");  
  return NULL;
}

char *run_bayes(){
    mu_assert(TestBayes(0)==1, "binwise test of Bayes failed");
    mu_assert(TestBayes(1)==1, "binwise test of variable binning in Bayes failed");
    return NULL;
}

char *run_svd(){
    mu_assert(TestSVD(0)==1, "binwise test of SVD failed");
    mu_assert(TestSVD(1)==1, "binwise test of variable binning in SVD failed");
    return NULL;
}
char *run_invert(){
    mu_assert(TestInvert(0)==1, "binwise test of Invert failed");
    mu_assert(TestInvert(1)==1, "binwise test of variable binning in Invert failed");
    return NULL;
}
char *run_bbb(){
    mu_assert(TestBinByBin(0)==1, "binwise test of BinByBin failed");
    mu_assert(TestBinByBin(1)==1, "binwise test of variable binning in BinByBin failed");
    return NULL;
}

char *all_tests(){
  RooUnfoldGenerate();
  mu_suite_start();
  mu_run_test(test_algs);
  return NULL;
}

char *test_bayes(){
    RooUnfoldGenerate();
    RooUnfoldGenerateVariable();    
    mu_suite_start();
    mu_run_test(run_bayes);
    return NULL;
}

char *test_svd(){
    RooUnfoldGenerate();
    RooUnfoldGenerateVariable();        
    mu_suite_start();
    mu_run_test(run_svd);
    return NULL;
}

char *test_invert(){
    RooUnfoldGenerate();
    RooUnfoldGenerateVariable();        
    mu_suite_start();
    mu_run_test(run_invert);
    return NULL;
}

char *test_bbb(){
    RooUnfoldGenerate();
    RooUnfoldGenerateVariable();        
    mu_suite_start();
    mu_run_test(run_bbb);
    return NULL;
}
