/* BEGIN_COMMON_COPYRIGHT_HEADER
 * (c)LGPL2+
 *
 * Razor - a lightweight, Qt based, desktop toolset
 * http://razor-qt.org
 *
 * Copyright: 2013 Razor team
 * Authors:
 *   Stephan Platz <razor@paalsteek.de>
 *
 * This program or library is free software; you can redistribute it
 * and/or modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.

 * You should have received a copy of the GNU Lesser General
 * Public License along with this library; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301 USA
 *
 * END_COMMON_COPYRIGHT_HEADER */

#ifndef BRIGHTNESSPOPUP_H
#define BRIGHTNESSPOPUP_H

#include <QtGui/QDialog>

class QSlider;
class QPushButton;
class QLabel;
class Backlight;

class BrightnessPopup : public QDialog
{
    Q_OBJECT
public:
    BrightnessPopup(QWidget* parent = 0);

    void open(QPoint pos, Qt::Corner anchor);
    void handleWheelEvent(QWheelEvent *event);

    QSlider *brightnessSlider() const { return m_brightnessSlider; }

		void setBacklight(Backlight *backlight);

signals:
    void mouseEntered();
    void mouseLeft();

    void brightnessChanged(int value);

protected:
    void resizeEvent(QResizeEvent *event);
    void enterEvent(QEvent *event);
    void leaveEvent(QEvent *event);

private slots:
    void handleSliderValueChanged(int value);
    void handleDeviceBrightnessChanged(int brightness = -1);

private:
    void realign();

    QSlider *m_brightnessSlider;
    QPoint m_pos;
    Qt::Corner m_anchor;
		Backlight *m_backlight;
};

#endif // BRIGHTNESSPOPUP_H
