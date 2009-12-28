######################################################################################
# Build function for main library
######################################################################################

IF(NOT WIN32)
  SET(SRCS nputil_libusb1.c)
  BUILDSYS_BUILD_LIB(
    NAME nputil_libusb1
    SOURCES "${SRCS}" 
    CXX_FLAGS FALSE
    LINK_LIBS FALSE
    LINK_FLAGS FALSE
    DEPENDS FALSE
    SHOULD_INSTALL TRUE
    VERSION "${LIBNPUTIL_VERSION}"
    )
ENDIF()

