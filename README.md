# NewNoName

строка компиляции (в будущем будет изменяться):

g++ -I include/ -I include/GL/ -I include/MyGeometry/ -I include/Objects/ main.cpp include/StandartIncludes.cpp include/InitOpenGL.cpp include/OpenGLEventHandler.cpp include/MyBaseOperations.cpp include/DrawingFunctions.cpp include/MyGeometry/MyMatrixes.cpp include/MyGeometry/MyAngle.cpp include/MyGeometry/MyFlatAngle.cpp include/MyGeometry/MyPoint.cpp include/MyGeometry/MySegment.cpp include/MyGeometry/MyLine.cpp include/MyGeometry/MyRectan.cpp include/MyGeometry/MyTriangle.cpp include/MyGeometry/MyPolygon.cpp include/MyGeometry/MyCircle.cpp include/MyGeometry/MyGeometry.cpp include/MyGeometry/MyComplexShapes.cpp include/Objects/MyObject.cpp include/Objects/objects.cpp -O2 -o WindowsBuild/engine -framework GLUT -framework OpenGL

# Build

Unix (Linux/Mac):
```
cd build
cmake ..
make install
```
(btw, you can use<br>make -j *numOfThreads* install<br>for multithreading) 
