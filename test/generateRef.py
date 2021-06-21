from ROOT import TFile
import ROOT
import os

def get_combination(parms, parms_name):
    combined_parms = []
    if len(parms_name) == 0:
        return [' ']
    cur_parm = parms_name[0]
    parms_name.pop(0)
    perv_comb = get_combination(parms, parms_name)
    for parm_val in parms[cur_parm]:
        for comb in perv_comb:
            new_comb = comb + " " + cur_parm + "=" + parm_val
            combined_parms.append(new_comb)
    return combined_parms

def get_unfold(f):
    unfold = f.Get("unfold")
    h_unfolded = unfold.Hreco()
    u = ROOT.TVector(h_unfolded.GetNbinsX())
    for i in range(h_unfolded.GetNbinsX()):
        u[i] = h_unfolded.GetBinContent(i+1)

    return u


def get_field():
    filename = "RooUnfoldTest.root"
    f =  TFile.Open(filename,"READ")
    u = get_unfold(f)
    # Add other fields you need
    return u


def write_field(all_output, ref_file_name):
    with open(ref_file_name, 'w') as f:
        for u in all_output:
            for i in range(u.GetNrows()):
                f.write(str(u[i]))
                f.write('\n')

if __name__ == '__main__':

    parms = {
        'method': ['1', '2'],
        'ftestx': ['2', '3']
    }
    ref_file_name = "../ref/put_test_name_here.ref"

    all_output = []
    combined_parm = get_combination(parms, list(parms.keys()))
    for single_parm in combined_parm:
        command_str = "../build/RooUnfoldTest " +  single_parm
        print(command_str)
        os.system(command_str)
        u = get_field()
        all_output.append(u)
    
    write_field(all_output, ref_file_name)
    os.system("rm RooUnfoldTest.root")
    os.system("rm RooUnfoldTest.ps")