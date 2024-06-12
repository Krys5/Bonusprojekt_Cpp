# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\bonusprojekt_v02_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\bonusprojekt_v02_autogen.dir\\ParseCache.txt"
  "bonusprojekt_v02_autogen"
  )
endif()
