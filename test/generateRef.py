import os
from test_utils import *

if __name__ == '__main__':

    parms = {
        'bincorr': ['1'],
        'seed':['42']
    }
    ref_file_name = "../ref/test_correlation.ref"
    test_name = 'test_correlation'
    field_to_compare = ['uncertainty']
    '''
        parms = {
        'addfakes': ['1']
    }
    ref_file_name = "../ref/test_fakes.ref"

    parms = {
        'bincorr': ['1']
    }
    ref_file_name = "../ref/test_correlation.ref"
    test_name = 'test_correlation'
    field_to_compare = ['uncertainty']

    '''
    all_output = []
    combined_parm = get_combination(parms, list(parms.keys()))

    delete_files()
    for single_parm in combined_parm:
        command_str = "../build/RooUnfoldTest " +  single_parm
        os.system(command_str)
        u = get_field("RooUnfoldTest.root", field_to_compare)
        all_output.extend(u)
        delete_files()
    write_field(all_output, ref_file_name)
