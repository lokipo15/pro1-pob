# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Release")
  file(REMOVE_RECURSE
  "CMakeFiles/PacmanGame_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/PacmanGame_autogen.dir/ParseCache.txt"
  "PacmanGame_autogen"
  )
endif()
