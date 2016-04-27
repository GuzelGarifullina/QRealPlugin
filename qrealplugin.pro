# Copyright 2016 Guzel Garifullina
#
# Licensed under the GNU General Public License, Version 3.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.gnu.org/licenses/gpl-3.0.en.html
#


DEFINES += QREALPLUGIN_LIBRARY

# qrealplugin files

SOURCES += qrealpluginplugin.cpp \
	qRealCoreSettings.cpp

HEADERS += qrealpluginplugin.h \
		qrealplugin_global.h \
		qrealpluginconstants.h \
	qRealCoreSettings.h

# Qt Creator linking
QMAKE_CXXFLAGS += -Wall -Wextra -pedantic -Weffc++ -Wold-style-cast
QMAKE_CXXFLAGS += -Wconversion -Wunreachable-code

## set the QTC_SOURCE environment variable to override the setting here
QTCREATOR_SOURCES = $$(QTC_SOURCE)
isEmpty(QTCREATOR_SOURCES):QTCREATOR_SOURCES=/home/guzel/Programs/qt-creator

## set the QTC_BUILD environment variable to override the setting here
IDE_BUILD_TREE = $$(QTC_BUILD)
isEmpty(IDE_BUILD_TREE):IDE_BUILD_TREE=/home/guzel/Programs/qt-creator

## uncomment to build plugin into user config directory
## <localappdata>/plugins/<ideversion>
##    where <localappdata> is e.g.
##    "%LOCALAPPDATA%\QtProject\qtcreator" on Windows Vista and later
##    "$XDG_DATA_HOME/data/QtProject/qtcreator" or "~/.local/share/data/QtProject/qtcreator" on Linux
##    "~/Library/Application Support/QtProject/Qt Creator" on Mac
# USE_USER_DESTDIR = yes

###### If the plugin can be depended upon by other plugins, this code needs to be outsourced to
###### <dirname>_dependencies.pri, where <dirname> is the name of the directory containing the
###### plugin's sources.

QTC_PLUGIN_NAME = qrealplugin
QTC_LIB_DEPENDS +=  \
	aggregation \
	extensionsystem \
	utils
QTC_PLUGIN_DEPENDS += \
	coreplugin \
	cppeditor \
	diffeditor \
	projectexplorer \
	beautifier

QTC_PLUGIN_RECOMMENDS += \
	# optional plugin dependencies. nothing here at this time

###### End _dependencies.pri contents ######

include($$QTCREATOR_SOURCES/src/qtcreatorplugin.pri)


