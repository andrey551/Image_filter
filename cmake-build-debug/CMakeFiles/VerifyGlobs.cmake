# CMAKE generated file: DO NOT EDIT!
# Generated by CMake Version 3.24
cmake_policy(SET CMP0009 NEW)

# sources at CMakeLists.txt:3 (file)
file(GLOB_RECURSE NEW_GLOB FOLLOW_SYMLINKS LIST_DIRECTORIES false "C:/Users/Never/CLionProjects/lab5/filter/*.asm")
set(OLD_GLOB
  "C:/Users/Never/CLionProjects/lab5/filter/pixel_transform.asm"
  )
if(NOT "${NEW_GLOB}" STREQUAL "${OLD_GLOB}")
  message("-- GLOB mismatch!")
  file(TOUCH_NOCREATE "C:/Users/Never/CLionProjects/lab5/cmake-build-debug/CMakeFiles/cmake.verify_globs")
endif()

# sources at CMakeLists.txt:3 (file)
file(GLOB_RECURSE NEW_GLOB FOLLOW_SYMLINKS LIST_DIRECTORIES false "C:/Users/Never/CLionProjects/lab5/header/*.h")
set(OLD_GLOB
  "C:/Users/Never/CLionProjects/lab5/header/errors_list.h"
  "C:/Users/Never/CLionProjects/lab5/header/file.h"
  "C:/Users/Never/CLionProjects/lab5/header/header.h"
  "C:/Users/Never/CLionProjects/lab5/header/image.h"
  "C:/Users/Never/CLionProjects/lab5/header/stat.h"
  "C:/Users/Never/CLionProjects/lab5/header/utils.h"
  )
if(NOT "${NEW_GLOB}" STREQUAL "${OLD_GLOB}")
  message("-- GLOB mismatch!")
  file(TOUCH_NOCREATE "C:/Users/Never/CLionProjects/lab5/cmake-build-debug/CMakeFiles/cmake.verify_globs")
endif()

# sources at CMakeLists.txt:3 (file)
file(GLOB_RECURSE NEW_GLOB FOLLOW_SYMLINKS LIST_DIRECTORIES false "C:/Users/Never/CLionProjects/lab5/src/*.c")
set(OLD_GLOB
  "C:/Users/Never/CLionProjects/lab5/src/file.c"
  "C:/Users/Never/CLionProjects/lab5/src/header.c"
  "C:/Users/Never/CLionProjects/lab5/src/image.c"
  "C:/Users/Never/CLionProjects/lab5/src/index.c"
  "C:/Users/Never/CLionProjects/lab5/src/utils.c"
  )
if(NOT "${NEW_GLOB}" STREQUAL "${OLD_GLOB}")
  message("-- GLOB mismatch!")
  file(TOUCH_NOCREATE "C:/Users/Never/CLionProjects/lab5/cmake-build-debug/CMakeFiles/cmake.verify_globs")
endif()
