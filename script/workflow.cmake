
include (FetchContent)
FetchContent_Declare(workflowapp
        GIT_REPOSITORY https://github.com/ihedvall/workflow.git
        GIT_TAG HEAD)


FetchContent_MakeAvailable(workflowapp)
message(STATUS "WORKFLOW_APP Populated: " ${workflowapp_POPULATED})
message(STATUS "WORKFLOW_APP Source Dir: " ${workflowapp_SOURCE_DIR})
message(STATUS "WORKFLOW_APP Binary Dir: " ${workflowapp_BINARY_DIR})