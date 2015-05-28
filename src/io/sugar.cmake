# This file generated automatically by:
#   generate_sugar_files.py
# see wiki for more info:
#   https://github.com/ruslo/sugar/wiki/Collecting-sources

if(DEFINED SRC_IO_SUGAR_CMAKE_)
  return()
else()
  set(SRC_IO_SUGAR_CMAKE_ 1)
endif()

include(sugar_files)

sugar_files(
    XGBOOST_SOURCE
    dmlc_simple.cpp
    io.cpp
    io.h
    libsvm_parser.h
    page_dmatrix-inl.hpp
    page_fmatrix-inl.hpp
    simple_dmatrix-inl.hpp
    simple_fmatrix-inl.hpp
    sparse_batch_page.h
)
