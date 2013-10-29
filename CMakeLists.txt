cmake_minimum_required(VERSION 2.6)

project(arkanoiddemo)

include_directories ("${PROJECT_SOURCE_DIR}")
include_directories ("${PROJECT_SOURCE_DIR}/Box2D/Common")
include_directories ("${PROJECT_SOURCE_DIR}/Box2D")
add_subdirectory (Box2D)

include_directories ("${PROJECT_SOURCE_DIR}/freeglut")
add_subdirectory (freeglut)

set (EXTRA_LIBS ${EXTRA_LIBS} Box2D)

set(arkanoiddemo_SRCS
App.cpp
Arkanoid.cpp
Background.cpp
Ball.cpp
Bat.cpp
Brick.cpp
CoordSystem.cpp
Edges.cpp
EventClick.cpp
EventDispatcher.cpp
EventLoop.cpp
GameLayout.cpp
GraphicsService.cpp
GraphicsSprite.cpp
GraphicsTexture.cpp
Log.cpp
main.cpp
MathUtil.cpp
Matrix.cpp
PhysicsObject.cpp
PhysicsService.cpp
PngLoader.cpp
Rectangle.cpp
Resource.cpp
ScreenMaster.cpp
SoundService.cpp
StartLayout.cpp
StartScreen.cpp
TimeService.cpp
Vector3.cpp
Wall.cpp
App.h
Arkanoid.h
Background.h
Ball.h
Bat.h
Brick.h
Context.h
CommonLayout.h
CoordSystem.h
Edges.h
EventClick.h
EventDispatcher.h
Event.h
EventLoop.h
EventType.h
GameLayout.h
GraphicsService.h
GraphicsSprite.h
GraphicsTexture.h
IEventListener.h
Log.h
MathTypes.h
MathUtil.h
Matrix.h
PhysicsObject.h
PhysicsService.h
PngLoader.h
Rectangle.h
Rect.h
Resource.h
Screen.h
ScreenMaster.h
SoundService.h
StartLayout.h
StartScreen.h
TimeService.h
Types.h
Vector3.h
Wall.h
ICoordListener.h
IImageLoader.h
rapidxml.hpp
)

INCLUDE_DIRECTORIES( ${libpng_INCLUDE_DIR} )
INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR} )
add_executable (arkanoiddemo ${arkanoiddemo_SRCS})
target_link_libraries (arkanoiddemo  ${EXTRA_LIBS} ${Boost_LIBRARIES} ${libpng})
