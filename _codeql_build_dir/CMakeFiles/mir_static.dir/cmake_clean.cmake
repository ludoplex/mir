file(REMOVE_RECURSE
  "libmir_static.a"
  "libmir_static.pdb"
)

# Per-language clean rules from dependency scanning.
foreach(lang C)
  include(CMakeFiles/mir_static.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
