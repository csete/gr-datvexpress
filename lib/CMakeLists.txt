# Copyright 2011,2012 Free Software Foundation, Inc.
#
# This file is part of GNU Radio
#
# GNU Radio is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3, or (at your option)
# any later version.
#
# GNU Radio is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with GNU Radio; see the file COPYING.  If not, write to
# the Free Software Foundation, Inc., 51 Franklin Street,
# Boston, MA 02110-1301, USA.

########################################################################
# Setup library
########################################################################
include(GrPlatform) #define LIB_SUFFIX
include(FindUSB)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/hw
    ${GNURADIO_RUNTIME_INCLUDE_DIRS}
    ${Boost_INCLUDE_DIRS}
    ${LIBUSB_INCLUDE_DIR}
)

link_directories(
	${Boost_LIBRARY_DIRS}
	${LIBUSB_LIBRARY_DIRS}
)

list(APPEND datvexpress_sources
    sink_c_impl.cc
    hw/express.cpp
    hw/si570.cpp

)

set(datvexpress_sources "${datvexpress_sources}" PARENT_SCOPE)

add_library(gnuradio-datvexpress SHARED ${datvexpress_sources})
target_link_libraries(gnuradio-datvexpress ${Boost_LIBRARIES} ${LIBUSB_LIBRARIES} ${GNURADIO_ALL_LIBRARIES})
set_target_properties(gnuradio-datvexpress PROPERTIES DEFINE_SYMBOL "gnuradio_datvexpress_EXPORTS")

if(APPLE)
    set_target_properties(gnuradio-datvexpress PROPERTIES
        INSTALL_NAME_DIR "${CMAKE_INSTALL_PREFIX}/lib"
    )
endif(APPLE)

########################################################################
# Install built library files
########################################################################
install(TARGETS gnuradio-datvexpress
    LIBRARY DESTINATION lib${LIB_SUFFIX} # .so/.dylib file
    ARCHIVE DESTINATION lib${LIB_SUFFIX} # .lib file
    RUNTIME DESTINATION bin              # .dll file
)

########################################################################
# Build and register unit test
########################################################################
include(GrTest)

include_directories(${CPPUNIT_INCLUDE_DIRS})

list(APPEND test_datvexpress_sources
    ${CMAKE_CURRENT_SOURCE_DIR}/test_datvexpress.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/qa_datvexpress.cc
)

add_executable(test-datvexpress ${test_datvexpress_sources})

target_link_libraries(
  test-datvexpress
  ${GNURADIO_RUNTIME_LIBRARIES}
  ${Boost_LIBRARIES}
  ${CPPUNIT_LIBRARIES}
  gnuradio-datvexpress
)

GR_ADD_TEST(test_datvexpress test-datvexpress)
