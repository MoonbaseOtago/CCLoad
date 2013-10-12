#ifndef _ExtraQPlainTextEdit_
#define _ExtraQPlainTextEdit_
#include <QPlainTextEdit>

class ExtraQPlainTextEdit:public QPlainTextEdit {
    Q_OBJECT
public:
	ExtraQPlainTextEdit(QWidget *p):QPlainTextEdit(p) {}
protected:
	void contextMenuEvent(QContextMenuEvent *event);
private slots:
	void menu_clear();
};
#endif
