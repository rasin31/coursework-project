WT_ADD_EXAMPLE(coursework.wt
  coursework.C
  User.C
  Session.C
  MarkEntryWidget.C
  MarkGradeWidget.C
  CourseworkApp.C
)
TARGET_LINK_LIBRARIES(coursework.wt wtdbo wtdbosqlite3)

# Test whether crypt(3) is provided by libc. If it's not, check if
# libcrypt exists and if it provides crypt(3).
CHECK_FUNCTION_EXISTS(crypt CRYPT_EXISTS)
IF(NOT CRYPT_EXISTS)
  CHECK_LIBRARY_EXISTS(crypt crypt "" CRYPT_LIB_EXISTS)
  IF(CRYPT_LIB_EXISTS)
    SET(CMAKE_REQUIRED_LIBRARIES "crypt")
    CHECK_FUNCTION_EXISTS(crypt CRYPT_EXISTS)
  ENDIF(CRYPT_LIB_EXISTS)
ENDIF(NOT CRYPT_EXISTS)

IF(CRYPT_LIB_EXISTS)
  TARGET_LINK_LIBRARIES(coursework.wt crypt)
ENDIF(CRYPT_LIB_EXISTS)

INCLUDE_DIRECTORIES(${WT_SOURCE_DIR}/src)
