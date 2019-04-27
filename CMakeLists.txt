################################################################################
# Project: RooUnfold
################################################################################

cmake_minimum_required(VERSION 2.8)

find_package(AnalyissBase QUIET)

find_package( ROOT COMPONENTS Tree Unfold Matrix Hist RIO MathCore Physics)

file(GLOB RooUnfoldLinkDef src/*_LinkDef.h)
file(GLOB RooUnfoldSources src/*.cxx)
file(GLOB RooUnfoldHeaders src/*.h)
list(REMOVE_ITEM RooUnfoldHeaders ${RooUnfoldLinkDef})
  
if(NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/src/bayes_c.for)
  message("disabling d'Agostini implementation")
  file(GLOB RooUnfoldDagostini src/RooUnfoldDagostini.*)
  list(REMOVE_ITEM RooUnfoldHeaders ${RooUnfoldDagostini})
  list(REMOVE_ITEM RooUnfoldSources ${RooUnfoldDagostini})
endif()

execute_process( COMMAND ln -sf ${RooUnfoldHeaders} -t ${CMAKE_CURRENT_BINARY_DIR} )

file(GLOB PythonTests "examples/*.py")

if(${AnalysisBase_FOUND})
  atlas_subdir( RooUnfold )
  
  atlas_add_root_dictionary( RooUnfold _dictSource
    ROOT_HEADERS
    ${RooUnfoldHeaders}
    ${RooUnfoldLinkDef})
  
  atlas_add_library( RooUnfold
    ${RooUnfoldHeaders} ${RooUnfoldSources} ${_dictSource}
    PUBLIC_HEADERS RooUnfold
    PRIVATE_INCLUDE_DIRS ${ROOT_INCLUDE_DIRS}
    PRIVATE_LINK_LIBRARIES ${ROOT_LIBRARIES})
else()
  # register all the files and directories
  include_directories ("${CMAKE_CURRENT_SOURCE_DIR}/src")
  include_directories ("${ROOT_INCLUDE_DIRS}")

  # generate the dictionary source code
  include(${ROOT_USE_FILE})
  ROOT_GENERATE_DICTIONARY(G__RooUnfold ${RooUnfoldHeaders} LINKDEF ${RooUnfoldLinkDef})

  # register the shared object to include both sources and dictionaries
  add_library( RooUnfold SHARED ${RooUnfoldSources} G__RooUnfold.cxx)
 
  # link everything together at the end
  target_link_libraries( RooUnfold ${ROOT_LIBRARIES} )
  
  # Add all targets to the build-tree export set
  export(TARGETS RooUnfold FILE "${PROJECT_BINARY_DIR}/RooUnfoldTargets.cmake")
  
  # Export the package for use from the build-tree
  # (this registers the build-tree with a global CMake-registry)
  export(PACKAGE RooUnfold)
  
  set(CONF_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}" "${PROJECT_BINARY_DIR}")
  set(CONF_LIBRARY_DIRS "${PROJECT_BINARY_DIR}")
  set(CONF_LIBRARIES    RooUnfold)
  configure_file(RooUnfoldConfig.cmake.in
    "${PROJECT_BINARY_DIR}/RooUnfoldConfig.cmake" @ONLY)
  
  # Install the RooUnfoldConfig.cmake and RooUnfoldConfigVersion.cmake
  install(FILES
    "${PROJECT_BINARY_DIR}/${CMAKE_FILES_DIRECTORY}/RooUnfoldConfig.cmake"
    "${PROJECT_BINARY_DIR}/RooUnfoldConfigVersion.cmake"
    DESTINATION "${PROJECT_SOURCE_DIR}" COMPONENT dev)

  include(CTest)
  enable_testing()  
endif()
  
foreach(TestScript ${PythonTests})
  get_filename_component(TestName ${TestScript} NAME_WE)
  add_test( NAME ${TestName} COMMAND python ${TestScript})
endforeach()
