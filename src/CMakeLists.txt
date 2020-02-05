if(UNIX)
  set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -Wl,--no-undefined")
endif()

# common lib

add_library(bcecommon STATIC
  Configuration.h Configuration.cpp
  Task.h Task.cpp
  SessionMapper.h SessionMapper.cpp
  )

target_link_libraries(bcecommon PUBLIC
  wt wtdbo wtdbopostgres wtdbosqlite3 jsoncpp)

set_target_properties(bcecommon PROPERTIES
  CXX_STANDARD 17
  CXX_EXTENSIONS OFF
  POSITION_INDEPENDENT_CODE ON)

target_include_directories(bcecommon PUBLIC ${CMAKE_CURRENT_LIST_DIR})


# web app

add_executable(bcenvironmentapp
  Application.h Application.cpp
  main.cpp)

target_link_libraries(bcenvironmentapp PRIVATE bcecommon wt wthttp wtdbo
  ${Boost_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})

target_include_directories(bcenvironmentapp PUBLIC ${CMAKE_CURRENT_LIST_DIR})

set_target_properties(bcenvironmentapp PROPERTIES
  CXX_STANDARD 17
  CXX_EXTENSIONS OFF
  )

install(TARGETS bcenvironmentapp)

# helper tool

add_executable(bcetool
  BCEToolMain.cpp)

target_link_libraries(bcetool PRIVATE bcecommon
  ${Boost_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})

set_target_properties(bcetool PROPERTIES
  CXX_STANDARD 17
  CXX_EXTENSIONS OFF
  )

install(TARGETS bcetool)
