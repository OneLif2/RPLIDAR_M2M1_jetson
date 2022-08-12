file(REMOVE_RECURSE
  "libslamware_core_platform.pdb"
  "libslamware_core_platform.a"
)

# Per-language clean rules from dependency scanning.
foreach(lang )
  include(CMakeFiles/slamware_core_platform.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
