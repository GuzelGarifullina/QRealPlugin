/* Copyright 2016 Guzel Garifullina
 *
 * Licensed under the GNU General Public License, Version 3.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.gnu.org/licenses/gpl-3.0.en.html */
#pragma once

#include "qrealplugin_global.h"
#include "qRealCoreSettings.h"

#include <extensionsystem/iplugin.h>
#include <QSettings>

namespace QReal{
namespace Internal{

class QRealPlugin: public ExtensionSystem::IPlugin
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QtCreatorPlugin" FILE "qrealplugin.json")

public:
	QRealPlugin();
	~QRealPlugin();

	bool initialize(const QStringList &arguments, QString *errorString) override;
	void extensionsInitialized() override;
	ShutdownFlag aboutToShutdown() override;
	void slotObjectAdded(QObject * obj)	;
private:
	qRealCoreSettings m_settings;

private slots:
	void triggerAction();
};

} // namespace Internal
} // namespace QReal
