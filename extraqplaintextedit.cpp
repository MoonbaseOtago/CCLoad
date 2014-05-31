#include <QMenu> 
#include "extraqplaintextedit.h"

void
ExtraQPlainTextEdit::contextMenuEvent(QContextMenuEvent *event)
{
	QMenu *menu = createStandardContextMenu();
      	menu->addAction(tr("Clear Console"), this, SLOT(menu_clear()));
     	menu->exec(event->globalPos());
     	delete menu;
}

void 
ExtraQPlainTextEdit::menu_clear()
{
	selectAll();
	clear();
}
