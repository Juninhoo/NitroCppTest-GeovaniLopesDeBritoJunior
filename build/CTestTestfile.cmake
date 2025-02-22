# CMake generated Testfile for 
# Source directory: C:/Users/geova/OneDrive/Ambiente de Trabalho/tests
# Build directory: C:/Users/geova/OneDrive/Ambiente de Trabalho/tests/build
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
if(CTEST_CONFIGURATION_TYPE MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
  add_test(RectangleTests "C:/Users/geova/OneDrive/Ambiente de Trabalho/tests/build/Debug/rectangle_tests.exe")
  set_tests_properties(RectangleTests PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/geova/OneDrive/Ambiente de Trabalho/tests/CMakeLists.txt;27;add_test;C:/Users/geova/OneDrive/Ambiente de Trabalho/tests/CMakeLists.txt;0;")
elseif(CTEST_CONFIGURATION_TYPE MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
  add_test(RectangleTests "C:/Users/geova/OneDrive/Ambiente de Trabalho/tests/build/Release/rectangle_tests.exe")
  set_tests_properties(RectangleTests PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/geova/OneDrive/Ambiente de Trabalho/tests/CMakeLists.txt;27;add_test;C:/Users/geova/OneDrive/Ambiente de Trabalho/tests/CMakeLists.txt;0;")
elseif(CTEST_CONFIGURATION_TYPE MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
  add_test(RectangleTests "C:/Users/geova/OneDrive/Ambiente de Trabalho/tests/build/MinSizeRel/rectangle_tests.exe")
  set_tests_properties(RectangleTests PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/geova/OneDrive/Ambiente de Trabalho/tests/CMakeLists.txt;27;add_test;C:/Users/geova/OneDrive/Ambiente de Trabalho/tests/CMakeLists.txt;0;")
elseif(CTEST_CONFIGURATION_TYPE MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
  add_test(RectangleTests "C:/Users/geova/OneDrive/Ambiente de Trabalho/tests/build/RelWithDebInfo/rectangle_tests.exe")
  set_tests_properties(RectangleTests PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/geova/OneDrive/Ambiente de Trabalho/tests/CMakeLists.txt;27;add_test;C:/Users/geova/OneDrive/Ambiente de Trabalho/tests/CMakeLists.txt;0;")
else()
  add_test(RectangleTests NOT_AVAILABLE)
endif()
subdirs("googletest")
subdirs("test")
