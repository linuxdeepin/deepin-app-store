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

#include "ui/widgets/title_bar_menu.h"

#include <QDebug>

#include "services/settings_manager.h"

namespace dstore
{

TitleBarMenu::TitleBarMenu(bool support_sign_in, QWidget *parent)
    : QMenu(parent),
      support_sign_in_(support_sign_in)
{

    this->initActions();
}

TitleBarMenu::~TitleBarMenu()
{

}

void TitleBarMenu::setThemeName(QString theme_name)
{
    theme_name_ = theme_name;
    SettingsManager::instance()->setThemeName(theme_name_);

   /* if (theme_name_ == "light") {
        switch_theme_action_->setChecked(false);
    } else {
        switch_theme_action_->setChecked(true);
    }*/
}

void TitleBarMenu::initActions()
{
    /*if (support_sign_in_) {
        this->addAction(QObject::tr("Recommend App"),
                        this, &TitleBarMenu::recommendAppRequested);
    }*/


    this->addAction(QObject::tr("Clear cache"),
                    this, &TitleBarMenu::clearCacheRequested);

    theme_name_ = SettingsManager::instance()->themeName();
    /*switch_theme_action_ = this->addAction(QObject::tr("Dark theme"));
    switch_theme_action_->setCheckable(true);
    connect(switch_theme_action_, &QAction::triggered,
            this, &TitleBarMenu::onThemeActionTriggered);*/
    this->setThemeName(theme_name_);

    privacy_agreement_action_ = this->addAction(QObject::tr("Privacy Policy"));
    connect(privacy_agreement_action_, &QAction::triggered,
            this, &TitleBarMenu::privacyAgreementRequested);

    this->addSeparator();
}

/*void TitleBarMenu::onThemeActionTriggered()
{
    if (theme_name_ == "light") {
        theme_name_ = "dark";
    } else {
        theme_name_ = "light";
    }
    this->setThemeName(theme_name_);
    emit this->switchThemeRequested(theme_name_);
}*/


}  // namespace dstore
