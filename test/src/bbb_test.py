
from ROOT import TFile, TH1, TH1D, TCanvas
import ROOT
from response_test import BuildRooUnfoldResponse


def BuildRooUnfoldBinByBin(mode=0):
    filename = ''
    if mode == 0:
        filename = "build/response.root"
    elif mode == 1:
        filename = "build/response_var.root"
    f = TFile.Open(filename,"READ")
    h_meas = f.Get("meas")
    response = BuildRooUnfoldResponse(filename)
    unfold = ROOT.RooUnfoldBinByBin(response, h_meas)
    h_unfolded = unfold.Hreco()
    u = ROOT.TVector(h_unfolded.GetNbinsX())

    for i in range(h_unfolded.GetNbinsX()):
        u[i] = h_unfolded.GetBinContent(i+1)

    return u


def TestBinByBin(mode = 0):
    u = BuildRooUnfoldBinByBin(mode)
    n = u.GetNrows()
    r = []
    ref_name = ''
    if mode == 0:
        ref_name = "ref/bbb.ref"
    elif mode == 1:
        ref_name = "ref/bbb_var.ref"

    with open(ref_name) as f:
        r = [float(line.rstrip()) for line in f]

    for i in range(n):
        if abs(u[i] - r[i]) > 0.01:
            print("Error in binbybin {} as {} is not {}".format(i, u[i], r[i]))
            return 1
    return 0

if __name__ =="__main__":
    if TestBinByBin(0) == 1:
        print("binwise test of BinByBin failed")
        exit(1)
    if TestBinByBin(1) == 1:
        print("binwise test of variable binning in BinByBin failed")
        exit(1)
