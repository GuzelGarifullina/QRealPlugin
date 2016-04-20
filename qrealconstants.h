/* Copyright 2016 Guzel Garifullina
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License. */

#pragma once

namespace QReal {
namespace Constants {

const char ACTION_ID[] = "QReal.Action";
const char MENU_ID[] = "QReal.Menu";

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
