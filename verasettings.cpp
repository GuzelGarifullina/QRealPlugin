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

#include <QDebug>
#include <QDir>
#include <QFileInfo>

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
		if (key == QLatin1String("VeraCommand")) {
			setCommand(s->value(key).toString());
		} else if (m_settings.contains(key)) {
			m_settings[key] = s->value(key);
		} else {
			s->remove(key);
		}
	}
	s->endGroup();

	//need to renew m_rules
	m_veraOptions();
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

QString VeraSettings::getRulePath() const
{
	return m_settings.value(QLatin1String(QReal::Constants::CORE_VERA_RULES))
		.toString();
}

void VeraSettings::setRulePath(const QString &rules)
{
	m_settings.insert(QLatin1String(QReal::Constants::CORE_VERA_RULES)
		, QVariant(rules));
	//need to renew m_rules
	m_veraOptions();
}

QStringList VeraSettings::veraOptions() const
{
	return m_rules;
}
void VeraSettings::m_veraOptions()
{
	m_rules = QStringList();
	QString rules = getRulePath();

	if (rules.isEmpty()) {
		return;
	}
	QFileInfo fileInfo(rules);
	m_rules << QLatin1String("--profile")
			<< fileInfo.fileName();

	QStringList fileParts = fileInfo.absolutePath().split(QLatin1Char('/'));
	fileParts.removeLast(); //profiles dir
	QString root = fileParts.join(QDir::separator());
	m_rules << QLatin1String("--root")
		<< root;
}
