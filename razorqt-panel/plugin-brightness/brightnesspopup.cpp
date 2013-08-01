/* BEGIN_COMMON_COPYRIGHT_HEADER
 * (c)LGPL2+
 *
 * Razor - a lightweight, Qt based, desktop toolset
 * http://razor-qt.org
 *
 * Copyright: 2012 Razor team
 * Authors:
 *   Johannes Zellner <webmaster@nebulon.de>
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

#include "brightnesspopup.h"
#include "backlight.h"

#include <qtxdg/xdgicon.h>

#include <QtGui/QSlider>
#include <QtGui/QVBoxLayout>
#include <QtGui/QApplication>
#include <QtGui/QDesktopWidget>
#include <QtCore/QProcess>

#include <QtCore/QDebug>

BrightnessPopup::BrightnessPopup(QWidget* parent):
    QDialog(parent, Qt::Dialog | Qt::WindowStaysOnTopHint | Qt::CustomizeWindowHint | Qt::X11BypassWindowManagerHint),
    m_pos(0,0),
    m_anchor(Qt::TopLeftCorner),
		m_backlight(0)
{
    m_brightnessSlider = new QSlider(Qt::Vertical, this);
    m_brightnessSlider->setTickPosition(QSlider::TicksBothSides);
    m_brightnessSlider->setTickInterval(10);

    QVBoxLayout *l = new QVBoxLayout(this);
    l->setSpacing(0);
    l->setMargin(2);

    l->addWidget(m_brightnessSlider, 0, Qt::AlignHCenter);

    connect(m_brightnessSlider, SIGNAL(valueChanged(int)), this, SLOT(handleSliderValueChanged(int)));
}

void BrightnessPopup::setBacklight(Backlight* backlight)
{
	if ( m_backlight == backlight )
		return;

	if ( m_backlight )
		disconnect(m_backlight);

	m_backlight = backlight;

	if ( m_backlight )
	{
		qDebug() << "Max:" << m_backlight->getMaxBrightness();
		qDebug() << "Cur:" << m_backlight->getCurBrightness();
		m_brightnessSlider->setMaximum(m_backlight->getMaxBrightness());
		m_brightnessSlider->setValue(m_backlight->getCurBrightness());

		//TODO: handle changes in the device brightness
	}

}

void BrightnessPopup::enterEvent(QEvent *event)
{
    emit mouseEntered();
}

void BrightnessPopup::leaveEvent(QEvent *event)
{
    emit mouseLeft();
}

void BrightnessPopup::handleSliderValueChanged(int value)
{
		if ( m_backlight )
			m_backlight->setCurBrightness(value);
}

void BrightnessPopup::handleDeviceBrightnessChanged(int brightness)
{
    m_brightnessSlider->setValue(brightness);
    //updateStockIcon();
}

void BrightnessPopup::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    realign();
}

void BrightnessPopup::open(QPoint pos, Qt::Corner anchor)
{
    m_pos = pos;
    m_anchor = anchor;
    realign();
    show();
}

void BrightnessPopup::handleWheelEvent(QWheelEvent *event)
{
    m_brightnessSlider->event(reinterpret_cast<QEvent*>(event));
}

void BrightnessPopup::realign()
{
    QRect rect;
    rect.setSize(sizeHint());
    switch (m_anchor)
    {
    case Qt::TopLeftCorner:
        rect.moveTopLeft(m_pos);
        break;

    case Qt::TopRightCorner:
        rect.moveTopRight(m_pos);
        break;

    case Qt::BottomLeftCorner:
        rect.moveBottomLeft(m_pos);
        break;

    case Qt::BottomRightCorner:
        rect.moveBottomRight(m_pos);
        break;

    }

    QRect screen = QApplication::desktop()->availableGeometry(m_pos);

    if (rect.right() > screen.right())
        rect.moveRight(screen.right());

    if (rect.bottom() > screen.bottom())
        rect.moveBottom(screen.bottom());

    move(rect.topLeft());
}
