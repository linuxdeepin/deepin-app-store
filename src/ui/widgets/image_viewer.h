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

#ifndef DEEPIN_APPSTORE_UI_WIDGETS_IMAGE_VIEWER_H
#define DEEPIN_APPSTORE_UI_WIDGETS_IMAGE_VIEWER_H

#include <QDialog>
#include <DSpinner>
#include <DIconButton>
using namespace  Dtk::Widget;

class QLabel;

namespace dstore {

class ImageViewer : public QDialog {
  Q_OBJECT
 public:
  explicit ImageViewer(QWidget* parent = nullptr);
  ~ImageViewer() override;

 signals:
  /**
   * Emitted when previous-button is clicked.
   */
  void previousImageRequested();

  /**
   * Emitted when next-button is clicked.
   */
  void nextImageRequested();

 public slots:
  /**
   * Open a local image file and render in image box.
   * @param filepath
   */
  void open(const QString& filepath);

  /**
   * Open a raw pixmap and render in popup window.
   * Note that this pixmap object is duplicated and might be scaled if needed.
   * @param pixmap
   */
  void openPixmap(QPixmap pixmap);

  /**
   * Show image loading indicator.
   */
  void showIndicator();

 protected:
  void mousePressEvent(QMouseEvent* event) override;

  void paintEvent(QPaintEvent* event) override;

 private:
  void initUI();
  void initConnection();

  QLabel* img_label_ = nullptr;
  Dtk::Widget::DIconButton* close_button_ = nullptr;
  Dtk::Widget::DIconButton* previous_button_ = nullptr;
  Dtk::Widget::DIconButton* next_button_ = nullptr;
  Dtk::Widget::DSpinner* spinner_ = nullptr;
};

}  // namespace dstore

#endif  // DEEPIN_APPSTORE_UI_WIDGETS_IMAGE_VIEWER_H
