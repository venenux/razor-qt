/* BEGIN_COMMON_COPYRIGHT_HEADER
 * (c)LGPL2+
 *
 * Razor - a lightweight, Qt based, desktop toolset
 * http://razor-qt.org
 *
 * Copyright: 2012 Razor team
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

#include "razorbrightness.h"

//#include "brightnessbutton.h"
//#include "brightnesspopup.h"
//#include "razorbrightnessconfiguration.h"

#include <QtGui/QMessageBox>
#include <QtDebug>
#include <qtxdg/xdgicon.h>
#include <razorqt/razornotification.h>

Q_EXPORT_PLUGIN2(brightness, RazorBrightnessPluginLibrary)

RazorBrightness::RazorBrightness(const IRazorPanelPluginStartupInfo &startupInfo):
        QObject(),
        IRazorPanelPlugin(startupInfo)
{
    //m_brightnessButton = new BrightnessButton(this);

    m_notification = new RazorNotification("", this);

		setObjectName("Brightness");
		mButton.setIcon(XdgIcon::fromTheme(QStringList() << "display-brightness"));
		//addWidget(&mButton);
		connect(&mButton, SIGNAL(clicked()), this, SLOT(showMessage()));

    settingsChanged();
}

RazorBrightness::~RazorBrightness()
{
    //delete m_brightnessButton;
}

void RazorBrightness::showMessage()
{
	QMessageBox::information(0, tr("Panel"), tr("Brightness!"));
}

void RazorBrightness::settingsChanged()
{
    /*m_volumeButton->setShowOnClicked(settings()->value(SETTINGS_SHOW_ON_LEFTCLICK, SETTINGS_DEFAULT_SHOW_ON_LEFTCLICK).toBool());
    m_volumeButton->setMuteOnMiddleClick(settings()->value(SETTINGS_MUTE_ON_MIDDLECLICK, SETTINGS_DEFAULT_MUTE_ON_MIDDLECLICK).toBool());
    m_volumeButton->setMixerCommand(settings()->value(SETTINGS_MIXER_COMMAND, SETTINGS_DEFAULT_MIXER_COMMAND).toString());
    m_volumeButton->volumePopup()->setSliderStep(settings()->value(SETTINGS_STEP, SETTINGS_DEFAULT_STEP).toInt());*/
}

QWidget *RazorBrightness::widget()
{
    //return m_volumeButton;
		return &mButton;
}

/*void RazorVolume::realign()
{
    m_volumeButton->hideVolumeSlider();
}

QDialog *RazorVolume::configureDialog()
{
    RazorVolumeConfiguration *configWindow = new RazorVolumeConfiguration(*settings());
    configWindow->setAttribute(Qt::WA_DeleteOnClose, true);

    if (m_engine)
       configWindow->setSinkList(m_engine->sinks());

    return configWindow;
}*/
