/* Copyright 2016 Guzel Garifullina
 *
 * Licensed under the GNU General Public License, Version 3.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.gnu.org/licenses/gpl-3.0.en.html */

#undef QT_NO_CAST_FROM_ASCII

#include "veratool.h"
#include "qrealpluginplugin.h"

#include <coreplugin/actionmanager/actioncontainer.h>
#include <coreplugin/editormanager/editormanager.h>
#include <coreplugin/editormanager/ieditor.h>
#include <projectexplorer/project.h>
#include <projectexplorer/projecttree.h>
#include <utils/fileutils.h>

#include <QProcess>
#include <QString>

using namespace QReal::Internal;

VeraTool::VeraTool() :
	m_veraSettings(new VeraSettings())
{
}
VeraTool::~VeraTool()
{
	delete m_veraSettings;
}

VeraSettings *VeraTool::getVeraSettings()
{
	return m_veraSettings;
}

void VeraTool::checkCurrentFile()
{
	if (!QFile::exists(m_veraSettings->command())) {
		QRealPlugin::showOutput("Wrong vera++ command specified\n");
		return;
	}
	QString file = m_getOpenedFile();
	m_checkFile(file);
}

//returns if error occured
bool VeraTool::m_checkFile(QString file)
{
	QStringList fileOp = QStringList(file);
	QProcess process;

	process.start(m_veraSettings->command(), m_veraSettings->veraOptions() + fileOp);
	process.waitForFinished(2000);

	QString error = process.readAllStandardError();
	if (!error.isEmpty()) {
		QString context = "Error in running vera++:\n";
		QRealPlugin::showOutput(context + error);
		return true;
	}

	QString output = process.readAllStandardOutput();
	if (!output.isEmpty()) {
		QString context = QLatin1String("Style problems in file ")
			+ file + QLatin1String(":\n");
		QRealPlugin::showOutput(context + output);
		return false;
	}

	QRealPlugin::showOutput(QLatin1String("vera++:\nEverything Ok in file ")
		+ file + QLatin1String(":\n"));
	return false;
}

void VeraTool::checkCurrentProject()
{
	if (!QFile::exists(m_veraSettings->command())) {
		QRealPlugin::showOutput("Wrong vera++ command specified\n");
		return;
	}

	QStringList files = m_getOpenedProjectFiles();
	for (QString f : files) {
		if (m_checkFile(f)) {
			return;
		}
	}
}

QString VeraTool::m_getOpenedFile() const
{
	return Core::EditorManager::currentEditor()->document()->filePath().toString();
}

QStringList VeraTool::m_getOpenedProjectFiles() const
{
	ProjectExplorer::Project *project = ProjectExplorer::ProjectTree::currentProject();
	return project->files(ProjectExplorer::Project::FilesMode::SourceFiles);
}
