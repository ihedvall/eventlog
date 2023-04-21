include (FetchContent)
FetchContent_Declare(workflowlib
        GIT_REPOSITORY https://github.com/ihedvall/workflowlib.git
        GIT_TAG HEAD)

set(WORKFLOW_DOC OFF)
set(WORKFLOW_TEST OFF)
set(WORKFLOW_TOOL ON)

FetchContent_MakeAvailable(workflowlib)
message(STATUS "WORKFLOW Populated: " ${workflowlib_POPULATED})
message(STATUS "WORKFLOW Source Dir: " ${workflowlib_SOURCE_DIR})
message(STATUS "WORKFLOW Binary Dir: " ${workflowlib_BINARY_DIR})
