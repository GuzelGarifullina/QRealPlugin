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

namespace QReal{
namespace Internal{

class VeraTool : public QObject
{
	Q_OBJECT
public:
	VeraTool();
private:
	QStringList m_basicOptions;
	const QString m_command =  QLatin1String("vera++"); //"echo";
	const QString m_dir = QLatin1String("/home/guzel/Programming/qRealPlugin");
private slots:
	void checkFile();
	void checkProject() const;

};

} // namespace Internal
} // namespace QReal

