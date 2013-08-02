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

#include "backlightfactory.h"
#include "xrandrbacklight.h"

#define _GNU_SOURCES
#include <dlfcn.h>

#include <QtCore/QDir>
#include <QtDebug>

BacklightFactory::BacklightFactory(QObject *parent)
	: QObject(parent)
{
	dlerror();
	dlsym(RTLD_DEFAULT, "XRRGetOutputProperty");
	char* error = dlerror();
	if (error)
		qDebug() << "Error:" << error;
	else
		m_devices.push_back(new XrandrBacklight());
}

BacklightFactory::~BacklightFactory()
{
}
