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

#include "brightnessbutton.h"

#include "brightnesspopup.h"

#include <QtGui/QSlider>
#include <QtGui/QMouseEvent>
#include <QtCore/QProcess>

#include <qtxdg/xdgicon.h>
#include "../panel/irazorpanel.h"
#include "../panel/irazorpanelplugin.h"

BrightnessButton::BrightnessButton(IRazorPanelPlugin *plugin, QWidget* parent):
        QToolButton(parent),
        mPlugin(plugin),
        m_panel(plugin->panel()),
        m_showOnClick(true)
{
    // initial icon for button. It will be replaced after devices scan.
    // In the worst case - no soundcard/pulse - is found it remains
    // in the button but at least the button is not blank ("invisible")
    //handleStockIconChanged("dialog-error"); //TODO: check for brightness devices
		handleStockIconChanged("display-brightness");
		setToolTip(tr("Brightness"));
    m_brightnessPopup = new BrightnessPopup();

    m_popupHideTimer.setInterval(1000);
    connect(this, SIGNAL(clicked()), this, SLOT(toggleBrightnessSlider()));
    connect(&m_popupHideTimer, SIGNAL(timeout()), this, SLOT(hideBrightnessSlider()));

    connect(m_brightnessPopup, SIGNAL(mouseEntered()), &m_popupHideTimer, SLOT(stop()));
    connect(m_brightnessPopup, SIGNAL(mouseLeft()), &m_popupHideTimer, SLOT(start()));

    //connect(m_brightnessPopup, SIGNAL(stockIconChanged(QString)), this, SLOT(handleStockIconChanged(QString)));
}

BrightnessButton::~BrightnessButton()
{
    if (m_brightnessPopup)
        delete m_brightnessPopup;
}

void BrightnessButton::setShowOnClicked(bool state)
{
    if (m_showOnClick == state)
        return;

    m_showOnClick = state;
}

void BrightnessButton::enterEvent(QEvent *event)
{
    if (!m_showOnClick)
        showBrightnessSlider();

    m_popupHideTimer.stop();
}

void BrightnessButton::leaveEvent(QEvent *event)
{
    m_popupHideTimer.stop();
}

void BrightnessButton::wheelEvent(QWheelEvent *event)
{
    m_brightnessPopup->handleWheelEvent(event);
}

void BrightnessButton::toggleBrightnessSlider()
{
    if (m_brightnessPopup->isVisible()) {
        hideBrightnessSlider();
    } else {
        showBrightnessSlider();
    }
}

void BrightnessButton::showBrightnessSlider()
{

    if (m_brightnessPopup->isVisible())
        return;

    m_popupHideTimer.stop();
    m_brightnessPopup->updateGeometry();
    m_brightnessPopup->adjustSize();
    QRect pos = mPlugin->calculatePopupWindowPos(m_brightnessPopup->size());
    m_brightnessPopup->open(pos.topLeft(), Qt::TopLeftCorner);
}

void BrightnessButton::hideBrightnessSlider()
{
    m_popupHideTimer.stop();
    m_brightnessPopup->hide();
}

void BrightnessButton::handleStockIconChanged(const QString &iconName)
{
    setIcon(XdgIcon::fromTheme(iconName, iconName+"-symbolic"));
}
