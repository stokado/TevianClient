project(Manager)

find_package (Qt5 COMPONENTS Core Network REQUIRED)
find_package (OpenSSL REQUIRED)

set(CMAKE_AUTOMOC ON)

add_library (${PROJECT_NAME} manager.cpp "myrect.h")

target_include_directories (${PROJECT_NAME}
		PUBLIC
			$<INSTALL_INTERFACE:include>
			$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
			${OPENSSL_INCLUDE_DIR}
)

target_link_libraries (${PROJECT_NAME} 
		PUBLIC
			Qt5::Core
			Qt5::Network
			${OPENSSL_LIBRARIES}
)

set_target_properties (${PROJECT_NAME}
		PROPERTIES
			ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/install/lib"
			LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/install/lib"
)