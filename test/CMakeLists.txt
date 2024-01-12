find_package(GTest) # GoogleTest

if (GTest_FOUND)
  enable_testing()

  file(GLOB TEST_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
  add_executable(OptibitsTests ${TEST_FILES})
  target_link_libraries(OptibitsTests Optibits::Optibits GTest::gtest GTest::gtest_main)

  gtest_discover_tests(OptibitsTests WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR})

endif ()