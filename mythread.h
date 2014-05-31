/*
    <one line to give the library's name and an idea of what it does.>
    Copyright (C) 2012  Paul Campbell <paul@taniwha.com>

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/


#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QThread>
#include <QMutex>
#include "ccloadview.h"

class ccloadView;

class MyThread : public QThread
{

protected:
    virtual void run();
    bool _bFinished;
    ccloadView *view;
    int saved, save_in, save_out;
    unsigned char save_buffer[256];
    QMutex mutex;
    char q[10000];
    char *qin;
    char *qout;
    int qsize;

public:
    MyThread(ccloadView *parent);
    int consoleRead(char *b, int count);
    virtual ~MyThread();
    int read(char *b, int l);
};

#endif // MYTHREAD_H
