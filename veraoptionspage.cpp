/* Copyright 2016 Guzel Garifullina
 *
 * Licensed under the GNU General Public License, Version 3.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.gnu.org/licenses/gpl-3.0.en.html */

#include "veraoptionspage.h"
#include "qrealpluginconstants.h"
#include "qrealcoresettings.h"
#include "ui_veraoptionspage.h"
#include "verasettings.h"

#include <coreplugin/icore.h>

namespace QReal {
namespace Internal {

VeraOptionsPageWidget::VeraOptionsPageWidget(VeraSettings *settings
	, QWidget *parent) :
	QWidget(parent)
	, ui(new Ui::VeraOptionsPage)
	, m_settings(settings)
{
	ui->setupUi(this);
	ui->command->setExpectedKind(Utils::PathChooser::ExistingCommand);
	connect(ui->command, &Utils::PathChooser::validChanged, ui->options, &QWidget::setEnabled);
	ui->rules->setExpectedKind(Utils::PathChooser::File);
}

VeraOptionsPageWidget::~VeraOptionsPageWidget()
{
	delete ui;
}

void VeraOptionsPageWidget::restore()
{
	ui->command->setPath(m_settings->command());
	ui->rules->setPath(m_settings->getRulePath());
	ui->revertSettings->setChecked(false);
}

void VeraOptionsPageWidget::apply()
{
	m_settings->setCommand(ui->command->path());
	m_settings->setRulePath(ui->rules->path());
	m_settings->save();
	if (ui->revertSettings->isChecked()) {
		qRealCoreSettings::loadDefaultSystemSettings();
		ui->revertSettings->setChecked(false);
	}
}

VeraOptionsPage::VeraOptionsPage(VeraSettings *settings, QObject *parent) :
	IOptionsPage(parent)
	, m_settings(settings)
{
	setId(QReal::Constants::VERA_OPTION_ID);
	setDisplayName(tr("Vera"));
	setCategory(QReal::Constants::OPTION_CATEGORY);
	setDisplayCategory(QLatin1String(QReal::Constants::DISPLAY_NAME));
	//setCategoryIcon(Constants::OPTION_CATEGORY_ICON);
}

QWidget *VeraOptionsPage::widget()
{
	m_settings->read();

	if (!m_widget) {
		m_widget = new VeraOptionsPageWidget(m_settings);
	}
	m_widget->restore();

	return m_widget;
}

void VeraOptionsPage::apply()
{
	if (m_widget) {
		m_widget->apply();
	}
}

void VeraOptionsPage::finish()
{
	//nothing to do there
}

} // namespace Internal
} // namespace QReal
