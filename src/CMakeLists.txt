include(sugar_include)

sugar_include(.)

### Always build xgboost as a library
add_library(xgboost ${XGBOOST_SOURCE} ${RABIT_SOURCE})

### Optionally build the executable 
option(XGBOOST_BUILD_EXAMPLES OFF)
if(XGBOOST_BUILD_EXAMPLES)
  message("XGBOOST_BUILD_EXAMPLES ${XGBOOST_BUILD_EXAMPLES}.......................................")
  add_executable(xgboost_main ${XGBOOST_EXE_SOURCE})
  target_link_libraries(xgboost_main xgboost)
endif()

### If you want to take advantage of boost serialization ...
if(XGBOOST_USE_BOOST)
  target_link_libraries(xgboost PRIVATE
	Boost::filesystem 
	Boost::system 
	Boost::serialization 
	Boost::iostreams
	)
endif()

if(XGBOOST_USE_HALF)
  target_link_libraries(xgboost PRIVATE half::half)
endif()

# Some platforms (e.g. Linux) need separate math library
check_library_exists(m pow "" LIB_M_REQUIRED)
if(LIB_M_REQUIRED)
  target_link_libraries(xgboost PRIVATE m)
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

include(CMakePackageConfigHelpers)

write_basic_package_version_file(
    "${version_config}" COMPATIBILITY SameMajorVersion
)

# Note: variable 'targets_export_name' used
configure_file("cmake/Config.cmake.in" "${project_config}" @ONLY)

install(
    TARGETS ${PROJECT_NAME}
    EXPORT "${targets_export_name}"
    LIBRARY DESTINATION "lib"
    ARCHIVE DESTINATION "lib"
    RUNTIME DESTINATION "bin"
    INCLUDES DESTINATION "${include_install_dir}/xgboost"
)

install(
    FILES
    ${XGBOOST_PUBLIC_HDR}
    DESTINATION "${include_install_dir}/xgboost"
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