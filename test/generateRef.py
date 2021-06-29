import os
from test_utils import *

if __name__ == '__main__':

    parms = {
        'method': ['1', '2', '3', '4', '5']
    }
    ref_file_name = "../ref/something.ref"
    test_name = 'something'
    '''
        parms = {
        'addfakes': ['1']
    }
    ref_file_name = "../ref/test_fakes.ref"
    '''
    all_output = []
    combined_parm = get_combination(parms, list(parms.keys()))

    delete_files()
    for single_parm in combined_parm:
        command_str = "../build/RooUnfoldTest " +  single_parm
        os.system(command_str)
        u = get_field("RooUnfoldTest.root")
        all_output.append(u)
        delete_files()
    write_field(all_output, ref_file_name)
