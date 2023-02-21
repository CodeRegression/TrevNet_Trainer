#--------------------------------------------------------
# CMake for generating TrevNet_TrainerLib Testing Suite
#
# @author: Wild Boar
#
# Date Created: 2023-02-20
#--------------------------------------------------------

# Add Google Test to the test group
find_package(GTest REQUIRED)

# Setup the includes
include_directories("../")

# Add the UnitTestLib library to the folder
add_library(UnitTestLib STATIC IMPORTED)
set_target_properties(UnitTestLib PROPERTIES
    IMPORTED_LOCATION "${LIBRARY_BASE}/UnitTestLib/build/UnitTestLib/libUnitTestLib.a"
    INTERFACE_INCLUDE_DIRECTORIES "${LIBRARY_BASE}/UnitTestLib"
)

# Create the executable
add_executable (TrevNet_TrainerTests
	Tests/Example_Tests.cpp
	Tests/NetworkFactory_Tests.cpp
)

# Add link libraries
target_link_libraries(TrevNet_TrainerTests TrevNet_TrainerLib TrevNetLib NVLib ${OpenCV_LIBS} UnitTestLib GTest::Main)

# Find the associated unit tests
gtest_discover_tests(TrevNet_TrainerTests)
