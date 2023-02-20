#--------------------------------------------------------
# CMake for generating the main executable
#
# @author: Wild Boar
#
# Date Created: 2023-02-20
#--------------------------------------------------------

# Setup the includes
include_directories("../")

# Create the executable
add_executable(TrevNet_Trainer
    Engine.cpp
    Source.cpp
)

# Add link libraries                               
target_link_libraries(TrevNet_Trainer TrevNet_TrainerLib  NVLib ${OpenCV_LIBS})

# Copy Resources across
add_custom_target(resource_copy ALL
	COMMAND cmake -E copy_directory ${CMAKE_SOURCE_DIR}/Resources ${CMAKE_BINARY_DIR}/TrevNet_Trainer 
    DEPENDS ${MY_TARGET}
)
