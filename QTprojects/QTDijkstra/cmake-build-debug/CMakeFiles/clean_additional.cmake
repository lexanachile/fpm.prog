# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\QTDijkstra_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\QTDijkstra_autogen.dir\\ParseCache.txt"
  "QTDijkstra_autogen"
  )
endif()
