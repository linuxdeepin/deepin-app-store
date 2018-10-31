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

#ifndef DEEPIN_APPSTORE_SERVICES_METADATA_MANAGER_H
#define DEEPIN_APPSTORE_SERVICES_METADATA_MANAGER_H

#include <QDir>
#include <QObject>
#include <QMutex>

#include "dbus/dbus_variant/app_metadata.h"

namespace dstore {

class MetadataCacheWorker;

// MetadataManager manages app metadata cache and app icon cache.
// Itself works in foreground thread, any http requests are sent in background.
class MetadataManager : public QObject {
  Q_OBJECT
 public:
  explicit MetadataManager(QObject* parent = nullptr);
  ~MetadataManager() override;

  /**
   * Get application icon file of specific app.
   * @param app_name
   * @return Absolute path to app icon file.
   */
  QString getAppIcon(const QString& app_name);

  /**
   * @brief return json format of metainfo
   * @param app_name_list
   * @return
   */
  QString getAppMetadataList(const QStringList &app_name_list);

  /**
   * Notify manager to download all of application icons.
   */
  void downloadAppIcons();

 private:
  bool downloadMetadata();
  bool parseMetadata(const QString& index_file, const QString& metadata_file);
  QJsonObject findMetadata(const QString& app_name);

  MetadataCacheWorker* cache_worker_ = nullptr;
  QDir cache_dir_;
  QDir icon_dir_;
  QString metadata_server_;
  QString operation_server_;
  QMutex mutex_;

//  QList<AppMetadata> apps_;
  QMap<QString, QJsonObject> apps_;
};

}  // namespace dstore

#endif  // DEEPIN_APPSTORE_SERVICES_METADATA_MANAGER_H
