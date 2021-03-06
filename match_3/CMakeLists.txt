﻿# CMakeList.txt : CMake project for match_3, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

set(assets_src "assets/assets.h" )   
set(game_render_src "game_render/igame_render.h" "game_render/game_render.h" "game_render/game_render.cpp")   
set(game_controller_src "game_controller/game_controller.h" "game_controller/game_controller.cpp")
set(game_model_src "game_model/game_model.h" "game_model/game_model.cpp" "game_model/gem_stone.h")

add_executable (match_3 "main.cpp" ${game_render_src} ${game_controller_src} ${assets} ${game_model_src})
set_target_properties (
	match_3 
	PROPERTIES 
	CXX_STANDARD 17
	CXX_STANDARD_REQUIRED ON	
)
#set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/"modules" ${CMAKE_MODULE_PATH})
#set(ENV{SFML_DIR} "c:\\Program Files (x86)\\SFML-2.5.1" )#Временно прибит гвоздями
set(SFML_STATIC_LIBRARIES TRUE)

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)
if(NOT SFML_FOUND)
	message(SEND_ERROR "Failed to find sfml")
	return()
endif()

find_package(Boost REQUIRED)
if(NOT Boost_FOUND)
	message(SEND_ERROR "Failed to find boost")
	return()
endif()

target_include_directories(			
	match_3
	PRIVATE 
    ${PROJECT_SOURCE_DIR} 
    ${Boost_INCLUDE_DIRS}
)
target_link_libraries(match_3  sfml-graphics sfml-audio)

set(resources_dir "resources")
set(resources ${resources_dir}/cursor.png ${resources_dir}/gems.png ${resources_dir}/background.png ${resources_dir}/calibri.ttf)
set(resources_bin_dir ${CMAKE_BINARY_DIR}/resources)

file(MAKE_DIRECTORY ${resources_bin_dir})
file(COPY ${resources} DESTINATION ${resources_bin_dir})
# TODO: Add tests and install targets if needed.
