/* Copyright 2016 Guzel Garifullina
 *
 * Licensed under the GNU General Public License, Version 3.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.gnu.org/licenses/gpl-3.0.en.html */

#pragma once

#include <QString>
#include <QMap>
#include <QVariant>
#include <QObject>

namespace QReal{
namespace Internal{

class VeraSettings : public QObject
{
	Q_OBJECT
public:
	VeraSettings();
	~VeraSettings();
	void read();
	void save();
	QString command() const;
	void setCommand (const QString &command);
	QString getRules() const ;
	void setRules(QString &rules);
	QStringList veraOptions() const;

private:
	QMap<QString, QVariant> m_settings;
	QString m_command = QLatin1String("vera++");
};

} // namespace Internal
} // namespace QReal

