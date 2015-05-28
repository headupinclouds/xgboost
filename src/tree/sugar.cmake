# This file generated automatically by:
#   generate_sugar_files.py
# see wiki for more info:
#   https://github.com/ruslo/sugar/wiki/Collecting-sources

if(DEFINED SRC_TREE_SUGAR_CMAKE_)
  return()
else()
  set(SRC_TREE_SUGAR_CMAKE_ 1)
endif()

include(sugar_files)

sugar_files(
    XGBOOST_SOURCE
    model.h
    param.h
    updater.cpp
    updater.h
    updater_basemaker-inl.hpp
    updater_colmaker-inl.hpp
    updater_distcol-inl.hpp
    updater_histmaker-inl.hpp
    updater_prune-inl.hpp
    updater_refresh-inl.hpp
    updater_skmaker-inl.hpp
    updater_sync-inl.hpp
)
