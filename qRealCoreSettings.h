/* Copyright 2016 Guzel Garifullina
 *
 * Licensed under the GNU General Public License, Version 3.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.gnu.org/licenses/gpl-3.0.en.html */

#pragma once

#include <QtCore/qglobal.h>
#include <QObject>
#include <coreplugin/icore.h>

#include "qrealpluginconstants.h"

namespace QReal{
namespace Internal{

class qRealCoreSettings : public QObject
{
	Q_OBJECT
public:
	qRealCoreSettings();
	~qRealCoreSettings();

	//load default settings on first startup
	//plugin and system
	void loadOnStartUp() const;
private:
	void m_loadDefaultSystemSettings() const;
	void m_loadFromFile(QString qRealPluginPath) const;
	void m_loadLicense(QString qRealPluginPath) const;
	void m_loadDocumentation(QString qRealPluginPath) const;
	void m_loadBeautifierSettings() const;
	const QString m_qRealPluginPath = (Core::ICore::userResourcePath()) + QLatin1Char('/')
		+ QLatin1String(Constants::PLUGIN_DIR);
};

} // namespace Internal
} // namespace QReal
