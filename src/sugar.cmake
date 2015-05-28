# This file generated automatically by:
#   generate_sugar_files.py
# see wiki for more info:
#   https://github.com/ruslo/sugar/wiki/Collecting-sources

if(DEFINED SRC_SUGAR_CMAKE_)
  return()
else()
  set(SRC_SUGAR_CMAKE_ 1)
endif()

include(sugar_files)
include(sugar_include)

sugar_include(gbm)
sugar_include(io)
sugar_include(learner)
sugar_include(sync)
sugar_include(tree)
sugar_include(utils)

sugar_files(
    XGBOOST_EXE_SOURCE
    data.h
    xgboost_main.cpp
)
