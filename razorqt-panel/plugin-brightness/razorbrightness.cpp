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

#include "brightnessbutton.h"
#include "backlightfactory.h"
#include "brightnesspopup.h"
//#include "razorbrightnessconfiguration.h"

#include <QtDebug>
#include <qtxdg/xdgicon.h>
#include <razor-global-key-shortcuts-client/razor-global-key-shortcuts-client.h>
#include <razorqt/razornotification.h>

#define DEFAULT_UP_SHORTCUT "XF86MonBrightnessUp"
#define DEFAULT_DOWN_SHORTCUT "XF86MonBrightnessDown"

Q_EXPORT_PLUGIN2(brightness, RazorBrightnessPluginLibrary)

RazorBrightness::RazorBrightness(const IRazorPanelPluginStartupInfo &startupInfo):
        QObject(),
        IRazorPanelPlugin(startupInfo)
{
    m_brightnessButton = new BrightnessButton(this);

    m_notification = new RazorNotification("", this);

    // global key shortcuts
    QString shortcutNotRegistered = "";

		setObjectName("Brightness");

		qDebug() << "Looking for backlight devices.";
		BacklightFactory factory;
		if ( factory.devices().size() > 0 )
		{
			m_brightnessButton->brightnessPopup()->setBacklight(factory.devices().first());
		}
		//addWidget(&mButton);
    m_keyBrightnessUp = GlobalKeyShortcut::Client::instance()->addAction(QString(), QString("/panel/%1/up").arg(settings()->group()), tr("Increase display brightness"), this);
    if (m_keyBrightnessUp)
    {
        connect(m_keyBrightnessUp, SIGNAL(activated()), m_brightnessButton->brightnessPopup(), SLOT(handleDeviceBrightnessChanged()));

        if (m_keyBrightnessUp->shortcut().isEmpty())
        {
            m_keyBrightnessUp->changeShortcut(DEFAULT_UP_SHORTCUT);
            if (m_keyBrightnessUp->shortcut().isEmpty())
            {
                shortcutNotRegistered = " '" DEFAULT_UP_SHORTCUT "'";
            }
        }
    }

    m_keyBrightnessDown = GlobalKeyShortcut::Client::instance()->addAction(QString(), QString("/panel/%1/down").arg(settings()->group()), tr("Decrease display brightness"), this);
    if (m_keyBrightnessDown)
    {
        connect(m_keyBrightnessDown, SIGNAL(activated()), m_brightnessButton->brightnessPopup(), SLOT(handleDeviceBrightnessChanged()));

        if (m_keyBrightnessDown->shortcut().isEmpty())
        {
            m_keyBrightnessDown->changeShortcut(DEFAULT_DOWN_SHORTCUT);
            if (m_keyBrightnessDown->shortcut().isEmpty())
            {
                shortcutNotRegistered += " '" DEFAULT_DOWN_SHORTCUT "'";
            }
        }
    }

    if(!shortcutNotRegistered.isEmpty())
    {
        m_notification->setSummary(tr("Brightness Control: The following shortcuts can not be registered: %1").arg(shortcutNotRegistered));
        m_notification->update();
    }
    
    m_notification->setTimeout(1000);
    m_notification->setUrgencyHint(RazorNotification::UrgencyLow);

    settingsChanged();
}

RazorBrightness::~RazorBrightness()
{
    delete m_brightnessButton;
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
    return m_brightnessButton;
}

void RazorBrightness::realign()
{
    m_brightnessButton->hideBrightnessSlider();
}

/*QDialog *RazorVolume::configureDialog()
{
    RazorVolumeConfiguration *configWindow = new RazorVolumeConfiguration(*settings());
    configWindow->setAttribute(Qt::WA_DeleteOnClose, true);

    if (m_engine)
       configWindow->setSinkList(m_engine->sinks());

    return configWindow;
}*/
