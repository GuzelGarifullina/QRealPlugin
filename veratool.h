/* Copyright 2016 Guzel Garifullina
 *
 * Licensed under the GNU General Public License, Version 3.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.gnu.org/licenses/gpl-3.0.en.html */

#pragma once

#include <QObject>
#include <QString>
#include <QStringList>

#include "verasettings.h"

namespace QReal{
namespace Internal{

class VeraTool : public QObject
{
	Q_OBJECT
public:
	VeraTool();
	~VeraTool();
private:
	QStringList m_basicOptions;

	VeraSettings * m_veraSettings;
	const QString m_command =  QLatin1String("/usr/local/bin/vera++"); //"echo";
	const QString m_dir = QLatin1String("/home/guzel/Programming/qRealPlugin");
	QString m_getOpenedFile() const ;
	QStringList m_getOpenedProjectFiles() const;

private slots:
	void checkFile();
	void checkProject();

};

} // namespace Internal
} // namespace QReal

