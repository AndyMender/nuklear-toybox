# TODO: Add when some code is moved to "common"
# target_link_libraries(common)

set(APP_NAME "calculator")

# specify main target
add_executable("${APP_NAME}" main.c)

target_link_libraries("${APP_NAME}" m)