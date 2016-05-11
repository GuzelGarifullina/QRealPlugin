/* Copyright 2016 Guzel Garifullina
 *
 * Licensed under the GNU General Public License, Version 3.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.gnu.org/licenses/gpl-3.0.en.html */

#include "verasettings.h"
#include "qrealpluginconstants.h"

#include <coreplugin/icore.h>
#include <QFileInfo>
#include <QDir>

#include <QDebug>

using namespace QReal::Internal;

VeraSettings::VeraSettings()
{
	m_settings.insert(QLatin1String(QReal::Constants::CORE_VERA_RULES)
		, QVariant(QLatin1String("")));
	read();
}

VeraSettings::~VeraSettings()
{

}

void VeraSettings::read()
{
	QSettings *s = Core::ICore::settings();

	s->beginGroup(QLatin1String(QReal::Constants::CORE_SETTINGS_GROUP));

	const QStringList keys = s->allKeys();
	for (const QString &key : keys) {
		if (key == QLatin1String("command")) {
			setCommand(s->value(key).toString());
		} else if (m_settings.contains(key)) {
			m_settings[key] = s->value(key);
		} else {
			s->remove(key);
		}
	}
	s->endGroup();
}

void VeraSettings::save()
{
	QSettings *s = Core::ICore::settings();

	s->beginGroup(QLatin1String(QReal::Constants::CORE_SETTINGS_GROUP));
	QMap<QString, QVariant>::const_iterator iSettings = m_settings.constBegin();
	while (iSettings != m_settings.constEnd()) {
		s->setValue(iSettings.key(), iSettings.value());
		++iSettings;
	}
	s->setValue(QLatin1String("VeraCommand"), m_command);
	s->endGroup();
}

QString VeraSettings::command() const
{
	return m_command;
}

void VeraSettings::setCommand(const QString &command)
{
	m_command = command;
}

QString VeraSettings::getRules() const
{
	return m_settings.value(QLatin1String(QReal::Constants::CORE_VERA_RULES))
		   .toString();
}

void VeraSettings::setRules(QString &rules)
{
	m_settings.insert(QLatin1String(QReal::Constants::CORE_VERA_RULES)
		, QVariant(rules));
}

QStringList VeraSettings::veraOptions() const
{
	QStringList options;
	QString rules = getRules();

	if (rules.isEmpty()) {
		return options;
	}
	QFileInfo fileInfo(rules);
	options << QLatin1String("--profile")
			<< fileInfo.fileName();

	QStringList fileParts = fileInfo.absolutePath().split(QLatin1Char('/'));
	fileParts.removeLast(); //filename
	fileParts.removeLast(); // profiles dir
	QString root = fileParts.join(QDir::separator());
	options << QLatin1String("--root")
			<< root;
	qDebug() << root;

	return options;
}
