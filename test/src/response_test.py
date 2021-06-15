import ROOT
from ROOT import TFile


def BuildRooUnfoldResponse(filename="response.root"):
    f =  TFile.Open(filename,"READ")
    h_response = f.Get("res")
    h_gen = f.Get("gen")
    h_sim = f.Get("sim")
    response = ROOT.RooUnfoldResponse(h_sim,h_gen,h_response)
    f.Close()
    return response
