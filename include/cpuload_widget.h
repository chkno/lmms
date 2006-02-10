/*
 * cpuload_widget.h - widget for displaying CPU-load (partly based on
 *                    Hydrogen's CPU-load-widget)
 *
 * Copyright (c) 2005-2006 Tobias Doerffel <tobydox/at/users.sourceforge.net>
 * 
 * This file is part of Linux MultiMedia Studio - http://lmms.sourceforge.net
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public
 * License along with this program (see COPYING); if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 *
 */


#ifndef _CPULOAD_WIDGET_H
#define _CPULOAD_WIDGET_H

#include "qt3support.h"

#ifdef QT4

#include <QWidget>
#include <QPixmap>
#include <QTimer>

#else

#include <qwidget.h>
#include <qpixmap.h>
#include <qtimer.h>

#endif

#include "types.h"
#include "engine.h"


class cpuloadWidget : public QWidget, public engineObject
{
	Q_OBJECT
public:
	cpuloadWidget( QWidget * _parent, engine * _engine );
	virtual ~cpuloadWidget();


protected:
	virtual void paintEvent( QPaintEvent * _ev );


protected slots:
	void updateCpuLoad();


private:
	Uint8 m_currentLoad;

	QPixmap m_temp;
	QPixmap m_background;
	QPixmap m_leds;

	bool m_changed;

	QTimer m_updateTimer;

} ;


#endif
