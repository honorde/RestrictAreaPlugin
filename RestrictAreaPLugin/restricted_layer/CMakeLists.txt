cmake_minimum_required(VERSION 2.8.3)
project(restricted_layer)

find_package(catkin REQUIRED COMPONENTS

  costmap_2d
  dynamic_reconfigure
  roscpp
  rviz
)


catkin_package(

)

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)

set(CMAKE_AUTOMOC ON)

if(rviz_QT_VERSION VERSION_LESS "5")
  message(STATUS "Using Qt4 based on the rviz_QT_VERSION: ${rviz_QT_VERSION}")
  find_package(Qt4 ${rviz_QT_VERSION} EXACT REQUIRED QtCore QtGui)
 
  include(${QT_USE_FILE})
else()
  message(STATUS "Using Qt5 based on the rviz_QT_VERSION: ${rviz_QT_VERSION}")
  find_package(Qt5 ${rviz_QT_VERSION} EXACT REQUIRED Core Widgets)

  set(QT_LIBRARIES Qt5::Widgets)
endif()


add_definitions(-DQT_NO_KEYWORDS)

set(SRC_FILES
src/restricted_layer.cpp

)
add_library(${PROJECT_NAME} ${SRC_FILES})
target_link_libraries(${PROJECT_NAME} ${QT_LIBRARIES} ${catkin_LIBRARIES})

