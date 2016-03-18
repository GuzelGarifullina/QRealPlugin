/* Copyright  2016 Guzel Garifullina
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

//to test
#undef QT_NO_CAST_FROM_ASCII
#include <iostream>

#include <coreplugin/icore.h>

#include "qrealconstants.h"
#include "qRealCoreSettings.h"

using namespace QReal;

qRealCoreSettings::qRealCoreSettings()
{
	settings = Core::ICore::settings();
}
qRealCoreSettings::~qRealCoreSettings(){
	//delete (settings);
}

void qRealCoreSettings::saveToSettings() const{
}

void qRealCoreSettings::loadDefaultSettings(){
	if (isFirtTimeLoaded()){
		loadDefaultPluginSettings();
		loadDefaultSystemSettings();
		settings->sync();
	}
}
void qRealCoreSettings::loadDefaultPluginSettings(){
	settings->beginGroup(QLatin1String(Constants::CORE_SETTINGS_GROUP));
	//new settings go here, abcde - is just an example
	settings->setValue(QLatin1String("abcde"), 0);
	settings->endGroup();
}
void qRealCoreSettings::loadDefaultSystemSettings(){

	settings->beginGroup("textTypingSettings");
	bool spacesForTabs= settings->value("AutoIndent").toBool();
	std::cout << spacesForTabs << std::endl;
	settings->setValue("textTypingSettings/AutoIndent", false);
	settings->endGroup();
	spacesForTabs= settings->value("AutoIndent").toBool();
	std::cout << spacesForTabs << std::endl;
}
bool qRealCoreSettings::isFirtTimeLoaded(){
	settings->beginGroup(QLatin1String(Constants::CORE_SETTINGS_GROUP));
	if (!settings->contains(QLatin1String("abcde"))){
		std::cout<< "first time settings loaded";
		settings->endGroup();
		return true;
	}
	return false;
}

