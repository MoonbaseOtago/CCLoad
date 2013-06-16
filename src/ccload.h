/***************************************************************************
 *   Copyright (C) %{CURRENT_YEAR} by %{AUTHOR} <%{EMAIL}>                            *
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

#ifndef CCLOAD_H
#define CCLOAD_H


//#include <KXmlGuiWindow>
#include <QMainWindow>

#include "ui_prefs_base.h"

class ccloadView;
class QPrinter;
class KToggleAction;
class KUrl;

/**
 * This class serves as the main window for ccload.  It handles the
 * menus, toolbars and status bars.
 *
 * @short Main window class
 * @author %{AUTHOR} <%{EMAIL}>
 * @version %{VERSION}
 */
//class ccload : public KXmlGuiWindow
class ccload : public QMainWindow
{
    Q_OBJECT
public:
    /**
     * Default Constructor
     */
    ccload();

    /**
     * Default Destructor
     */
    virtual ~ccload();

private slots:

private:
    void setupActions();

private:
    Ui::prefs_base ui_prefs_base ;
    ccloadView *m_view;

    QPrinter   *m_printer;
    KToggleAction *m_toolbarAction;
    KToggleAction *m_statusbarAction;
};

#endif // _CCLOAD_H_
