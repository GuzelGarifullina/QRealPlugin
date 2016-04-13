/* Copyright  2016 Guzel Garifullina
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License. */

#pragma once

#include <QtCore/qglobal.h>
#include <QObject>

#include <QSettings>

namespace QReal{
namespace Internal{


class qRealCoreSettings: public QObject
{
	Q_OBJECT
public:
	qRealCoreSettings();
	~qRealCoreSettings();

	//change qreal plugin settings
	void saveSettings() const;

	//load default settings on first startup
	//plugin and system
	void loadDefaultSettings();
private:
	QSettings *m_settings;
	bool m_isFirtTimeLoaded();
	void m_loadDefaultPluginSettings();
	void m_loadDefaultSystemSettings();
	void m_loadFromFile(QString qRealPluginPath);
	void m_loadLicense(QString qRealPluginPath);
	void m_loadDocumentation(QString qRealPluginPath);
	void m_loadBeautifierSettings();
signals:
	void settingsChanged();
};

} // namespace Internal
} // namespace QReal


