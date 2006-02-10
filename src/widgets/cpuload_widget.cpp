/*
 * cpuload_widget.cpp - widget for displaying CPU-load (partly based on
 *                      Hydrogen's CPU-load-widget)
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


#include "qt3support.h"

#ifdef QT4

#include <QPainter>

#else

#include <qpainter.h>

#endif


#include "cpuload_widget.h"
#include "embed.h"
#include "mixer.h"


cpuloadWidget::cpuloadWidget( QWidget * _parent, engine * _engine ) :
	QWidget( _parent ),
	engineObject( _engine ),
	m_currentLoad( 0 ),
	m_temp(),
	m_background( embed::getIconPixmap( "cpuload_bg" ) ),
	m_leds( embed::getIconPixmap( "cpuload_leds" ) ),
	m_changed( TRUE ),
	m_updateTimer()
{
	setFixedSize( m_background.width(), m_background.height() );

	m_temp = QPixmap( width(), height() );

	connect( &m_updateTimer, SIGNAL( timeout() ),
					this, SLOT( updateCpuLoad() ) );
	m_updateTimer.start( 100 );	// update cpu-load at 10 fps

#ifndef QT4
	setBackgroundMode( NoBackground );
#endif
}




cpuloadWidget::~cpuloadWidget()
{
}




void cpuloadWidget::paintEvent( QPaintEvent *  )
{
	if( m_changed == TRUE )
	{
		m_changed = FALSE;

		QPainter p( &m_temp );
		p.drawPixmap( 0, 0, m_background );

		// as load-indicator consists of small 2-pixel wide leds with
		// 1 pixel spacing, we have to make sure, only whole leds are
		// shown which we achieve by the following formula
		int w = ( m_leds.width() * m_currentLoad / 300 ) * 3;
		if( w > 0 )
		{
			p.drawPixmap( 23, 3, m_leds, 0, 0, w,
							m_leds.height() );
		}
	}
	QPainter p( this );
	p.drawPixmap( 0, 0, m_temp );
}




void cpuloadWidget::updateCpuLoad()
{
	// smooth load-values a bit
	Uint8 new_load = ( m_currentLoad + eng()->getMixer()->cpuLoad() ) / 2;
	if( new_load != m_currentLoad )
	{
		m_currentLoad = new_load;
		m_changed = TRUE;
		update();
	}
}



#include "cpuload_widget.moc"

