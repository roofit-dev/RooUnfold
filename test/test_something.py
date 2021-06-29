from test_utils import perform_test

if __name__ == '__main__':
    parms = {
        'method': ['1', '2'],
        'ftestx': ['2', '3']
    }
    ref_file_name = "../ref/something.ref"
    test_name = 'something'
    field_to_compare = ['unfold']
    perform_test(parms, ref_file_name, test_name, field_to_compare)
