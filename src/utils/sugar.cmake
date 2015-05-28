# This file generated automatically by:
#   generate_sugar_files.py
# see wiki for more info:
#   https://github.com/ruslo/sugar/wiki/Collecting-sources

if(DEFINED SRC_UTILS_SUGAR_CMAKE_)
  return()
else()
  set(SRC_UTILS_SUGAR_CMAKE_ 1)
endif()

include(sugar_files)

sugar_files(
    XGBOOST_SOURCE
    base64-inl.h
    bitmap.h
    config.h
    fmap.h
    group_data.h
    io.h
    iterator.h
    math.h
    omp.h
    quantile.h
    random.h
    thread.h
    thread_buffer.h
    utils.h
)
