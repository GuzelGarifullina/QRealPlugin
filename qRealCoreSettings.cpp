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

#include <fstream>
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
	const int MAX_CHARS_PER_LINE = 512;
	std::string fileName ="/home/guzel/Programming/all/lol/readFromFile/data.txt";

	std::ifstream fin;
	fin.open(fileName); // open a file
	if (!fin.good()){
		std::cout << "Error when open file";
		return; // exit if file not found
	}
	char lineBuf[MAX_CHARS_PER_LINE] = "";
	QString group ="";
	QString groupX="";
	QString name="";
	QString value="";
	int pos = 0;
	while (fin.getline(lineBuf, MAX_CHARS_PER_LINE))
	{
		QString line = QString(lineBuf);
		pos = line.indexOf(']');
		if (line.indexOf('[') == 0
			&& pos > 0)
		{
			groupX = line.mid(1, pos -1);
			if (group != ""){
				settings->endGroup();
			}
			group = groupX;
			settings->beginGroup(group);
		}
		else
		{
			pos = line.indexOf('=');
			if (pos > 0) {
				name = line.left(pos);
				value = line.mid(pos+1, line.length()-1);
				settings->setValue(name, value);
			}
		}
	}
	settings->endGroup();
}
bool qRealCoreSettings::isFirtTimeLoaded(){
	settings->beginGroup(QLatin1String(Constants::CORE_SETTINGS_GROUP));
	bool res=settings->contains(QLatin1String("abcd"));
	if (!res){
		std::cout<< "first time settings loaded";
	}
	settings->endGroup();
	return res;
}

