# components/gps/CMakeLists.txt
idf_component_register(
    SRCS "gps.c"
    INCLUDE_DIRS "."
    REQUIRES driver
)