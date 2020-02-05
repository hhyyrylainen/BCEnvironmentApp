if(UNIX)
  set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -Wl,--no-undefined")
endif()

add_executable(bcenvironmentapp
  Application.h Application.cpp
  Configuration.h Configuration.cpp
  main.cpp)

target_link_libraries(bcenvironmentapp PRIVATE wt wthttp
  wtdbo wtdbopostgres wtdbosqlite3 jsoncpp
  ${Boost_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})

target_include_directories(bcenvironmentapp PUBLIC ${CMAKE_CURRENT_LIST_DIR})

set_target_properties(bcenvironmentapp PROPERTIES
  CXX_STANDARD 17
  CXX_EXTENSIONS OFF
  )

install(TARGETS bcenvironmentapp)
