include(sugar_include)

sugar_include(.)

### Always build xgboost as a library
add_library(xgboost ${XGBOOST_SOURCE} ${RABIT_SOURCE})

if(XGBOOST_DO_LEAN)
  target_compile_definitions(xgboost PUBLIC XGBOOST_DO_LEAN=1)
else()
  target_compile_definitions(xgboost PUBLIC XGBOOST_DO_LEAN=0)
endif()

### Optionally build the executable
option(XGBOOST_BUILD_EXAMPLES "Build xgboost examples" OFF)
if(XGBOOST_BUILD_EXAMPLES)
  message("XGBOOST_BUILD_EXAMPLES ${XGBOOST_BUILD_EXAMPLES}.......................................")
  add_executable(xgboost_main ${XGBOOST_EXE_SOURCE})
  target_link_libraries(xgboost_main xgboost)
endif()

### If you want to take advantage of boost serialization ...
if(XGBOOST_USE_BOOST)
  hunter_add_package(Boost COMPONENTS filesystem system serialization iostreams)
  find_package(Boost CONFIG REQUIRED filesystem system serialization iostreams)
  target_link_libraries(xgboost PUBLIC
  Boost::filesystem
  Boost::system
  Boost::serialization
  Boost::iostreams
  )
  target_compile_definitions(xgboost PUBLIC XGBOOST_USE_BOOST=1)
endif()

if(XGBOOST_USE_HALF)
  hunter_add_package(half)
  find_package(half CONFIG REQUIRED)
  target_link_libraries(xgboost PUBLIC half::half)
  target_compile_definitions(xgboost PUBLIC XGBOOST_SQUEEZE=1)
endif()

# Some platforms (e.g. Linux) need separate math library
check_library_exists(m pow "" LIB_M_REQUIRED)
if(LIB_M_REQUIRED)
  target_link_libraries(xgboost PUBLIC m)
endif()

message("=========SKIP_INSTALL========: ${SKIP_INSTALL}")
if(SKIP_INSTALL)
  return()
endif()

# install
set(generated_dir "${CMAKE_CURRENT_BINARY_DIR}/generated")
set(config_install_dir "lib/cmake/${PROJECT_NAME}")
set(version_config "${generated_dir}/${PROJECT_NAME}ConfigVersion.cmake")
set(project_config "${generated_dir}/${PROJECT_NAME}Config.cmake")
set(targets_export_name "${PROJECT_NAME}Targets")
set(namespace "${PROJECT_NAME}::")

set(include_install_dir "include")

include(CMakePackageConfigHelpers)

write_basic_package_version_file(
    "${version_config}" COMPATIBILITY SameMajorVersion
)

# Use variables:
#   * targets_export_name
#   * PROJECT_NAME
configure_package_config_file(
    "cmake/Config.cmake.in"
    "${project_config}"
    INSTALL_DESTINATION "${config_install_dir}"
)

install(
    TARGETS ${PROJECT_NAME}
    EXPORT "${targets_export_name}"
    LIBRARY DESTINATION "lib"
    ARCHIVE DESTINATION "lib"
    RUNTIME DESTINATION "bin"
    INCLUDES DESTINATION "${include_install_dir}/xgboost"
)

install(
    DIRECTORY
        "${PROJECT_SOURCE_DIR}/java"
        "${PROJECT_SOURCE_DIR}/subtree"
        "${PROJECT_SOURCE_DIR}/R-package"
        "${PROJECT_SOURCE_DIR}/src"
        "${PROJECT_SOURCE_DIR}/wrapper"
    DESTINATION "${include_install_dir}/xgboost"
    FILES_MATCHING PATTERN "*.h" PATTERN "*.hpp"
)

install(
    FILES "${project_config}" "${version_config}"
    DESTINATION "${config_install_dir}"
)

install(
    EXPORT "${targets_export_name}"
    NAMESPACE "${namespace}"
    DESTINATION "${config_install_dir}"
)
