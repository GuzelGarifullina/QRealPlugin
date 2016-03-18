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

#undef QT_NO_CAST_FROM_ASCII
#include <iostream>
#include <QCoreApplication>
#include "qrealplugin.h"
#include "qrealconstants.h"

#include <coreplugin/icore.h>
#include <coreplugin/icontext.h>
#include <coreplugin/actionmanager/actionmanager.h>
#include <coreplugin/actionmanager/command.h>
#include <coreplugin/actionmanager/actioncontainer.h>
#include <coreplugin/coreconstants.h>

#include <extensionsystem/pluginmanager.h>

#include <QAction>
#include <QMessageBox>
#include <QMainWindow>
#include <QMenu>

#include <coreplugin/inavigationwidgetfactory.h>

#include <QtPlugin>
#include <coreplugin/inavigationwidgetfactory.h>
#include <QTableWidget>

using namespace QReal::Internal;
QRealPlugin::QRealPlugin():
	settings(Core::ICore::settings())
{
	// Create your members
}

QRealPlugin::~QRealPlugin()
{
	// Unregister objects from the plugin manager's object pool
	// Delete members
	//delete settings;
}

bool QRealPlugin::initialize(const QStringList &arguments, QString *errorString)
{
	// Register objects in the plugin manager's object pool
	// Load settings

	bool spacesForTabs= settings->value("textTypingSettings/AutoIndent").toBool();
	std::cout << spacesForTabs << std::endl;
	settings->setValue("textTypingSettings/AutoIndent", true);
	settings->sync();
	spacesForTabs= settings->value("textTypingSettings/AutoIndent").toBool();
	std::cout << spacesForTabs << std::endl;

	QString name = QCoreApplication::arguments().at(0);
	std::cout << name.toStdString() << std::endl;

	// Add actions to menus
	// Connect to other plugins' signals
	// In the initialize function, a plugin can be sure that the plugins it
	// depends on have initialized their members.

	Q_UNUSED(arguments)
	Q_UNUSED(errorString)


	QAction *action = new QAction(tr("QReal actions"), this);
	Core::Command *cmd = Core::ActionManager::registerAction(action
		, Constants::ACTION_ID
		, Core::Context(Core::Constants::C_GLOBAL));
	cmd->setDefaultKeySequence(QKeySequence(tr("Ctrl+Alt+Meta+A")));
	connect(action, SIGNAL(triggered()), this, SLOT(triggerAction()));


	Core::ActionContainer *menu = Core::ActionManager::createMenu(Constants::MENU_ID);
	menu->menu()->setTitle(tr("QReal"));
	menu->addAction(cmd);
	Core::ActionManager::actionContainer(Core::Constants::M_WINDOW)->addMenu(menu);

	//menu between window and help
	Core::ActionContainer* acMenuBar = Core::ActionManager::
		actionContainer(Core::Constants::MENU_BAR);
	Core::ActionContainer* acMHelp = Core::ActionManager::
		actionContainer(Core::Constants::M_HELP);
	acMenuBar->addMenu(acMHelp, menu);
	return true;
}

void QRealPlugin::extensionsInitialized()
{
	// Retrieve objects from the plugin manager's object pool
	// In the extensionsInitialized function, a plugin can be sure that all
	// plugins that depend on it are completely initialized.
}

ExtensionSystem::IPlugin::ShutdownFlag QRealPlugin::aboutToShutdown()
{
	// Save settings
	// Disconnect from signals that are not needed during shutdown
	// Hide UI (if you add UI that is not in the main window directly)
	return SynchronousShutdown;
}

void QRealPlugin::triggerAction()
{
	QMessageBox::information(Core::ICore::mainWindow()
		, tr("Action triggered") //title
		, tr("This is an action from QReal.")); //message inside messagebox
}
