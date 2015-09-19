# Copyright (c) 2014-2015 cyrille_favreau@hotmail.com

set(MODELVIEWERSERVICE_SOURCES
  ModelViewerService.cpp
  ModelLoader.cpp
)

set(MODELVIEWERSERVICE_HEADERS
  ModelLoader.h
)

set(MODELVIEWERSERVICE_LINK_LIBRARIES
  ${GLUT_LIBRARIES}
  assimp
)

if(APPLE)
else()
  list(APPEND MODELVIEWERSERVICE_LINK_LIBRARIES
    GL
    GLU
  )
endif(APPLE)


common_application(ModelViewerService)
