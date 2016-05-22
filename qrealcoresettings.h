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
	//now it loads only documentation
	static void loadOnStartUp();

	//changes global settings to fit codestyle
	static void loadDefaultSystemSettings();
private:
	static void m_loadGlobalSettings(QString qRealPluginPath);
	static void m_loadLicense(QString qRealPluginPath);
	static void m_loadDocumentation(QString qRealPluginPath);
	static const QString m_qRealPluginPath;
};
} // namespace Internal
} // namespace QReal
