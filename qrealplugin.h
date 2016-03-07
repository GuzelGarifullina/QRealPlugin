/* Copyright 2016 Guzel Garifullina
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

#ifndef QREAL_H
#define QREAL_H

#include "qreal_global.h"

#include <extensionsystem/iplugin.h>

namespace QReal {
namespace Internal {

class QRealPlugin : public ExtensionSystem::IPlugin
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QtCreatorPlugin" FILE "QReal.json")

public:
	QRealPlugin();
	~QRealPlugin();

	bool initialize(const QStringList &arguments, QString *errorString);
	void extensionsInitialized();
	ShutdownFlag aboutToShutdown();

private slots:
	void triggerAction();
};

} // namespace Internal
} // namespace QReal

#endif // QREAL_H

