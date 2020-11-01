cmake_minimum_required(VERSION "3.19.0")


project("IAS")

add_executable("${PROJECT_NAME}" "main.c")

install(TARGETS "${PROJECT_NAME}" DESTINATION bin) #${CMAKE_INSTALL_PREFIX}/bin
install(FILES "main.c" DESTINATION src) #${CMAKE_INSTALL_PREFIX}/src
