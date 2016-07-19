cmake_minimum_required(VERSION 3.0)

include("cmake/HunterGate.cmake")

### Hunter snapshot that will be used ###
HunterGate(
  URL "https://github.com/ruslo/hunter/archive/v0.12.30.tar.gz"
  SHA1 "4069d2d2c6021784f1a786b13cc6192e50303782"
  )

project(xgboost VERSION 0.1)

# -Wno-narrowing  = Don't warn about type narrowing
include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG(-Wno-c++11-narrowing COMPILER_SUPPORTS_NO_NARROWING)
if(COMPILER_SUPPORTS_NO_NARROWING)
  set(CMAKE_CXX_FLAGS    "${CMAKE_CXX_FLAGS} -Wno-c++11-narrowing -Wno-narrowing")
endif()

### Import sugar for source collection ###
hunter_add_package(Sugar)
include("${SUGAR_ROOT}/cmake/Sugar")
include(sugar_include)
include(CheckLibraryExists)

string(COMPARE EQUAL "${CMAKE_GENERATOR}" "Xcode" is_xcode)

# The various compiler checks take > 10 seconds on ios "Try OpenMP CXX flag = [-openmp]" in xcode
# TODO: Investigate why this is so much slower with ios toolchain
if(NOT is_xcode) 
  find_package( OpenMP )
  if(OPENMP_FOUND)
    message("OPENMP FOUND")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
  endif()
endif()

sugar_include(.)

option(SKIP_INSTALL "Skip the package install" OFF)
option(XGBOOST_USE_BOOST "Use boost serialization" ON)
option(XGBOOST_USE_HALF "Support half precision floating point storage" ON)

add_subdirectory(src)
