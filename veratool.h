/* Copyright 2016 Guzel Garifullina
 *
 * Licensed under the GNU General Public License, Version 3.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.gnu.org/licenses/gpl-3.0.en.html */

#pragma once

#include "verasettings.h"

#include <QObject>
#include <QString>
#include <QStringList>

namespace QReal{
namespace Internal{

class VeraTool : public QObject
{
	Q_OBJECT
public:
	VeraTool();
	VeraSettings * getVeraSettings();
	~VeraTool();
private:
	VeraSettings * m_veraSettings;
	QString m_getOpenedFile() const ;
	QStringList m_getOpenedProjectFiles() const;
	bool m_checkFile(QString file);
private slots:
	void checkCurrentFile();
	void checkCurrentProject();
};

} // namespace Internal
} // namespace QReal

