function(gafro_add_example EXECUTABLE)
  add_executable(${EXECUTABLE} ${EXECUTABLE}.cpp)
  target_compile_options(${EXECUTABLE} PUBLIC "-O3")
  target_link_libraries(${EXECUTABLE} PUBLIC gafro::gafro gafro_robot_descriptions::gafro_robot_descriptions)
  target_include_directories(${EXECUTABLE} PRIVATE ${CMAKE_CURRENT_LIST_DIR})

  install(TARGETS ${EXECUTABLE} EXPORT ${PROJECT_NAME}-config-targets RUNTIME DESTINATION bin)
endfunction()