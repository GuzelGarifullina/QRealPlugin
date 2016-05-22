/* Copyright 2016 Guzel Garifullina
 *
 * Licensed under the GNU General Public License, Version 3.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.gnu.org/licenses/gpl-3.0.en.html */

#pragma once

namespace QReal {
namespace Constants {

const char DISPLAY_NAME[] = "QReal";
const char MENU_ID[] = "QReal.Menu";
const char ACTION_CHECKFILE[]     = "QReal.CheckFile";
const char ACTION_CHECKPROJECT[] = "QReal.CheckProject";

const char MSG_ACTION_CHECKFILE[]     = "Check File";
const char MSG_ACTION_CHECKPROJECT[] = "Check Project";

const char CORE_SETTINGS_GROUP [] = "QRealPlugin";
const char CORE_VERA_RULES [] = "VeraRulesPath";

//for option page
const char DISPLAY_VERA_NAME[] = "Vera";
const char VERA_OPTION_ID[]= "Vera";
const char OPTION_CATEGORY[] = "II.QReal";

// need to load settings
const char CORE_SETTINGS_LICENSE[] = "CppTools/LicenseTemplate";
const char CORE_SETTINGS_DOCUMENTATION[] = "Help/UserDocumentation";
const char CORE_SETTINGS_BEAUTIFIER_BUILD[] = "Beautifier/uncrustify/command";

//in filesystem
const char PLUGIN_DIR [] = "qRealPlugin";
const char DEFAULT_SETTINGS_FILENAME [] = "defaultSettings.ini";
const char LICENSE_FILENAME [] = "license.txt";
const char DOCUMENTATION_DIR [] = "documentation";

} // namespace QReal
} // namespace Constants
