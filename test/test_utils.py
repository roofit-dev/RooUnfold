import os
import ROOT

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

def get_uncertainty(f):
    unfold = f.Get("unfold")
    h_unfolded = unfold.Hreco()
    u = ROOT.TVector(h_unfolded.GetNbinsX())
    for i in range(h_unfolded.GetNbinsX()):
        u[i] = h_unfolded.GetBinError(i+1)

    return u

def get_field(filename, field_to_compare = ['unfold']):
    global comparing_fields
    f =  ROOT.TFile.Open(filename,"READ")
    u = []
    for field in field_to_compare:
        if field in comparing_fields:
            tmp_u = comparing_fields[field](f)
            u.append(tmp_u)
        else:
            print("[ERROR] Specified field not present in the file for comparison")
            exit(1)

    return u


def write_field(all_output, ref_file_name):
    with open(ref_file_name, 'w') as f:
        for all_u in all_output:
            for u in all_u:
                for i in range(u.GetNrows()):
                    f.write(str(u[i]))
                    f.write('\n')


def delete_files():
    os.system("rm -f RooUnfoldTest.root")
    os.system("rm -f RooUnfoldTest.ps")


def compare(all_output, ref_file_name, test_name, allowed_difference):
    r = []
    with open(ref_file_name) as f:
        r = [float(line.rstrip()) for line in f]

    n = 0
    for u in all_output:
        n += u.GetNrows()

    if len(r) != n:
        return 1

    ctr = 0
    for u in all_output:
        for i in range(u.GetNrows()):
            if abs(u[i] - r[ctr]) > allowed_difference:
                print("Error in {} {} as {} is not {}".format(test_name, i, u[i], r[i]))
                return 1
            ctr += 1
    return 0

def perform_test(parms, ref_file_name, test_name, field_to_compare, allowed_difference = 1):
    all_output = []
    combined_parm = get_combination(parms, list(parms.keys()))
    for single_parm in combined_parm:
        command_str = "../build/RooUnfoldTest " +  single_parm
        os.system(command_str)
        u = get_field("RooUnfoldTest.root", field_to_compare)
        all_output.extend(u)
        os.system("rm RooUnfoldTest.root")
        os.system("rm RooUnfoldTest.ps")

    if compare(all_output, ref_file_name, test_name, allowed_difference) == 1:
        print("Test failed")
        exit(1)


comparing_fields = {"unfold": get_unfold,"uncertainty":get_uncertainty}
