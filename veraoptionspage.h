/* Copyright 2016 Guzel Garifullina
 *
 * Licensed under the GNU General Public License, Version 3.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.gnu.org/licenses/gpl-3.0.en.html */

#pragma once

#include "verasettings.h"
#include "ui_veraoptionspage.h"

#include <coreplugin/dialogs/ioptionspage.h>

#include <QPointer>
#include <QWidget>

namespace QReal {
namespace Internal {

class VeraOptionsPageWidget : public QWidget
{
	Q_OBJECT

public:
	explicit VeraOptionsPageWidget(VeraSettings *settings, QWidget *parent = nullptr);
	virtual ~VeraOptionsPageWidget();
	void restore();
	void apply();

private:
	Ui::VeraOptionsPage *ui;
	VeraSettings *m_settings;
};

class VeraOptionsPage : public Core::IOptionsPage
{
	Q_OBJECT

public:
	explicit VeraOptionsPage(VeraSettings *settings, QObject *parent = nullptr);
	QWidget *widget() override;
	void apply() override;
	void finish() override;

private:
	QPointer<VeraOptionsPageWidget> m_widget;
	VeraSettings *m_settings;
};

} // namespace Internal
} // namespace QReal
