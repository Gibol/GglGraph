QT          += opengl

HEADERS     = \
              window.h \
    gglgraph.h
SOURCES     = \
              main.cpp \
              window.cpp \
    gglgraph.cpp

# install
target.path = $$[QT_INSTALL_EXAMPLES]/opengl/2dpainting
sources.files = $$SOURCES $$HEADERS $$RESOURCES $$FORMS 2dpainting.pro
sources.path = $$[QT_INSTALL_EXAMPLES]/opengl/2dpainting
INSTALLS += target sources

linux:LIBS += -lGLU
