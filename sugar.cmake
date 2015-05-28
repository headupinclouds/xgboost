# This file generated automatically by:
#   generate_sugar_files.py
# see wiki for more info:
#   https://github.com/ruslo/sugar/wiki/Collecting-sources

# Eventually this should go in rabbit, but keep it out of the subtree for now

if(DEFINED SRC_RABIT_CMAKE_)
  return()
else()
  set(SRC_RABIT_CMAKE_ 1)
endif()

include(sugar_files)
include(sugar_include)

### For now we just include the dummy engine to support initial testing
sugar_files(
    RABIT_SOURCE
    subtree/rabit/include/rabit.h
    subtree/rabit/include/rabit_serializable.h
    subtree/rabit/include/rabit/engine.h
    subtree/rabit/src/engine_empty.cc
)
