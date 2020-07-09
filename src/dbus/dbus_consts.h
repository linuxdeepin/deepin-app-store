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

#ifndef DEEPIN_APPSTORE_DBUS_DBUS_CONSTS_H
#define DEEPIN_APPSTORE_DBUS_DBUS_CONSTS_H

namespace dstore {

extern const char kAppStoreDbusService[];
extern const char kAppStoreDbusPath[];
extern const char kAppStoreDbusInterface[];

extern const char kAppstoreDaemonService[];
extern const char kAppstoreDaemonPath[];
extern const char kAppstoreDaemonInterface[];

extern const char kAppstoreDaemonSettingsPath[];
extern const char kAppstoreDaemonSettingsInterface[];

extern const char kLastoreDebDbusPath[];
extern const char kLastoreDebDbusService[];

extern const char kLastoreDebJobService[];

extern const char kLicenseService[];
extern const char kLicenseInfoPath[];
extern const char kLicenseInfoInterface[];

extern const char kAppearanceService[];
extern const char kAppearancePath[];
extern const char kAppearanceInterface[];

extern const char kNetworkService[];
extern const char kLauncherPath[];
extern const char kLauncherInterface[];
extern const char kNetworkProxyChainsPath[];
extern const char kNetworkProxyChainsInterface[];
}  // namespace dstore

#endif  // DEEPIN_APPSTORE_DBUS_DBUS_CONSTS_H
