######################################################################################
# Build function for main library
######################################################################################

IF(NOT WIN32)
  FIND_PACKAGE(libusb-1.0)
  IF(LIBUSB_1_FOUND)
    INCLUDE_DIRECTORIES(${LIBUSB_1_INCLUDE_DIRS})
    SET(SRCS nputil_libusb1.c)
    BUILDSYS_BUILD_LIB(
      NAME nputil_libusb1
      SOURCES "${SRCS}"
      CXX_FLAGS FALSE
      LINK_LIBS ${LIBUSB_1_LIBRARIES}
      LINK_FLAGS FALSE
      DEPENDS FALSE
      SHOULD_INSTALL TRUE
      VERSION "${LIBNPUTIL_VERSION}"
      )
  ELSE()
    MESSAGE(STATUS "NOT BUILD LIBUSB-1.0 UTILITY LIBRARY - LIBUSB-1.0 NOT FOUND")
  ENDIF()
  FIND_PACKAGE(libusb)
  IF(LIBUSB_FOUND)
    INCLUDE_DIRECTORIES(${LIBUSB_INCLUDE_DIRS})
    SET(SRCS nputil_libusb.c)
    BUILDSYS_BUILD_LIB(
      NAME nputil_libusb
      SOURCES "${SRCS}"
      CXX_FLAGS FALSE
      LINK_LIBS ${LIBUSB_LIBRARIES}
      LINK_FLAGS FALSE
      DEPENDS FALSE
      SHOULD_INSTALL TRUE
      VERSION "${LIBNPUTIL_VERSION}"
      )
  ELSE()
    MESSAGE(STATUS "NOT BUILD LIBUSB-0.1 UTILITY LIBRARY - LIBUSB-0.1 NOT FOUND")
  ENDIF()  
ELSE()
  # Find Windows DDK?
ENDIF()

