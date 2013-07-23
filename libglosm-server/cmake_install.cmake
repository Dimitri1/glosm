# Install script for directory: /home/dimitri/Dropbox/trc_simulator_8/glosm/libglosm-server

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
    "/home/dimitri/Dropbox/trc_simulator_8/glosm/libglosm-server/glosm/BBox.hh"
    "/home/dimitri/Dropbox/trc_simulator_8/glosm/libglosm-server/glosm/DummyHeightmap.hh"
    "/home/dimitri/Dropbox/trc_simulator_8/glosm/libglosm-server/glosm/Exception.hh"
    "/home/dimitri/Dropbox/trc_simulator_8/glosm/libglosm-server/glosm/geomath.h"
    "/home/dimitri/Dropbox/trc_simulator_8/glosm/libglosm-server/glosm/Geometry.hh"
    "/home/dimitri/Dropbox/trc_simulator_8/glosm/libglosm-server/glosm/GeometryDatasource.hh"
    "/home/dimitri/Dropbox/trc_simulator_8/glosm/libglosm-server/glosm/GeometryOperations.hh"
    "/home/dimitri/Dropbox/trc_simulator_8/glosm/libglosm-server/glosm/GPXDatasource.hh"
    "/home/dimitri/Dropbox/trc_simulator_8/glosm/libglosm-server/glosm/Guard.hh"
    "/home/dimitri/Dropbox/trc_simulator_8/glosm/libglosm-server/glosm/HeightmapDatasource.hh"
    "/home/dimitri/Dropbox/trc_simulator_8/glosm/libglosm-server/glosm/id_map.hh"
    "/home/dimitri/Dropbox/trc_simulator_8/glosm/libglosm-server/glosm/Math.hh"
    "/home/dimitri/Dropbox/trc_simulator_8/glosm/libglosm-server/glosm/Misc.hh"
    "/home/dimitri/Dropbox/trc_simulator_8/glosm/libglosm-server/glosm/NonCopyable.hh"
    "/home/dimitri/Dropbox/trc_simulator_8/glosm/libglosm-server/glosm/OsmDatasource.hh"
    "/home/dimitri/Dropbox/trc_simulator_8/glosm/libglosm-server/glosm/osmtypes.h"
    "/home/dimitri/Dropbox/trc_simulator_8/glosm/libglosm-server/glosm/ParsingHelpers.hh"
    "/home/dimitri/Dropbox/trc_simulator_8/glosm/libglosm-server/glosm/PreloadedGPXDatasource.hh"
    "/home/dimitri/Dropbox/trc_simulator_8/glosm/libglosm-server/glosm/PreloadedXmlDatasource.hh"
    "/home/dimitri/Dropbox/trc_simulator_8/glosm/libglosm-server/glosm/SRTMDatasource.hh"
    "/home/dimitri/Dropbox/trc_simulator_8/glosm/libglosm-server/glosm/Timer.hh"
    "/home/dimitri/Dropbox/trc_simulator_8/glosm/libglosm-server/glosm/WayMerger.hh"
    "/home/dimitri/Dropbox/trc_simulator_8/glosm/libglosm-server/glosm/XMLParser.hh"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  IF(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libglosm-server.so")
    FILE(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libglosm-server.so"
         RPATH "")
  ENDIF(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libglosm-server.so")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES "/home/dimitri/Dropbox/trc_simulator_8/glosm/libglosm-server/libglosm-server.so")
  IF(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libglosm-server.so")
    IF(CMAKE_INSTALL_DO_STRIP)
      EXECUTE_PROCESS(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libglosm-server.so")
    ENDIF(CMAKE_INSTALL_DO_STRIP)
  ENDIF(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libglosm-server.so")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

