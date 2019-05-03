cmake_minimum_required(VERSION 3.13.4)
project(NewNoName VERSION 0.01 LANGUAGES CXX)

set(INC "include")
set(GEOM "${INC}/MyGeometry")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")

set(OpenGL_USE_STATIC_LIBS OFF)
set(GLUT_USE_STATIC_LIBS OFF)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

include_directories("${OpenGL_INCLUDE_DIRS}/" "${GLUT_INCLUDE_DIRS}/" "${INC}/" "${GEOM}/" "${INC}/Objects/")

add_executable(engine
	main.cpp
	include/StandartIncludes.cpp
	include/InitOpenGL.cpp include/OpenGLEventHandler.cpp
	include/OpenGLEventHandler.cpp
	include/DrawingFunctions.cpp
	${GEOM}/MyMatrixes.cpp
	${GEOM}/MyAngle.cpp
	${GEOM}/MyFlatAngle.cpp
	${GEOM}/MyPoint.cpp
	${GEOM}/MySegment.cpp
	${GEOM}/MyLine.cpp
	${GEOM}/MyRectan.cpp
	${GEOM}/MyTriangle.cpp
	${GEOM}/MyPolygon.cpp
	${GEOM}/MyCircle.cpp
	${GEOM}/MyGeometry.cpp
	${GEOM}/MyComplexShapes.cpp
	include/Objects/MyObject.cpp
	include/Objects/objects.cpp
)

target_link_libraries(engine ${GLUT_LIBRARIES} ${OpenGL_LIBRARIES})
