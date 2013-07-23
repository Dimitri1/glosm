# Install script for directory: /home/dimitri/Dropbox/trc_simulator_8/glosm/libglosm-client

# Set the install prefix
IF(NOT DEFINED CMAKE_INSTALL_PREFIX)
  SET(CMAKE_INSTALL_PREFIX "/usr/local")
ENDIF(NOT DEFINED CMAKE_INSTALL_PREFIX)
STRING(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
IF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  IF(BUILD_TYPE)
    STRING(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  ELSE(BUILD_TYPE)
    SET(CMAKE_INSTALL_CONFIG_NAME "")
  ENDIF(BUILD_TYPE)
  MESSAGE(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
ENDIF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)

# Set the component getting installed.
IF(NOT CMAKE_INSTALL_COMPONENT)
  IF(COMPONENT)
    MESSAGE(STATUS "Install component: \"${COMPONENT}\"")
    SET(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  ELSE(COMPONENT)
    SET(CMAKE_INSTALL_COMPONENT)
  ENDIF(COMPONENT)
ENDIF(NOT CMAKE_INSTALL_COMPONENT)

# Install shared libraries without execute permission?
IF(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  SET(CMAKE_INSTALL_SO_NO_EXE "1")
ENDIF(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/glosm" TYPE FILE FILES
    "/home/dimitri/Dropbox/trc_simulator_8/glosm/libglosm-client/glosm/CheckGL.hh"
    "/home/dimitri/Dropbox/trc_simulator_8/glosm/libglosm-client/glosm/FirstPersonViewer.hh"
    "/home/dimitri/Dropbox/trc_simulator_8/glosm/libglosm-client/glosm/GeometryLayer.hh"
    "/home/dimitri/Dropbox/trc_simulator_8/glosm/libglosm-client/glosm/GeometryTile.hh"
    "/home/dimitri/Dropbox/trc_simulator_8/glosm/libglosm-client/glosm/GPXLayer.hh"
    "/home/dimitri/Dropbox/trc_simulator_8/glosm/libglosm-client/glosm/GPXTile.hh"
    "/home/dimitri/Dropbox/trc_simulator_8/glosm/libglosm-client/glosm/Layer.hh"
    "/home/dimitri/Dropbox/trc_simulator_8/glosm/libglosm-client/glosm/MercatorProjection.hh"
    "/home/dimitri/Dropbox/trc_simulator_8/glosm/libglosm-client/glosm/OrthoViewer.hh"
    "/home/dimitri/Dropbox/trc_simulator_8/glosm/libglosm-client/glosm/Projection.hh"
    "/home/dimitri/Dropbox/trc_simulator_8/glosm/libglosm-client/glosm/Renderable.hh"
    "/home/dimitri/Dropbox/trc_simulator_8/glosm/libglosm-client/glosm/SphericalProjection.hh"
    "/home/dimitri/Dropbox/trc_simulator_8/glosm/libglosm-client/glosm/TerrainLayer.hh"
    "/home/dimitri/Dropbox/trc_simulator_8/glosm/libglosm-client/glosm/TerrainTile.hh"
    "/home/dimitri/Dropbox/trc_simulator_8/glosm/libglosm-client/glosm/Tile.hh"
    "/home/dimitri/Dropbox/trc_simulator_8/glosm/libglosm-client/glosm/TileManager.hh"
    "/home/dimitri/Dropbox/trc_simulator_8/glosm/libglosm-client/glosm/VertexBuffer.hh"
    "/home/dimitri/Dropbox/trc_simulator_8/glosm/libglosm-client/glosm/Viewer.hh"
    "/home/dimitri/Dropbox/trc_simulator_8/glosm/libglosm-client/../viewer/trafic-simulation/GPXWriter.hh"
    "/home/dimitri/Dropbox/trc_simulator_8/glosm/libglosm-client/../viewer/MyGlobalVariables.hh"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/glosm/util" TYPE FILE FILES "/home/dimitri/Dropbox/trc_simulator_8/glosm/libglosm-client/glosm/util/gl.h")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  IF(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libglosm-client.so")
    FILE(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libglosm-client.so"
         RPATH "")
  ENDIF(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libglosm-client.so")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES "/home/dimitri/Dropbox/trc_simulator_8/glosm/libglosm-client/libglosm-client.so")
  IF(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libglosm-client.so")
    FILE(RPATH_REMOVE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libglosm-client.so")
    IF(CMAKE_INSTALL_DO_STRIP)
      EXECUTE_PROCESS(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libglosm-client.so")
    ENDIF(CMAKE_INSTALL_DO_STRIP)
  ENDIF(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libglosm-client.so")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

