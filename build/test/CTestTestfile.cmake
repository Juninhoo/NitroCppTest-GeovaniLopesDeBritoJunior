# CMake generated Testfile for 
# Source directory: C:/Users/geova/OneDrive/Ambiente de Trabalho/tests/test
# Build directory: C:/Users/geova/OneDrive/Ambiente de Trabalho/tests/build/test
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
if(CTEST_CONFIGURATION_TYPE MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
  add_test(UnitTest "C:/Users/geova/OneDrive/Ambiente de Trabalho/tests/build/test/Debug/UnitTest.exe")
  set_tests_properties(UnitTest PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/geova/OneDrive/Ambiente de Trabalho/tests/test/CMakeLists.txt;28;add_test;C:/Users/geova/OneDrive/Ambiente de Trabalho/tests/test/CMakeLists.txt;0;")
elseif(CTEST_CONFIGURATION_TYPE MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
  add_test(UnitTest "C:/Users/geova/OneDrive/Ambiente de Trabalho/tests/build/test/Release/UnitTest.exe")
  set_tests_properties(UnitTest PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/geova/OneDrive/Ambiente de Trabalho/tests/test/CMakeLists.txt;28;add_test;C:/Users/geova/OneDrive/Ambiente de Trabalho/tests/test/CMakeLists.txt;0;")
elseif(CTEST_CONFIGURATION_TYPE MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
  add_test(UnitTest "C:/Users/geova/OneDrive/Ambiente de Trabalho/tests/build/test/MinSizeRel/UnitTest.exe")
  set_tests_properties(UnitTest PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/geova/OneDrive/Ambiente de Trabalho/tests/test/CMakeLists.txt;28;add_test;C:/Users/geova/OneDrive/Ambiente de Trabalho/tests/test/CMakeLists.txt;0;")
elseif(CTEST_CONFIGURATION_TYPE MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
  add_test(UnitTest "C:/Users/geova/OneDrive/Ambiente de Trabalho/tests/build/test/RelWithDebInfo/UnitTest.exe")
  set_tests_properties(UnitTest PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/geova/OneDrive/Ambiente de Trabalho/tests/test/CMakeLists.txt;28;add_test;C:/Users/geova/OneDrive/Ambiente de Trabalho/tests/test/CMakeLists.txt;0;")
else()
  add_test(UnitTest NOT_AVAILABLE)
endif()
