/*
    <one line to give the program's name and a brief idea of what it does.>
    Copyright (C) 2012  Paul Campbell <paul@taniwha.com>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*/

#ifndef TTYLOCK_H
#define TTYLOCK_H
#include <QString>

class ttylock
{

public:
    ttylock(QString tty);
    virtual ~ttylock();
    bool lock();
    void unlock();
    
private:
    bool locked;
    QString tty;
    QString pid_name;
    QString dev_name;
    bool get_names(QString);
    bool write_lock(QString, int);
    bool check_lock(QString, int);
};

#ifndef _PATH_LOCK
#  define LOCK_PATH	"/var/lock/"
#else
#  define LOCK_PATH	_PATH_LOCK
#endif
#ifndef _PATH_DEV
#  define DEV_PATH	"/dev/"
#else
#  define DEV_PATH	_PATH_DEV
#endif

#endif // TTYLOCK_H
