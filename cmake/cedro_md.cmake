set(CMD_HEADERS
  ${CMAKE_CURRENT_SOURCE_DIR}/include/internal/cedromd.h
  ${CMAKE_CURRENT_SOURCE_DIR}/include/managers/CMDBaseManager.h
  ${CMAKE_CURRENT_SOURCE_DIR}/include/managers/CMDProcessedManager.h
  ${CMAKE_CURRENT_SOURCE_DIR}/include/common/CMDTypes.h
  ${CMAKE_CURRENT_SOURCE_DIR}/include/helpers/StringHelper.h
  ${CMAKE_CURRENT_SOURCE_DIR}/include/models/SQTModel.h
  ${CMAKE_CURRENT_SOURCE_DIR}/include/models/BQTModel.h
  ${CMAKE_CURRENT_SOURCE_DIR}/include/models/GQTModel.h
  ${CMAKE_CURRENT_SOURCE_DIR}/include/models/SABModel.h
  ${CMAKE_CURRENT_SOURCE_DIR}/include/models/VAPModel.h
  ${CMAKE_CURRENT_SOURCE_DIR}/include/models/GPNModel.h
  ${CMAKE_CURRENT_SOURCE_DIR}/include/cedromd
)

set(CMD_SRCS
  ${CMAKE_CURRENT_SOURCE_DIR}/src/managers/CMDBaseManager.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/managers/CMDProcessedManager.cpp
)

set(CMD_INCLUDE_DIRS
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/include/managers
    ${CMAKE_CURRENT_SOURCE_DIR}/include/internal
    ${CMAKE_CURRENT_SOURCE_DIR}/include/common
    ${CMAKE_CURRENT_SOURCE_DIR}/include/helpers
    ${CMAKE_CURRENT_SOURCE_DIR}/include/models
)