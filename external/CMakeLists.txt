add_subdirectory(fmt)

find_package(OpenSSL)
# Make OpenSSL available to the whole project.
add_library(ssl INTERFACE)
target_link_libraries(ssl INTERFACE OpenSSL::SSL)
