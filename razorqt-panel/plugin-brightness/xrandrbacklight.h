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

#ifndef XRANDRBACKLIGHT_H
#define XRANDRBACKLIGHT_H

#include <QtCore/QObject>

#include "backlight.h"

class XrandrBacklight : public Backlight
{
	Q_OBJECT

public:
		XrandrBacklight(QString name = "", QObject *parent = 0);
		~XrandrBacklight();

		QString getName() { return "xrandr"; }
		int getMaxBrightness();
		int getCurBrightness();
		void setCurBrightness(int brightness);

protected:
		char    *m_dpy_name = NULL;
};

#endif // BACKLIGHT_H
