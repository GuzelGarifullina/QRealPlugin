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

#include <coreplugin/icore.h>

#include "qrealconstants.h"
#include "qRealCoreSettings.h"

#include <QFileInfo>
#include <QMessageBox>
#include <QTextStream>
#include <QDebug>

using namespace QReal::Internal;

qRealCoreSettings::qRealCoreSettings()
{
	m_settings = Core::ICore::settings();
}
qRealCoreSettings::~qRealCoreSettings()
{
	//nothing to do there
}

void qRealCoreSettings::saveSettings() const
{
	//nothing to do there
}

void qRealCoreSettings::loadDefaultSettings()
{
	if (m_isFirtTimeLoaded()) {
		//m_loadDefaultPluginSettings();
		m_loadDefaultSystemSettings();
		m_settings->sync();
	}
}
void qRealCoreSettings::m_loadDefaultPluginSettings()
{
	m_settings->beginGroup(QLatin1String(Constants::CORE_SETTINGS_GROUP));
	//new settings go here, now we need it only to load settings first time
	m_settings->setValue(QLatin1String(Constants::CORE_SETTINGS_TO_LOAD_SETTINGS), 0);
	m_settings->endGroup();
}
void qRealCoreSettings::m_loadDefaultSystemSettings()
{
	QString fileDir = QLatin1String(Constants::PLUGIN_PATH) + QLatin1Char('/') +
		QLatin1String(Constants::SETTINGS_DIRNAME) + QLatin1Char('/') +
		QLatin1String(Constants::DEFAULT_SETTINGS_FILENAME);

	Q_ASSERT(QFileInfo::exists(fileDir));

	QSettings defaultSettings(fileDir, QSettings::IniFormat);
	QStringList keysList = defaultSettings.allKeys();
	for (int i = 0; i < keysList.size(); ++i) {
		QString key = keysList.at(i);
		QVariant value = defaultSettings.value(key);
		m_settings->setValue(key, value);
	}
}
bool qRealCoreSettings::m_isFirtTimeLoaded()
{
	m_settings->beginGroup(Constants::CORE_SETTINGS_GROUP);
	bool res = !(m_settings->contains(Constants::CORE_SETTINGS_TO_LOAD_SETTINGS));
	//res = res || !res && (m_settings->value(Constants::CORE_SETTINGS_TO_LOAD_SETTINGS).toInt());
	if (res) {
		qDebug() << "first time settings loaded";
	}
	m_settings->endGroup();
	return res;
}
