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
#include <QDebug>
#include <QtGlobal>

using namespace QReal::Internal;

qRealCoreSettings::qRealCoreSettings() :
	m_settings(Core::ICore::settings())
{
	//nothing to do there
}
qRealCoreSettings::~qRealCoreSettings()
{
	//nothing to do there
}

void qRealCoreSettings::saveSettings() const
{
	//nothing to do there
}

void qRealCoreSettings::loadDefaultSettings() const
{
	if (m_isFirtTimeLoaded()) {
		m_loadDefaultPluginSettings();
		m_loadDefaultSystemSettings();

		m_settings->sync();
	}
}
void qRealCoreSettings::m_loadDefaultPluginSettings() const
{
	m_settings->beginGroup(QLatin1String(Constants::CORE_SETTINGS_GROUP));
	//new settings go here, now we need it only to load settings first time
	m_settings->setValue(QLatin1String(Constants::CORE_SETTINGS_TO_LOAD_SETTINGS), 0);
	m_settings->endGroup();
}
void qRealCoreSettings::m_loadDefaultSystemSettings() const
{
	QString qRealPluginPath = (Core::ICore::userResourcePath()) + QLatin1Char('/')
		+ QLatin1String(Constants::PLUGIN_DIR);

	m_loadFromFile(qRealPluginPath);
	m_loadLicense(qRealPluginPath);
	m_loadDocumentation(qRealPluginPath);
	m_loadBeautifierSettings();
}

void qRealCoreSettings::m_loadFromFile(QString qRealPluginPath) const
{
	QString settingsPath = qRealPluginPath + "/"
		+ (Constants::DEFAULT_SETTINGS_FILENAME);

	Q_ASSERT(QFileInfo::exists(settingsPath));

	QSettings defaultSettings(settingsPath
		, QSettings::IniFormat);
	QStringList keysList = defaultSettings.allKeys();

	for (int i = 0; i < keysList.size(); ++i) {
		QString key = keysList.at(i);
		QVariant value = defaultSettings.value(key);
		m_settings->setValue(key
			, value);
	}
}
void qRealCoreSettings::m_loadLicense(QString qRealPluginPath) const
{
	QString licensePath = qRealPluginPath + "/"
		+ (Constants::LICENSE_FILENAME);

	Q_ASSERT(QFileInfo::exists(licensePath));
	m_settings->setValue(Constants::CORE_SETTINGS_LICENSE
		, licensePath);
}

void qRealCoreSettings::m_loadDocumentation(QString qRealPluginPath) const
{
	QString documentPath = qRealPluginPath + "/"
		+ (Constants::DOCUMENTATION_FILENAME);

	Q_ASSERT(QFileInfo::exists(documentPath));
	QString userDocumentsString = m_settings->value(Constants::CORE_SETTINGS_DOCUMENTATION)
		.toString();
	// will not need as we load setting only once
	//at first was idea not to dublicale the same files
	QStringList userDocuments = userDocumentsString.split( ", " );
	for (int i = 0; i < userDocuments.size(); ++i) {
		if (userDocuments.at(i) == documentPath) {
			return;
		}
	}
	//

	m_settings->setValue(Constants::CORE_SETTINGS_DOCUMENTATION
		, QString(documentPath + " ," + userDocumentsString));
}
void qRealCoreSettings::m_loadBeautifierSettings() const
{
	#ifdef Q_OS_LINUX
	Q_ASSERT(QFileInfo::exists(Constants::BEAUTIFIER_BUILD));

	m_settings->setValue(Constants::CORE_SETTINGS_BEAUTIFIER_BUILD
		, Constants::BEAUTIFIER_BUILD);
	#endif
}

bool qRealCoreSettings::m_isFirtTimeLoaded() const
{
	m_settings->beginGroup(Constants::CORE_SETTINGS_GROUP);
	bool res = !(m_settings->contains(Constants::CORE_SETTINGS_TO_LOAD_SETTINGS));
	if (res) {
		qDebug() << "first time settings loaded";
	}
	m_settings->endGroup();
	return res;
}
