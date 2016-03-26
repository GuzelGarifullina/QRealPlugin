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

// !!to test soon will delete
#undef QT_NO_CAST_FROM_ASCII
#include <iostream>

#include <fstream>
#include <coreplugin/icore.h>

#include "qrealconstants.h"
#include "qRealCoreSettings.h"

#include <QFile>
#include <QMessageBox>
#include <QTextStream>

using namespace QReal;

qRealCoreSettings::qRealCoreSettings()
{
	m_settings = Core::ICore::settings();
}
qRealCoreSettings::~qRealCoreSettings(){
	//nothing to do there
}

void qRealCoreSettings::saveSettings() const{
	//nothing to do there
}

void qRealCoreSettings::loadDefaultSettings(){
	if (m_isFirtTimeLoaded()){
		m_loadDefaultPluginSettings();
		m_loadDefaultSystemSettings();
		m_settings->sync();
	}
}
void qRealCoreSettings::m_loadDefaultPluginSettings(){
	m_settings->beginGroup(QLatin1String(Constants::CORE_SETTINGS_GROUP));
	//new settings go here, abcde - is just an example
	m_settings->setValue(QLatin1String("abcde"), 0);
	m_settings->endGroup();
}
void qRealCoreSettings::m_loadDefaultSystemSettings(){
	// !change to build dir
	QString fileName ="/home/guzel/Programming/all/lol/readFromFile/data.txt";
	QFile file(fileName);
	if(!file.open(QIODevice::ReadOnly)){
		// !!need normal message, soon delete
		QMessageBox::information(0,"error",file.errorString());
	}

	QTextStream inStream(&file);

	QString group ="";
	QString groupX="";
	QString name="";
	QString value="";
	int pos = 0;
	while (!inStream.atEnd())
	{
		QString line = inStream.readLine();
		pos = line.indexOf(']');
		if (line.indexOf('[') == 0
			&& pos > 0)
		{
			groupX = line.mid(1, pos -1);
			if (group != ""){
				m_settings->endGroup();
			}
			group = groupX;
			m_settings->beginGroup(group);
		}
		else
		{
			pos = line.indexOf('=');
			if (pos > 0) {
				name = line.left(pos);
				value = line.mid(pos+1, line.length()-1);
				m_settings->setValue(name, value);
			}
		}
	}
	m_settings->endGroup();
}
bool qRealCoreSettings::m_isFirtTimeLoaded(){
	m_settings->beginGroup(QLatin1String(Constants::CORE_SETTINGS_GROUP));
	bool res=m_settings->contains(QLatin1String("abcd"));
	if (!res){
		std::cout<< "first time settings loaded";
	}
	m_settings->endGroup();
	return res;
}

