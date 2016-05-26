/* Copyright 2016 Guzel Garifullina
 *
 * Licensed under the GNU General Public License, Version 3.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.gnu.org/licenses/gpl-3.0.en.html */

// !!to test soon will delete
#undef QT_NO_CAST_FROM_ASCII

#include "qrealcoresettings.h"
#include "qrealpluginconstants.h"

#include <coreplugin/icore.h>
#include <coreplugin/helpmanager.h>

#include <QFileInfo>
#include <QMessageBox>
#include <QDebug>
#include <QDir>

using namespace QReal::Internal;

qRealCoreSettings::qRealCoreSettings()
{
	//nothing to do there
}

qRealCoreSettings::~qRealCoreSettings()
{
	//nothing to do there
}

const QString qRealCoreSettings::m_qRealPluginPath = Core::ICore::userResourcePath()
	+ QLatin1Char('/')
	+ QLatin1String(Constants::PLUGIN_DIR);

void qRealCoreSettings::loadOnStartUp()
{
	m_loadDocumentation(m_qRealPluginPath);
}

void qRealCoreSettings::loadDefaultSystemSettings()
{
	m_loadGlobalSettings(m_qRealPluginPath);
	m_loadLicense(m_qRealPluginPath);
}

void qRealCoreSettings::m_loadGlobalSettings(QString qRealPluginPath)
{
	QString settingsPath = qRealPluginPath + "/"
		+ (Constants::DEFAULT_SETTINGS_FILENAME);

	Q_ASSERT(QFileInfo::exists(settingsPath));

	QSettings defaultSettings(settingsPath, QSettings::IniFormat);
	QStringList keysList = defaultSettings.allKeys();

	QSettings *s = Core::ICore::settings();

	for (int i = 0; i < keysList.size(); ++i) {
		QString key = keysList.at(i);
		QVariant value = defaultSettings.value(key);
		s->setValue(key, value);
	}
	s->sync();
}

void qRealCoreSettings::m_loadLicense(QString qRealPluginPath)
{
	QString licensePath = qRealPluginPath + "/"
		+ (Constants::LICENSE_FILENAME);

	Q_ASSERT(QFileInfo::exists(licensePath));

	QSettings *s = Core::ICore::settings();
	s->setValue(Constants::CORE_SETTINGS_LICENSE, licensePath);
	s->sync();
}

// loads all .qhc files from documentation dir
void qRealCoreSettings::m_loadDocumentation(QString qRealPluginPath)
{
	QString documentsPath = qRealPluginPath + "/"
		+ (Constants::DOCUMENTATION_DIR);

	Q_ASSERT(QFileInfo::exists(documentsPath));

	QDir dir(documentsPath);

	auto items = dir.entryInfoList({"*.qch"}
			,QDir::Files | QDir::Readable | QDir::NoDotAndDotDot);
	QStringList doc;
	foreach(QFileInfo item, items){
		doc << item.absoluteFilePath();
	}
	Core::HelpManager::registerDocumentation(doc);
}
