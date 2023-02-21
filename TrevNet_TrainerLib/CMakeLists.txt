#--------------------------------------------------------
# CMake for generating the TrevNet_TrainerLib
#
# @author: Wild Boar
#
# Date Created: 2023-02-20
#--------------------------------------------------------

# Setup include directories
include_directories("../" "${LIBRARY_BASE}/NVLib")

# Create Library
add_library (TrevNet_TrainerLib STATIC
	ArgUtils.cpp
	CodeDash.cpp
	Socket.cpp
	ProblemLoader.cpp
	NetworkFactory.cpp
	Evaluator.cpp
)
