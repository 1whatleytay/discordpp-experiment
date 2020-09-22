add_library(utility STATIC
    include/utility/swap.h
    include/utility/optional.h
    include/utility/io.h
    include/utility/data.h
    include/utility/json.h
    include/utility/parser.h

    src/data.cpp
    src/json.cpp
    src/parser.cpp)

target_include_directories(utility PUBLIC include)