/*
 * Copyright (C) 2019 ~ 2020 Union Tech Co., Ltd.
 *
 * Author:     zhoutao <zhoutao@uniontech.com>
 *
 * Maintainer: zhoutao <zhoutao@uniontech.com>
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

#ifndef METADATAMANAGER_H
#define METADATAMANAGER_H

#include <QDebug>
#include <QDBusInterface>
#include <QTimer>
#include <QThread>
#include <QSqlTableModel>
#include <QSqlRecord>
#include <QVariant>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

#include "../../dbus/dbus_variant/app_version.h"
#include "../../dbus/dbus_variant/installed_app_info.h"
#include "../../dbus/dbus_variant/installed_app_timestamp.h"
#include "tcp_server.h"

typedef struct CacheAppInfo{
    QString      Category;
    QString      PackageName;
    QHash<QString,QString>  LocaleName;
}cacheAppInfo;

class WorkerDataBase : public QObject
{
  Q_OBJECT
public:
    WorkerDataBase(QObject *parent = nullptr);
    ~WorkerDataBase();

public slots:
  void updateCache();
  QString getPackageDesktop(QString packageName);
  qlonglong getAppInstalledTime(QString id);
  bool compareVersion(QString localVersion, QString remoteVersion);
signals:
  void resultReady(const InstalledAppInfoList listInstalledInfo,const QHash<QString,qlonglong> listAppsSize,const QHash<QString,AppVersion> listApps);
};

class MetaDataManagerPrivate;
class MetaDataManager : public QObject, data_proc_inerface
{
    Q_OBJECT
public:
    explicit MetaDataManager(QDBusInterface *lastoreDaemon,QObject *parent = nullptr);
    ~MetaDataManager();
    InstalledAppInfoList listInstalled();
    AppVersionList queryVersion(const QStringList &idList);
    qlonglong queryDownloadSize(const QString &id);
    void updateSource();
    QDBusObjectPath addJob(QDBusObjectPath);
    QList<QDBusObjectPath> getJobList();

protected:
    void msg_proc(QByteArray &data, QTcpSocket *sock) override;
    void disconnect_proc(QString &str) override;

private:
    tcp_server server;

signals:
    void jobListChanged();
    void updateCache();
    void packageUpdated(QString CmdType,QString PackageName ,QString PackageVersion);

public slots:
    void cleanService(QStringList jobList);
    void jobController(QString cmd, QString jobId);
    void updateJobList();

private:
    QScopedPointer<MetaDataManagerPrivate> d_ptr;
    Q_DECLARE_PRIVATE_D(qGetPtrHelper(d_ptr), MetaDataManager)

    QThread thread;
    WorkerDataBase *worker;
    QDBusInterface *m_pLastoreDaemon;
};

#endif // METADATAMANAGER_H
