#include <iostream>
#include <fstream>
#include <string>
#include "dbg.h"
#include "minunit.h"
using std::cout;
using std::endl;

#include "unittests.h"

int TestBayes(){
  auto u = BuildRooUnfoldBayes();
  int n = u.GetNrows();

  std::vector<float> r;
  std::ifstream ref("../ref/bayes.ref");
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


bool TestSVD(){
  auto u = BuildRooUnfoldSVD();
  int n = u.GetNrows();

  std::vector<float> r;
  std::ifstream ref("../ref/svd.ref");
  if (ref.is_open()){
    std::string line;
    while (getline(ref,line)){
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

bool TestInvert(){
  auto u = BuildRooUnfoldInvert();
  int n = u.GetNrows();

  std::vector<float> r;
  std::ifstream ref("../ref/invert.ref");
  if (ref.is_open()){
    std::string line;
    while (getline(ref,line)){
      r.push_back(std::stof(line));
    }
  ref.close();
  }
  for (int i=0; i<n; i++){
    check(EQ(u[i], r[i], 1), "error in matrix invert bin: %d as %f is not %f",i,u[i],r[i]);
  }
  
  return 1;
error:
  return -1;
}


bool TestBinByBin(){
  auto u = BuildRooUnfoldBinByBin();
  int n = u.GetNrows();

  std::vector<float> r;
  std::ifstream ref("../ref/bbb.ref");
  if (ref.is_open()){
    std::string line;
    while (getline(ref,line)){
      r.push_back(std::stof(line));
    }
  ref.close();
  }
  for (int i=0; i<n; i++){
    check(EQ(u[i], r[i], 1), "error in binbybin bin: %d as %f is not %f",i,u[i],r[i]);
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

char *all_tests(){
  RooUnfoldGenerate();
  mu_suite_start();
  mu_run_test(test_algs);
  return NULL;
}

RUN_TESTS(all_tests);

