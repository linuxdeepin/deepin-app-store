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

#ifndef DEEPIN_APPSTORE_UI_STORE_DAEMON_PROXY_H
#define DEEPIN_APPSTORE_UI_STORE_DAEMON_PROXY_H

#include <QDebug>
#include <QObject>
#include <QThread>
#include <QVariantMap>
#include <QJsonArray>

#include "services/search_result.h"
#include "services/store_daemon_manager.h"

namespace dstore
{

class StoreDaemonProxy : public QObject
{
    Q_OBJECT
public:
    explicit StoreDaemonProxy(QObject *parent = nullptr);
    ~StoreDaemonProxy() override;

Q_SIGNALS:
    // void isDbusConnectedReply(bool state);

    /**
     * Emitted when apt-get clean is called.
     */
    void clearArchives();

    /**
    * Emitted when JobList property changed.
    * @param jobs
    */
    void jobListChanged(const QStringList &jobs);

public Q_SLOTS:
    /**
     * Check connecting to backend app store daemon or not.
     */
    bool isDBusConnected()
    {
        return manager_->isDBusConnected();
    }

    // Store Manager methods:
    /**
     * Query application version information.
     * @param apps
     */
    QVariantMap query(const QVariantList &apps)
    {
        return manager_->query(apps);
    }

    /**
     * Get deb package size
     * @param app_name
     */
    QVariantMap queryDownloadSize(const QVariantList &apps)
    {
        return manager_->queryDownloadSize(apps);
    }

    /**
     * Get a list of installed packages.
     */
    QVariantMap installedPackages()
    {
        return manager_->installedPackages();
    }

    /**
     * Request to open installed application.
     * @param app_name
     */
    void openApp(const QVariant &app)
    {
        return manager_->openApp(app);
    }

    /**
     * apt-get install xxx, to install or upgrade a program.
     * @param app_name
     * @param app_local_name App local name is used by lastore daemon
     */
    QVariantMap installPackages(const QVariantList &apps)
    {
        return manager_->installPackage(apps);
    }

    /**
     * apt-get upgrade xxx
     * @param app_name
     */
    QVariantMap updatePackages(const QVariantList &apps)
    {
        return manager_->updatePackage(apps);
    }

    /**
     * apt-get remove xxx
     * @param app_name
     */
    QVariantMap removePackages(const QVariantList &apps)
    {
        return manager_->removePackage(apps);
    }

    /**
     * Returns all of jobs existing in backend.
     * @return stringList
     */
    QVariantMap jobList()
    {
        return manager_->jobList();
    }

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
    QVariantMap getJobInfo(const QString &job)
    {
        return manager_->getJobInfo(job);
    }

    QVariantMap getJobsInfo(const QStringList &jobs)
    {
        return manager_->getJobsInfo(jobs);
    }


    /**
     * Clean up a specific job.
     * @param job
     */
    QVariantMap cleanJob(const QString &job)
    {
        return manager_->cleanJob(job);
    }

    /**
     * Pause a running job
     * @param job
     */
    QVariantMap pauseJob(const QString &job)
    {
        return manager_->pauseJob(job);
    }

    /**
     * Resume a paused job
     * @param job
     */
    QVariantMap startJob(const QString &job)
    {
        return manager_->startJob(job);
    }

    /**
     * Try to fix installation error.
     */
    QVariantMap fixError(const QString &error_type)
    {
        return manager_->fixError(error_type);
    }

    QString test()
    {
        QThread::sleep(3);
        return "this is test";
    }

    // TODO: just for search
    void updateAppList(const SearchMetaList &app_list)
    {
        return manager_->updateAppList(app_list);
    }

private:
    void initConnections();

    QThread *manager_thread_ = nullptr;
    StoreDaemonManager *manager_ = nullptr;
};

}  // namespace dstore

#endif  // DEEPIN_APPSTORE_UI_STORE_DAEMON_PROXY_H
