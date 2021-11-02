project(TevianClient)

find_package(Qt5 COMPONENTS Widgets Gui REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_executable(${PROJECT_NAME} 
	customview.h
	customview.cpp
	tevianclient.ui
	tevianclient.h
	tevianclient.cpp
	resources.qrc
	main.cpp
)

target_include_directories (${PROJECT_NAME} PUBLIC Manager)

target_link_libraries(${PROJECT_NAME} PUBLIC Qt5::Widgets Qt5::Gui Manager)

set_target_properties (${PROJECT_NAME}
		PROPERTIES
			ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/install/lib"
			LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/install/lib"
			RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/install/bin"
)

if(WIN32)
	get_target_property(_qmake_executable Qt5::qmake IMPORTED_LOCATION)
	get_filename_component(_qt_bin_dir "${_qmake_executable}" DIRECTORY)
	find_program(WINDEPLOYQT_EXECUTABLE windeployqt HINTS "${_qt_bin_dir}")
	add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND "${CMAKE_COMMAND}" -E
        env PATH="${_qt_bin_dir}" "${WINDEPLOYQT_EXECUTABLE}"
            --verbose 0
            --no-compiler-runtime
            \"$<TARGET_FILE:TevianClient>\"
)
endif()