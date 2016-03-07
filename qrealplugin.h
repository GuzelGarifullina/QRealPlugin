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

