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


#include "mythread.h"
#include "qtextcursor.h"
#include <iostream>
#include <stdio.h>
#include <unistd.h>

void MyThread::run()
{
    unsigned char buff[256];
    bool escape = 0;
    int l, i;
    
    while ( ! _bFinished ) {
	if (view->port >= 0) {
	    l = ::read(view->port, &buff[0], sizeof(buff));
	    if (l > 0) {
		mutex.lock();
		for (i = 0; i < l; i++) {
		    //printf(" 0x%02x", buff[i]);fflush(stdout);
		    if (escape) {
			if (buff[i] == 0xfd) {
			    escape = 0;
			    continue;
			}
			printf("%c", buff[i]);fflush(stdout);
#ifdef NOTDEF
			int p = view->form.console->textCursor().position();
			view->form.console->moveCursor(QTextCursor::End, QTextCursor::MoveAnchor);
			view->form.console->insertPlainText(QChar(buff[i]));
			view->form.console->textCursor().setPosition(p);
#endif
		    } else {
			if (buff[i] == 0xfc) {
			    escape = 1;
			    continue;
			}
			if (saved < sizeof(save_buffer)) {
			    save_buffer[save_in++] = buff[i];
			    saved++;
			    if (save_in == sizeof(save_buffer)) 
				save_in = 0;
			}
		    }
		}
		mutex.unlock();
		continue;
	    }
	}
	
        QThread::msleep( 100 );
    }
}

void
MyThread::consoleWrite(QString s)
{
    mutex.lock();
    int p = view->form.console->textCursor().position();
    view->form.console->moveCursor(QTextCursor::End, QTextCursor::MoveAnchor);
    view->form.console->insertPlainText(s);
    view->form.console->textCursor().setPosition(p);
    mutex.unlock();
}

int MyThread::read(char *b, int l)
{
    int r=0;
    mutex.lock();
    while (r < l && saved) {
	    *b++ =  save_buffer[save_out++];
	    if (save_out == sizeof(save_buffer)) 
		save_out = 0;
	    saved--;
	    r++;
    }
    mutex.unlock();
    return r;
}

MyThread::MyThread(ccloadView *parent): QThread(parent),_bFinished(0), view(parent), save_in(0), saved(0), save_out(0)
{
     
}

MyThread::~MyThread()
{
      _bFinished = true;
      wait();
}

