/*
 * Copyright (C) 2017 ~ 2018 Deepin Technology Co., Ltd.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef DEEPIN_APPSTORE_UI_CHANNEL_SETTINGS_PROXY_H
#define DEEPIN_APPSTORE_UI_CHANNEL_SETTINGS_PROXY_H

#include <QObject>
#include <QVariantMap>

namespace dstore
{

/**
 * Expose backend settings to web page.
 */
class SettingsProxy : public QObject
{
    Q_OBJECT
public:
    explicit SettingsProxy(QObject *parent = nullptr);

Q_SIGNALS:
    void raiseWindowRequested();
    void fontChangeRequested(const QString &fontFamily, int pixelSize);
    void authStateChanged();

public Q_SLOTS:
    /**
     * Returns metadata server and operation server address.
     * @return
     */
    const QVariantMap getSettings();

    /**
     * Return authorization state.
     * @return
     */
    quint32 getAuthorizationState();

    /**
     * Allow auto install software
     */
    void setAutoInstall(bool autoinstall);

    /**
     * Request to open url in external web browser.
     * @param url
     */
    void openUrl(const QString &url);


    /**
     * Raise main window.
     */
    void raiseWindow();

    /**
     * Get app version
     */
    QString getAppVersion();
};

}  // namespace dstore

#endif  // DEEPIN_APPSTORE_UI_CHANNEL_SETTINGS_PROXY_H
