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

#include <QtCore/QDebug>
#include <X11/Xatom.h>
#include <X11/extensions/Xrandr.h>

#include "unistd.h"

#include "xrandrbacklight.h"

static Display* dpy = NULL;
static Atom backlight, backlight_new, backlight_legacy;

long backlight_get (Display *dpy, RROutput output)
{
	unsigned long   nitems;
	unsigned long   bytes_after;
	unsigned char   *prop;
	Atom	    actual_type;
	int		    actual_format;
	long	    value;

	backlight = backlight_new;
	if (!backlight ||
			XRRGetOutputProperty (dpy, output, backlight,
				0, 4, False, False, None,
				&actual_type, &actual_format,
				&nitems, &bytes_after, &prop) != Success) {
		backlight = backlight_legacy;
		if (!backlight ||
				XRRGetOutputProperty (dpy, output, backlight,
					0, 4, False, False, None,
					&actual_type, &actual_format,
					&nitems, &bytes_after, &prop) != Success)
			return -1;
	}

	if (actual_type != XA_INTEGER || nitems != 1 || actual_format != 32)
		value = -1;
	else
		value = *((long *) prop);
	XFree (prop);
	return value;
}

XRRPropertyInfo* backlight_get_info(Display *dpy, RROutput output)
{
	XRRPropertyInfo *propinfo = NULL;

	backlight = backlight_new;
	if ( backlight )
		  propinfo = XRRQueryOutputProperty(dpy, output,
									      backlight);
	if ( !propinfo )
	{
		backlight = backlight_legacy;
		if (!backlight )
				propinfo = XRRQueryOutputProperty(dpy, output,
													backlight);
	}

	return propinfo;
}

bool backlight_set_backlight(Display *dpy, RROutput output, int brightness)
{
	unsigned long   nitems;
	unsigned long   bytes_after;
	unsigned char   *prop;
	Atom	    actual_type;
	int		    actual_format;
	long	    value = (long) brightness;

	backlight = backlight_new;
	if (!backlight ||
			XRRGetOutputProperty (dpy, output, backlight,
				0, 4, False, False, None,
				&actual_type, &actual_format,
				&nitems, &bytes_after, &prop) != Success) {
		backlight = backlight_legacy;
		if (!backlight ||
				XRRGetOutputProperty (dpy, output, backlight,
					0, 4, False, False, None,
					&actual_type, &actual_format,
					&nitems, &bytes_after, &prop) != Success)
			return false;
	}
	if (actual_type == XA_INTEGER || nitems == 1 || actual_format == 32)
	{
		qDebug() << "Setting brightness";
		XRRChangeOutputProperty (dpy, output,
							 backlight, actual_type, actual_format, PropModeReplace,
												 (unsigned char*) &value, 1);
		qDebug() << "Brightness set";
		return true;
	}
	return false;
}

XrandrBacklight::XrandrBacklight(QString name, QObject *parent)
	: Backlight(name, parent)
	, m_dpy_name(NULL)
{
	if ( !name.isEmpty() )
		m_dpy_name = name.toLocal8Bit().data();
	qDebug() << "Setting up dpy";
	dpy = XOpenDisplay (m_dpy_name);
}

XrandrBacklight::~XrandrBacklight()
{
}

int XrandrBacklight::getMaxBrightness()
{
	qDebug() << "max1";
	if (!dpy)
		dpy = XOpenDisplay (m_dpy_name);
	if (dpy)
	{
		qDebug() << "max2";
		backlight_new    = XInternAtom (dpy, "Backlight", True);
		backlight_legacy = XInternAtom (dpy, "BACKLIGHT", True);
		if (backlight_new == None && backlight_legacy == None)
		{
			qDebug() << "No outputs have backlight property";
			return -1;
		}
		int screen;
		for (screen = 0; screen < ScreenCount (dpy); screen++)
		{
			Window		    root = RootWindow (dpy, screen);
			XRRScreenResources  *resources = XRRGetScreenResourcesCurrent (dpy, root);
			int           o;

			if (!resources)
				return -1;
			for (o = 0; o < resources->noutput; o++)
			{
				RROutput	output = resources->outputs[o];
				XRRPropertyInfo *propinfo = backlight_get_info(dpy, output);
				qDebug() << "propinfo:" << propinfo->range << "," << propinfo->num_values;
				if ( propinfo && propinfo->range && propinfo->num_values > 0 )
				{
					for ( int i = 0; i < propinfo->num_values; i++ )
						qDebug() << i << ":" << propinfo->values[i];
					return (int)propinfo->values[1];
				}
			}
		}
	}
	return -1;
}

int XrandrBacklight::getCurBrightness()
{
	qDebug() << "cur1";
	if (!dpy)
		dpy = XOpenDisplay (m_dpy_name);
	if (dpy)
	{
		qDebug() << "cur2";
		backlight_new    = XInternAtom (dpy, "Backlight", True);
		backlight_legacy = XInternAtom (dpy, "BACKLIGHT", True);
		if (backlight_new == None && backlight_legacy == None)
		{
			qDebug() << "No outputs have backlight property";
			return -1;
		}
		int screen;
		for (screen = 0; screen < ScreenCount (dpy); screen++)
		{
			Window		    root = RootWindow (dpy, screen);
			XRRScreenResources  *resources = XRRGetScreenResourcesCurrent (dpy, root);
			int           o;

			if (!resources)
				return -1;
			for (o = 0; o < resources->noutput; o++)
			{
				RROutput	output = resources->outputs[o];
				long cur;
				cur = backlight_get (dpy, output);
				if ( cur != -1 )
				{
					qDebug() << "backlight:" << cur;
					return (int)cur;
				}
			}
		}
	}
	return -1;
}

void XrandrBacklight::setCurBrightness(int brightness)
{
	qDebug() << "set1";
	if (!dpy)
		dpy = XOpenDisplay (m_dpy_name);
	if (dpy)
	{
		qDebug() << "set2";
		backlight_new    = XInternAtom (dpy, "Backlight", True);
		backlight_legacy = XInternAtom (dpy, "BACKLIGHT", True);
		if (backlight_new == None && backlight_legacy == None)
		{
			qDebug() << "No outputs have backlight property";
			return;
		}
		int screen;
		for (screen = 0; screen < ScreenCount (dpy); screen++)
		{
			Window		    root = RootWindow (dpy, screen);
			XRRScreenResources  *resources = XRRGetScreenResourcesCurrent (dpy, root);
			int           o;

			if (!resources)
				return;
			for (o = 0; o < resources->noutput; o++)
			{
				qDebug() << "set3";
				RROutput	output = resources->outputs[o];
				if (backlight_set_backlight (dpy, output, brightness))
					break;
				qDebug() << "set4";
			}
		}
	}
}
