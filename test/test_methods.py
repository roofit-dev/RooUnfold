from test_utils import perform_test

if __name__ == '__main__':
    parms = {
        'method': ['1', '2', '3', '4', '5']
    }
    ref_file_name = "../ref/test_methods.ref"
    test_name = 'test_methods'
    field_to_compare = ['unfold']
    perform_test(parms, ref_file_name, test_name, field_to_compare)
