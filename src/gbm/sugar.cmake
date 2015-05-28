# This file generated automatically by:
#   generate_sugar_files.py
# see wiki for more info:
#   https://github.com/ruslo/sugar/wiki/Collecting-sources

if(DEFINED SRC_GBM_SUGAR_CMAKE_)
  return()
else()
  set(SRC_GBM_SUGAR_CMAKE_ 1)
endif()

include(sugar_files)

sugar_files(
    XGBOOST_SOURCE
    gblinear-inl.hpp
    gbm.cpp
    gbm.h
    gbtree-inl.hpp
)
