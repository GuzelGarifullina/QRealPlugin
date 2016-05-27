/* Copyright 2016 Guzel Garifullina
 *
 * Licensed under the GNU General Public License, Version 3.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.gnu.org/licenses/gpl-3.0.en.html */

//to taste
#undef QT_NO_CAST_FROM_ASCII

#include "qrealpluginplugin.h"
#include "qrealpluginconstants.h"
#include "veraoptionspage.h"
#include "verasettings.h"
#include "qrealcoresettings.h"

#include <cppeditor/cppeditorconstants.h>
#include <coreplugin/actionmanager/actionmanager.h>
#include <coreplugin/actionmanager/command.h>
#include <coreplugin/actionmanager/actioncontainer.h>
#include <coreplugin/coreconstants.h>
#include <coreplugin/icore.h>
#include <coreplugin/icontext.h>
#include <coreplugin/messagemanager.h>
#include <extensionsystem/pluginmanager.h>
#include <extensionsystem/pluginspec.h>

#include <QAction>
#include <QMessageBox>
#include <QMenu>
#include <QtPlugin>

using namespace QReal::Internal;

QRealPlugin::QRealPlugin() :
	m_veraSettings(new VeraSettings),
	m_veraTool(new VeraTool(m_veraSettings))
{
	//nothing to do there
}

QRealPlugin::~QRealPlugin()
{
	delete (m_veraTool);
	delete (m_veraSettings);
}

bool QRealPlugin::initialize(const QStringList &arguments, QString *errorString)
{
	Q_UNUSED(arguments)
	Q_UNUSED(errorString)

	qRealCoreSettings::loadOnStartUp();

	Core::ActionContainer *menu = Core::ActionManager::createMenu(Constants::MENU_ID);
	menu->menu()->setTitle(tr(Constants::DISPLAY_NAME));
	menu->setOnAllDisabledBehavior(Core::ActionContainer::Show);
	Core::ActionManager::actionContainer(Core::Constants::M_TOOLS)->addMenu(menu);

	m_checkFileAction = new QAction(tr(Constants::MSG_ACTION_CHECKFILE), this);
	Core::Command *cmd = Core::ActionManager::registerAction(m_checkFileAction
			, Constants::ACTION_CHECKFILE
			, Core::Context(Core::Constants::C_GLOBAL));
	menu->addAction(cmd);
	connect(m_checkFileAction, SIGNAL(triggered()), m_veraTool, SLOT(checkCurrentFile()));

	m_checkProjectAction = new QAction(
			tr(Constants::MSG_ACTION_CHECKPROJECT)
			, this);
	cmd = Core::ActionManager::registerAction(m_checkProjectAction
			, Constants::ACTION_CHECKPROJECT
			, Core::Context(Core::Constants::C_GLOBAL));
	menu->addAction(cmd);
	connect(m_checkProjectAction, SIGNAL(triggered()), m_veraTool, SLOT(checkCurrentProject()));

	addAutoReleasedObject(new VeraOptionsPage(m_veraSettings, this));
	updateActions();

	return true;
}

void QRealPlugin::updateActions(Core::IEditor *editor)
{
	const bool enabled = (editor && editor->document()->id() == CppEditor::Constants::CPPEDITOR_ID);

	m_checkFileAction->setEnabled(enabled);
	m_checkProjectAction->setEnabled(enabled);
}


void QRealPlugin::extensionsInitialized()
{
	if (const Core::EditorManager * editorManager = Core::EditorManager::instance()) {
		connect(editorManager, &Core::EditorManager::currentEditorChanged
			, this, &QRealPlugin::updateActions);
	}
}

ExtensionSystem::IPlugin::ShutdownFlag QRealPlugin::aboutToShutdown()
{
	return SynchronousShutdown;
}

//shows in general message
void QRealPlugin::showOutput(const QString &output)
{
	Core::MessageManager::write(output);
}
