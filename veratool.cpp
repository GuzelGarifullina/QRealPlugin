/* Copyright 2016 Guzel Garifullina
 *
 * Licensed under the GNU General Public License, Version 3.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.gnu.org/licenses/gpl-3.0.en.html */

#undef QT_NO_CAST_FROM_ASCII

#include "veratool.h"
#include <QDebug>
#include <QString>
#include <QProcess>
#include "qrealpluginplugin.h"

#include <coreplugin/editormanager/editormanager.h>
#include <coreplugin/editormanager/ieditor.h>
#include <projectexplorer/projecttree.h>
#include <projectexplorer/project.h>
#include <utils/fileutils.h>


using namespace QReal::Internal;
VeraTool::VeraTool()
{
	//m_basicOptions << "--root" << m_dir;
	// <<"--profile" << "allRules";
}
void VeraTool::checkFile()
{
	QString dir = "/home/guzel/Programming/qRealPlugin";
	QString file = dir + "/qRealCoreSettings.cpp";
	QStringList fileOp = QStringList(file);
	QProcess process;

	process.start(m_command, m_basicOptions + fileOp);
	process.waitForFinished(2000);

	QString error = process.readAllStandardError();
	if (!error.isEmpty()) {
		QString context = "Error in running vera++:\n";
		QRealPlugin::showOutput(error, context);
		return;
	}
	QString output = process.readAllStandardOutput();
	if (!output.isEmpty()) {
		QString context = "Problems in style:\n";
		QRealPlugin::showOutput(output, context);
		return;
	}
	QRealPlugin::showOutput("Everything Ok", "vera++:\n");
}
void VeraTool::checkProject()
{
	/*QStringList files = m_getOpenedProjectFiles();
	   for (QString f : files){
		QRealPlugin::showOutput(f,"");
	   }*/
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



