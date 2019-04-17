################################################################################
# Project: RooUnfold
################################################################################

find_package( ROOT COMPONENTS Tree Unfold Matrix Hist RIO MathCore Physics)

file(GLOB RooUnfoldLinkDef src/*_LinkDef.h)
file(GLOB RooUnfoldSources src/*.cxx)
file(GLOB RooUnfoldHeaders src/*.h)
file(GLOB RooUnfoldDagostini src/RooUnfoldDagostini.*)
list(REMOVE_ITEM RooUnfoldHeaders ${RooUnfoldLinkDef})
list(REMOVE_ITEM RooUnfoldHeaders ${RooUnfoldDagostini})
list(REMOVE_ITEM RooUnfoldSources ${RooUnfoldDagostini})

atlas_subdir( RooUnfold )

#execute_process(
#  COMMAND mkdir -p ${CMAKE_CURRENT_SOURCE_DIR}/RooUnfold
#  COMMAND ln -s ${RooUnfoldHeaders} -t ${CMAKE_CURRENT_SOURCE_DIR}/RooUnfold
#)

atlas_add_root_dictionary( RooUnfold _dictSource
  ROOT_HEADERS
  ${RooUnfoldHeaders}
  ${RooUnfoldLinkDef})

atlas_add_library( RooUnfold
  ${RooUnfoldHeaders} ${RooUnfoldSources} ${_dictSource}
  PUBLIC_HEADERS RooUnfold
  PRIVATE_INCLUDE_DIRS ${ROOT_INCLUDE_DIRS}
  PRIVATE_LINK_LIBRARIES ${ROOT_LIBRARIES})
