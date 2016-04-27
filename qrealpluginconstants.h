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

const char ACTION_ID[] = "qrealplugin.Action";
const char MENU_ID[] = "qrealplugin.Menu";

const char CORE_SETTINGS_GROUP [] = "QRealPlugin";
const char CORE_SETTINGS_TO_LOAD_SETTINGS [] = "isFirstTimeLoaded";

// need to load settings
const char CORE_SETTINGS_LICENSE[] = "CppTools/LicenseTemplate";
const char CORE_SETTINGS_DOCUMENTATION[] = "Help/UserDocumentation";
const char CORE_SETTINGS_BEAUTIFIER_BUILD[] = "Beautifier/uncrustify/command";


//in filesystem
const char PLUGIN_DIR [] = "qRealPlugin";
const char DEFAULT_SETTINGS_FILENAME [] = "defaultSettings.ini";
const char LICENSE_FILENAME [] = "license.txt";
const char DOCUMENTATION_FILENAME [] = "qrgui.qch";
//only for Linux, and it is not always
const char BEAUTIFIER_BUILD [] = "/usr/bin/uncrustify";

} // namespace QReal
} // namespace Constants
