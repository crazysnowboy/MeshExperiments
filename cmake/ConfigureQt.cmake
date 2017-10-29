# @see http://doc.qt.io/qt-5/cmake-manual.html
set(CMAKE_PREFIX_PATH "/usr/local/QT5.3.1/5.3/gcc_64/lib/cmake")

#--- Needed for GUI
find_package(Qt5Widgets REQUIRED)
include_directories(${Qt5Widgets_INCLUDE_DIRS})
list(APPEND LIBRARIES Qt5::Widgets)

#--- Needed for OpenGL
find_package(Qt5OpenGL REQUIRED)
include_directories(${Qt5OpenGL_INCLUDE_DIRS})
list(APPEND LIBRARIES Qt5::OpenGL)

#--- Needed for the QGLViewer library
find_package(Qt5Xml REQUIRED)
include_directories(${Qt5Xml_INCLUDE_DIRS})
list(APPEND LIBRARIES Qt5::Xml)

#--- Needed for the QGLViewer library
find_package(Qt5Svg REQUIRED)
include_directories(${Qt5Svg_INCLUDE_DIRS})
list(APPEND LIBRARIES Qt5::Svg)

