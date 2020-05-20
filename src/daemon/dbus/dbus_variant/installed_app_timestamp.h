/*
 * Copyright (C) 2018 Deepin Technology Co., Ltd.
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

#ifndef DEEPIN_APPSTORE_DBUS_DBUS_VARIANT_INSTALLED_APP_TIMESTAMP_H
#define DEEPIN_APPSTORE_DBUS_DBUS_VARIANT_INSTALLED_APP_TIMESTAMP_H

#include <QDBusArgument>
#include <QDebug>
#include <QList>
#include <QString>
#include <QVariant>

struct InstalledAppTimestamp {
 public:
  InstalledAppTimestamp();
  ~InstalledAppTimestamp();

  static void registerMetaType();

  inline bool operator==(const InstalledAppTimestamp& other) const {
    return this->pkg_name == other.pkg_name;
  }

  friend QDebug operator<<(QDebug debug, const InstalledAppTimestamp& info);
  friend QDBusArgument& operator<<(QDBusArgument& argument,
                                   const InstalledAppTimestamp& info);
  friend QDataStream& operator<<(QDataStream& stream,
                                 const InstalledAppTimestamp& info);
  friend const QDBusArgument& operator>>(const QDBusArgument& argument,
                                         InstalledAppTimestamp& info);
  friend const QDataStream& operator>>(QDataStream& stream,
                                       InstalledAppTimestamp& info);

  QString pkg_name;
  qlonglong timestamp;
};

typedef QList<InstalledAppTimestamp> InstalledAppTimestampList;
Q_DECLARE_METATYPE(InstalledAppTimestamp);
Q_DECLARE_METATYPE(InstalledAppTimestampList);

#endif  // DEEPIN_APPSTORE_DBUS_DBUS_VARIANT_INSTALLED_APP_TIMESTAMP_H
