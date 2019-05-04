cmake_minimum_required(VERSION 3.0)
project(NewNoName VERSION 0.01 LANGUAGES CXX)

set(INC "include")
set(GEOM "${INC}/MyGeometry")
set(OBJ "${INC}/Objects")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")

set(OpenGL_USE_STATIC_LIBS OFF)
set(GLUT_USE_STATIC_LIBS OFF)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

message("GLUTlib: ${GLUT_LIBRARY}")
message("OpenGLlib: ${OPENGL_LIBRARIES}")
message("dirs: ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS}")

include_directories("${INC}/" "${GEOM}/" "${INC}/Objects/")

add_executable(engine
	main.cpp
	${INC}/StandartIncludes.cpp
	${INC}/InitOpenGL.cpp
	${INC}/OpenGLEventHandler.cpp
	${INC}/MyBaseOperations.cpp
	${INC}/DrawingFunctions.cpp
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
	${OBJ}/MyObject.cpp
	${OBJ}/objects.cpp
)

target_link_libraries(engine ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})

message("source dir: ${CMAKE_SOURCE_DIR}")

install(TARGETS engine DESTINATION ${CMAKE_SOURCE_DIR}/WindowsBuild)
