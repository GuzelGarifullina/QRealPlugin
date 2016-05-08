/* Copyright 2016 Guzel Garifullina
 *
 * Licensed under the GNU General Public License, Version 3.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.gnu.org/licenses/gpl-3.0.en.html */

#pragma once

#include <QtCore/qglobal.h>
#include <coreplugin/icore.h>
#include <QObject>
#include <QSettings>

#include "qrealpluginconstants.h"

namespace QReal{
namespace Internal{

class qRealCoreSettings : public QObject
{
	Q_OBJECT
public:
	qRealCoreSettings();
	~qRealCoreSettings();

	//change qreal plugin settings
	void saveSettings() const;

	//load default settings on first startup
	//plugin and system
	void loadOnStartUp() const;
private:
	QSettings *m_settings;
	bool m_isFirtTimeLoaded() const;
	void m_loadDefaultPluginSettings() const;
	void m_loadDefaultSystemSettings() const;
	void m_loadFromFile(QString qRealPluginPath) const;
	void m_loadLicense(QString qRealPluginPath) const;
	void m_loadDocumentation(QString qRealPluginPath) const;
	void m_loadBeautifierSettings() const;
	const QString m_qRealPluginPath = (Core::ICore::userResourcePath()) + QLatin1Char('/')
		+ QLatin1String(Constants::PLUGIN_DIR);
/*signals:
	//will need in future when will have plugin settings
	void settingsChanged();*/
};

} // namespace Internal
} // namespace QReal
