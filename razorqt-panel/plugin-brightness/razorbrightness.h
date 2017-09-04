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

#ifndef RAZORBRIGHTNESS_H
#define RAZORBRIGHTNESS_H

#include "../panel/irazorpanelplugin.h"
//#include <QtGui/QToolButton>

#include <QtGui/QSlider>

class BrightnessButton;
class RazorNotification;
namespace GlobalKeyShortcut
{
class Action;
}

class RazorBrightness : public QObject, public IRazorPanelPlugin
{
	Q_OBJECT
	public:
		RazorBrightness(const IRazorPanelPluginStartupInfo &startupInfo);
		~RazorBrightness();

		virtual QWidget *widget();
		virtual QString themeId() const { return "Brightness"; }
		virtual IRazorPanelPlugin::Flags flags() const { return PreferRightAlignment | HaveConfigDialog ; }
		void realign();
		//QDialog *configureDialog();

	protected slots:
		virtual void settingsChanged();
		void handleDeviceBrightnessChanged();
		void showMessage();

	private:
		BrightnessButton *m_brightnessButton;
		RazorNotification *m_notification;
    GlobalKeyShortcut::Action *m_keyBrightnessUp;
    GlobalKeyShortcut::Action *m_keyBrightnessDown;
};


class RazorBrightnessPluginLibrary: public QObject, public IRazorPanelPluginLibrary
{
	Q_OBJECT
		Q_INTERFACES(IRazorPanelPluginLibrary)
	public:
		IRazorPanelPlugin *instance(const IRazorPanelPluginStartupInfo &startupInfo)
		{
			return new RazorBrightness(startupInfo);
		}
};

#endif // RAZORVOLUME_H
