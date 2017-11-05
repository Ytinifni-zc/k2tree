ExternalProject_Add(
    gtest_external
    GIT_REPOSITORY https://github.com/google/googletest.git
    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=<INSTALL_DIR>
    UPDATE_COMMAND ""
)
ExternalProject_Get_Property(gtest_external source_dir install_dir)

file(MAKE_DIRECTORY "${install_dir}/include")

set(${package_found_prefix}_CMAKE_DEP test_external)
set(${package_found_prefix}_LIBRARIES "${install_dir}/lib/libgtest.a"
                                        "${install_dir}/lib/libgtest_main.a")
set(${package_found_prefix}_INCLUDE_DIRS "${install_dir}/include")