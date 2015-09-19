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
  GL
  GLU
  assimp
)

common_application(ModelViewerService)
