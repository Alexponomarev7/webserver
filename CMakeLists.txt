cmake_minimum_required(VERSION 3.9)

project(web_server)

include_directories(".")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Release)

set(LIBRARY
        server/libs/connection/connection.cpp
        #server/libs/connection/storage.cpp
        server/libs/connection/testlib.cpp
        server/libs/common/types.cpp
        server/libs/daemon/daemontools.cpp
        )

set(UTILS
        utils/logger/logger.cpp
        utils/time.cpp
        utils/string/string.cpp server/libs/daemon/config.cpp server/libs/daemon/config.h utils/sys/cmdparser.cpp utils/sys/cmdparser.h utils/sys/helpers.h)

add_executable(wserver server/daemons/main.cpp ${LIBRARY} ${UTILS})