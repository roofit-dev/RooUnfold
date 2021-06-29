from test_utils import *

if __name__ == '__main__':

    parms = {
        'method': ['1', '2'],
        'ftestx': ['2', '3']
    }
    ref_file_name = "../ref/put_test_name_here.ref"

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
