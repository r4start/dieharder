set(DIEHARDER_SOURCES
      add_ui_rngs.c 
      add_ui_tests.c 
      choose_rng.c 
      dieharder.c 
      dieharder_exit.c 
      help.c 
      list_rngs.c 
      list_tests.c 
      output.c output.h 
      output_rnds.c 
      parsecl.c 
      rdieharder.c 
      run_all_tests.c 
      run_test.c 
      set_globals.c 
      testbits.c 
      time_rng.c 
      user_template.c 
      copyright.h 
      dieharder.h 
      output.h 
      user_template.h)

include_directories(include)

set(BINARY_NAME "dieharder_test")

add_executable(${BINARY_NAME} ${DIEHARDER_SOURCES})
target_link_libraries(${BINARY_NAME} gsl gslcblas m ${PROJECT_NAME})