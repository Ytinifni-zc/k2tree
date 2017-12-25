file(REMOVE_RECURSE
  "tests_utils.pdb"
  "tests_utils"
)

# Per-language clean rules from dependency scanning.
foreach(lang )
  include(CMakeFiles/tests_utils.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
