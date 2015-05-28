# This file generated automatically by:
#   generate_sugar_files.py
# see wiki for more info:
#   https://github.com/ruslo/sugar/wiki/Collecting-sources

if(DEFINED SRC_LEARNER_SUGAR_CMAKE_)
  return()
else()
  set(SRC_LEARNER_SUGAR_CMAKE_ 1)
endif()

include(sugar_files)

sugar_files(
    XGBOOST_SOURCE
    dmatrix.h
    evaluation-inl.hpp
    evaluation.h
    helper_utils.h
    learner-inl.hpp
    objective-inl.hpp
    objective.h
)
