# Metaballs

cmake_minimum_required (VERSION 2.7)

project (test_ATSPI)

find_package (OpenGL REQUIRED)
find_package (GLUT REQUIRED)

include_directories (
    ${OPENGL_INCLUDE_DIR}
    ${GLUT_INCLUDE_DIR}
)

add_executable (Metaballs src/metaballs.c src/particle.c src/cube.c)

target_link_libraries (Metaballs
    ${OPENGL_LIBRARIES}
    ${GLUT_LIBRARIES}
)
