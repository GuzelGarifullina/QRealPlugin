/* Copyright 2016 Guzel Garifullina
 *
 * Licensed under the GNU General Public License, Version 3.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.gnu.org/licenses/gpl-3.0.en.html */

// !!to test soon will delete
#undef QT_NO_CAST_FROM_ASCII

#include <coreplugin/icore.h>
#include <coreplugin/helpmanager.h>


#include "qrealpluginconstants.h"
#include "qRealCoreSettings.h"

#include <QFileInfo>
#include <QMessageBox>
#include <QDebug>
#include <QtGlobal>
#include <QDir>

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

void qRealCoreSettings::loadOnStartUp() const
{
	/*if (m_isFirtTimeLoaded()) {
		m_loadDefaultPluginSettings();
	}*/
	m_loadDocumentation(m_qRealPluginPath);

}
void qRealCoreSettings::m_loadDefaultPluginSettings() const
{
	m_settings->beginGroup(QLatin1String(Constants::CORE_SETTINGS_GROUP));
	//new settings go here, now we need it only to load settings first time
	m_settings->setValue(QLatin1String(Constants::CORE_SETTINGS_TO_LOAD_SETTINGS), 0);
	m_settings->endGroup();
	m_settings->sync();
}


// !! add button
void qRealCoreSettings::m_loadDefaultSystemSettings() const
{
	m_loadFromFile(m_qRealPluginPath);
	m_loadLicense(m_qRealPluginPath);
	m_loadBeautifierSettings();
}

// !!!! rename
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
	m_settings->sync();
}

void qRealCoreSettings::m_loadLicense(QString qRealPluginPath) const
{
	QString licensePath = qRealPluginPath + "/"
		+ (Constants::LICENSE_FILENAME);

	Q_ASSERT(QFileInfo::exists(licensePath));
	m_settings->setValue(Constants::CORE_SETTINGS_LICENSE
		, licensePath);
	m_settings->sync();
}


// loads all .qhc files from documentation dir
void qRealCoreSettings::m_loadDocumentation(QString qRealPluginPath) const
{
	QString documentsPath = qRealPluginPath + "/"
			+ (Constants::DOCUMENTATION_DIR);

	Q_ASSERT(QFileInfo::exists(documentsPath));

	QDir dir(documentsPath);
	QStringList nameFilter("*.qch");

	QStringList doc;
	foreach(QFileInfo item, dir.entryInfoList(nameFilter) ){
		doc << item.absoluteFilePath();
	}
	Core::HelpManager::registerDocumentation(doc);
}

// look for other builds
// dont need it?
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
