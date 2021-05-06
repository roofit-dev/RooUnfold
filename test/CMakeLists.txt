add_library(tests
        src/generate_test.cxx
        src/response_test.cxx
        src/bayes_test.cxx
        src/svd_test.cxx
        src/tunfold_test.cxx
        src/invert_test.cxx
        src/bbb_test.cxx
        src/RooUnfold_unit_tests.cxx)
target_link_libraries(tests PUBLIC ROOT::Matrix ROOT::Core ROOT::Hist RooUnfold)