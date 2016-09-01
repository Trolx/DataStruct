cmake_minimum_required(VERSION 3.3)
project(DataStructLearn)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    .idea/.name
    .idea/DataStructLearn.iml
    .idea/encodings.xml
    .idea/misc.xml
    .idea/modules.xml
    .idea/vcs.xml
    .idea/workspace.xml
    LinkedListLearn/.idea/.name
    LinkedListLearn/.idea/encodings.xml
    LinkedListLearn/.idea/LinkedListLearn.iml
    LinkedListLearn/.idea/misc.xml
    LinkedListLearn/.idea/modules.xml
    LinkedListLearn/.idea/vcs.xml
    LinkedListLearn/.idea/workspace.xml
    LinkedListLearn/LinkedListLearn/.idea/LinkedListLearn.iml
    LinkedListLearn/LinkedListLearn/.idea/misc.xml
    LinkedListLearn/LinkedListLearn/.idea/vcs.xml
    LinkedListLearn/LinkedListLearn/.idea/workspace.xml
    LinkedListLearn/CMakeLists.txt
    LinkedListLearn/DLinkList.c
    LinkedListLearn/main.cpp
    TreeLearn/.idea/.name
    TreeLearn/.idea/encodings.xml
    TreeLearn/.idea/misc.xml
    TreeLearn/.idea/modules.xml
    TreeLearn/.idea/TreeLearn.iml
    TreeLearn/.idea/workspace.xml
    TreeLearn/BinaryTree.cpp
    TreeLearn/CMakeLists.txt
    TreeLearn/main.cpp
    README.md)

add_executable(DataStructLearn ${SOURCE_FILES})