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

#ifndef DEEPIN_APPSTORE_SERVICES_STORE_DAEMON_MANAGER_H
#define DEEPIN_APPSTORE_SERVICES_STORE_DAEMON_MANAGER_H

#include <QObject>
#include <QScopedPointer>
#include "services/search_result.h"

namespace dstore
{

class StoreDaemonManagerPrivate;
class StoreDaemonManager : public QObject
{
    Q_OBJECT
public:
    explicit StoreDaemonManager(QObject *parent = nullptr);
    ~StoreDaemonManager() override;

Q_SIGNALS:
    /**
     * Emitted when JobList property changed.
     * @param jobs
     */
    void jobListChanged(const QStringList &jobs);


    /*
        system login state change
        info: Map(("AccessToken", QVariant(QString, "EIhuP262Qi2vyaPSG_196Q"))("Expiry", QVariant(qlonglong, 1544583742))("HardwareID", QVariant(QString, "bdb3ff930e39c8726b29f2252b132b82da494f492ba41fa2f4b157951069b470"))("Token", QVariant(QString, "0cb068641e132fcba475276f0a0e590b"))("UserID", QVariant(qlonglong, 17898))("loggedIn", QVariant(bool, true))) or {}
    */
    void loginStateChanged(QVariantMap info);

public Q_SLOTS:
    /**
     * @brief clearArchives clean apt arvhives
     */
    void clearArchives();
    QVariantMap fixError(const QString &error_type);

    /**
     * Check connecting to backend app store daemon or not.
     */
    bool isDBusConnected();

    /**
     * @brief openApp by app_name
     * @param app_name: TODO, open by packageURI
     */
    void openApp(const QVariant &app);

    // TODO: remove
    // update all list of app
    void updateAppList(const SearchMetaList &app_list);

    QVariantMap installedPackages();

    QVariantMap query(const QVariantList &apps);

    QVariantMap queryDownloadSize(const QVariantList &apps);

    /**
     * apt-get install xxx
     * @param app_name
     * @param app_local_name
     */
    QVariantMap installPackage(const QVariantList &apps);

    /**
     * apt-get upgrade xxx
     * @param app_name
     * @param app_local_name
     */
    QVariantMap updatePackage(const QVariantList &apps);
    /**
     * apt-get remove xxx
     * @param app_name
     * @param app_local_name
     */
    QVariantMap removePackage(const QVariantList &apps);

    QVariantMap queryVersions(const QStringList &apps);

    /**
     * Clean up a specific job.
     * @param job
     */
    QVariantMap cleanJob(const QString &job);

    /**
     * Pause a running job
     * @param job
     */
    QVariantMap pauseJob(const QString &job);

    /**
     * Resume a paused job
     * @param job
     */
    QVariantMap startJob(const QString &job);


    /**
     * Get temporary job info.
     * * valid: bool, false if this job is invalid.
     * * id: string
     * * name: string
     * * status: string
     * * type: string
     * * speed: int64
     * * progress: double
     * * description: string
     * * cancelable: boolean
     * * packages: stringList
     */
    QVariantMap getJobInfo(const QString &job);

    QVariantMap getJobsInfo(const QStringList &jobs);

    /**
     * Returns all of jobs existing in backend.
     * @return stringList
     */
    QVariantMap jobList();

    void onJobListChanged();

private:
    QScopedPointer<StoreDaemonManagerPrivate> dd_ptr;
    Q_DECLARE_PRIVATE_D(qGetPtrHelper(dd_ptr), StoreDaemonManager)
};

}  // namespace dstore

#endif  // DEEPIN_APPSTORE_SERVICES_STORE_DAEMON_MANAGER_H
