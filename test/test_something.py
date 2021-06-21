from generateRef import *
import os

def compare(all_output, ref_file_name, test_name):
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
            if abs(u[i] - r[ctr]) > 0.01:
                print("Error in {} {} as {} is not {}".format(test_name, i, u[i], r[i]))
                return 1
            ctr += 1
    return 0

if __name__ == '__main__':

    parms = {
        'method': ['1', '2'],
        'ftestx': ['2', '3']
    }
    ref_file_name = "../ref/something.ref"
    test_name = 'something'
    all_output = []
    combined_parm = get_combination(parms, list(parms.keys()))
    for single_parm in combined_parm:
        command_str = "../build/RooUnfoldTest " +  single_parm
        os.system(command_str)
        u = get_field("RooUnfoldTest.root")
        all_output.append(u)
        os.system("rm RooUnfoldTest.root")
        os.system("rm RooUnfoldTest.ps")

    if compare(all_output, ref_file_name, test_name) == 1:
        print("Test failed")
        exit(1)
