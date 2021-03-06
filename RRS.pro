TEMPLATE = subdirs

CONFIG += ordered

SUBDIRS += ./CfgReader
SUBDIRS += ./CfgEditor
SUBDIRS += ./filesystem
SUBDIRS += ./libJournal
SUBDIRS += ./tcp-connection
SUBDIRS += ./asound
SUBDIRS += ./simulator

SUBDIRS += ./viewer

SUBDIRS += ./addons/passcar
SUBDIRS += ./addons/vl60
SUBDIRS += ./addons/tep70
SUBDIRS += ./addons/chs2t
SUBDIRS += ./addons/ep20

SUBDIRS += ./launcher
SUBDIRS += ./launcher2


SUBDIRS += ./tools/profconv
SUBDIRS += ./tools/pathconv
SUBDIRS += ./tools/routeconv

#SOURCES += \
#    addons/vl60/vl60-equipment/src/tapping-sound.cpp \
#    addons/vl60/vl60-equipment/src/tapping-sound.cpp

#HEADERS += \
#    addons/vl60/vl60-equipment/include/tapping-sound.h
