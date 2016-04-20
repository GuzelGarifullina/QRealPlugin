# Copyright 2016 Guzel Garifullina
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

TEMPLATE = lib
DEFINES += QREAL_LIBRARY

# QReal files

SOURCES += qrealplugin.cpp \
	qRealCoreSettings.cpp

HEADERS += qrealplugin.h \
		qreal_global.h \
		qrealconstants.h \
	qRealCoreSettings.h

# Qt Creator linking
QMAKE_CXXFLAGS += -Wall -Wextra -pedantic -Weffc++ -Wold-style-cast
QMAKE_CXXFLAGS += -Wconversion -Wunreachable-code
#QMAKE_CXXFLAGS += -isystem /home/guzel/Programs/qt/Tools/QtCreator/lib/qtcreator

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

QTC_PLUGIN_NAME = QReal
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


#####To make .so file

# Set the destination directory of the shared libraries
# MYDLLDIR is a name something I made up myself, DESTDIR is a QMake variable.
# $$IN_PWD expands to the directory your .pro file is in.
# This example copies the final build output to ../dlls (one level above your project).
MYDLLDIR = $$IN_PWD/../dlls

# We need quotes around the path in order to support whitespaces in the path
# for Windows. e.g. (''C:\Users\Gert van Dijk\...'').
# For some strange reason $$quote(...) does not seem to work for Windows here.
DESTDIR = \"$$MYDLLDIR\"

#
# Here's some magic to move all of the project's header files to the same DLL directory.
#

DDIR = \"$$MYDLLDIR/\"
SDIR = \"$$IN_PWD/\"
# Replace slashes in paths with backslashes for Windows
#win32:file ~= s,/,\\,g
#win32:DDIR ~= s,/,\\,g
#win32:SDIR ~= s,/,\\,g
# For-loop to copy all header files to DDIR.
for(file, HEADERS) {
	QMAKE_POST_LINK += $$QMAKE_COPY $$quote($${SDIR}$${file}) $$quote($$DDIR) $$escape_expand(\\n\\t)
}

