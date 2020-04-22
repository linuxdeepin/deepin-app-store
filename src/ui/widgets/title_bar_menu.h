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

#ifndef DEEPIN_APPSTORE_UI_WIDGETS_TOOL_BAR_MENU_H
#define DEEPIN_APPSTORE_UI_WIDGETS_TOOL_BAR_MENU_H

#include <QMenu>
#include <QVariantMap>

namespace dstore {

class TitleBarMenu : public QMenu {
  Q_OBJECT

 public:
  explicit TitleBarMenu(bool support_sign_in, QWidget* parent = nullptr);
  ~TitleBarMenu() override;

public slots:
  void privacyAgreementDialogRequested();

 signals:
  void switchThemeRequested(QString themeName);
  void clearCacheRequested();
  void privacyAgreementRequested();

 private:
  void initActions();

  QAction* privacy_agreement_action_ = nullptr;
};

}  // namespace dstore

#endif // DEEPIN_APPSTORE_UI_WIDGETS_TOOL_BAR_MENU_H
