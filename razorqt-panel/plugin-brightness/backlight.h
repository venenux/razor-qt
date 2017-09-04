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

#ifndef BACKLIGHT_H
#define BACKLIGHT_H

#include <QtCore/QObject>

class Backlight : public QObject
{
		Q_OBJECT
		Q_PROPERTY(int brightness READ getCurBrightness WRITE setCurBrightness)

public:
		Backlight(QString name, QObject *parent = 0);
		~Backlight();

		virtual QString getName() = 0;
		virtual int getMaxBrightness() = 0;
		virtual int getCurBrightness() = 0;
		virtual void setCurBrightness(int brightness) = 0;
};

#endif // BACKLIGHT_H
