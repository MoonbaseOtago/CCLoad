/***************************************************************************
 *   Copyright (C) 2012 by Paul Campbell <paul@taniwha.com> 		   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA .        *
 ***************************************************************************/

#include "ccload.h"
#include "ccloadview.h"
//#include "settings.h"

#include <QDropEvent>
#include <QPainter>
#include <QPrinter>
#include <QStatusBar>

//#include <KConfigDialog>
//#include <KStatusBar>

//#include <KAction>
//#include <KActionCollection>
//#include <KStandardAction>

//#include <KLocale>

ccload::ccload()
    : QMainWindow(),
      m_view(new ccloadView(this)),
      m_printer(0)
{
    // accept dnd
    //setAcceptDrops(true);
     {
     QSettings settings("MoonBase", "ccload");
     restoreGeometry(settings.value("main-geometry").toByteArray());
     restoreState(settings.value("main-windowState").toByteArray());
    }
    // tell the KXmlGuiWindow that this is indeed the main widget
    setCentralWidget(m_view);

    // then, setup our actions
    setupActions();

    // add a status bar
    statusBar()->show();

    // a call to KXmlGuiWindow::setupGUI() populates the GUI
    // with actions, using KXMLGUI.
    // It also applies the saved mainwindow settings, if any, and ask the
    // mainwindow to automatically save settings if changed: window size,
    // toolbar position, icon size, etc.
    //setupGUI();
}

void ccload::closeEvent(QCloseEvent *event)
{
     QSettings settings("MoonBase", "ccload");
     settings.setValue("main-geometry", saveGeometry());
     settings.setValue("main-windowState", saveState());
     QMainWindow::closeEvent(event);
}

ccload::~ccload()
{
}

void ccload::setupActions()
{
    //KStandardAction::openNew(this, SLOT(fileNew()), actionCollection());

    //KStandardAction::preferences(this, SLOT(optionsPreferences()), actionCollection());

    // custom menu and menu item - the slot is in the class ccloadView
    //KAction *custom = new KAction(KIcon("colorize"), i18n("Swi&tch Colors"), this);
    //actionCollection()->addAction( QLatin1String("switch_action"), custom );
    //connect(custom, SIGNAL(triggered(bool)), m_view, SLOT(switchColors()));
}


//#include "ccload.moc"
