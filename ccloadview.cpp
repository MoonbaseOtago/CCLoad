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

#include "ccloadview.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>

#include <QLabel>
#include <QLineEdit>
#include <QFileDialog>
#include <QThread>
#include <QFileInfo>
#include <QTimer>
#include <iostream>

class Sleeper : public QThread
{
public:
    static void usleep(unsigned long usecs){QThread::usleep(usecs);}
    static void msleep(unsigned long msecs){QThread::msleep(msecs);}
    static void sleep(unsigned long secs){QThread::sleep(secs);}
};

// Chip Name, FlashSize, FlashPageSize, FlashWordSize
char *ccloadView::ChipDescriptors[] =  {
	"CC2511F32;8000;400;2",
	"CC2511F16;4000;400;2",
	"CC2511F08;2000;400;2",
	"CC2510F32;8000;400;2",
	"CC2510F16;4000;400;2",
	"CC2510F08;2000;400;2",
	"CC2431F128;20000;800;4",
	"CC2431F64;10000;800;4",
	"CC2431F32;8000;800;4",
	"CC2430F128;20000;800;4",
	"CC2430F64;10000;800;4",
	"CC2430F32;8000;800;4",
	"CC1110F32;8000;400;2",
	"CC1110F16;4000;400;2",
	"CC1110F08;2000;400;2",
	"CC2540F128;20000;800;2",
	"CC2540F256;40000;800;2",
	"CC2541F128;20000;800;2",
	"CC2541F256;40000;800;2",
	"CC2530F32;8000;800;4",
	"CC2530F64;10000;800;4",
	"CC2530F128;20000;800;4",
	"CC2530F256;40000;800;4",
	"CC2531F128;20000;800;4",
	"CC2531F256;40000;800;4",
	"CC2533F32;8000;400;4",
	"CC2533F64;10000;400;4",
	"CC2533F96;18000;400;4",
	0
};

ccloadView::ccloadView(QWidget *)
{
    waiting = false;
    chipDefined = false;
    inDebugMode = false;
    port = -1;
    prod = 1;

    form.setupUi(this);
    lock = NULL;
    maddr=0;
    app_msize = 0;
    startPC=0;
    startPCvalid=true;
    connected = 0;
    settings = new QSettings("MoonbaseOtago", "CCload");
    form.fileName->setText(settings->value("fileName", "").toString());
    form.fileName_App->setText(settings->value("fileName_App", "").toString());
    form.autoConnect->setChecked(settings->value("autoConnect", true).toBool());   
    form.erasePage->setChecked(settings->value("erasePage", true).toBool());   
    form.verifyAfterWrite->setChecked(settings->value("verifyAfterWrite", false).toBool());   
    form.erasePage_App->setChecked(settings->value("erasePage_App", true).toBool());   
    form.verifyAfterWrite_App->setChecked(settings->value("verifyAfterWrite_App", false).toBool());   
    form.writeMAC->setChecked(settings->value("writeMAC", false).toBool());   
    form.autoIncMAC->setChecked(settings->value("autoIncMAC", false).toBool());   
    form.hiMAC->setText(settings->value("hiMAC", "00000000").toString());
    form.lowMAC->setText(settings->value("lowMAC", "00000000").toString());
    form.hiMAC->setMaxLength(8);
    form.lowMAC->setMaxLength(8);
    form.lowMAC->setInputMask("HHHHHHHH");
    form.hiMAC->setInputMask("HHHHHHHH");
    form.allowUnknowns->setEnabled(true);
    form.allowUnknowns->setChecked(true);
    btnMACwrite_Click_set();
    connect(form.DD, SIGNAL(clicked()), this, SLOT(btnFlashDD_Click()));
    connect(form.DC, SIGNAL(clicked()), this, SLOT(btnFlashDC_Click()));
    connect(form.RST, SIGNAL(clicked()), this, SLOT(btnFlashRST_Click()));
    connect(form.Connect, SIGNAL(clicked()), this, SLOT(btnConnect_Click()));
    connect(this, SIGNAL(startupclick()), this, SLOT(btnConnect_Click()));
    connect(form.selectFile, SIGNAL(clicked()), this, SLOT(btnSelectFile_Click()));
    connect(form.selectFile_App, SIGNAL(clicked()), this, SLOT(btnSelectFile_App_Click()));
    connect(form.readFile, SIGNAL(clicked()), this, SLOT(btnRead_Click()));
    connect(form.readFile_App, SIGNAL(clicked()), this, SLOT(btnRead_App_Click()));
    connect(form.loadFile, SIGNAL(clicked()), this, SLOT(btnSelectLoad_Click()));
    connect(form.loadFile_App, SIGNAL(clicked()), this, SLOT(btnSelectLoad_App_Click()));
    connect(form.Debug, SIGNAL(clicked()), this, SLOT(btnDebug_Click()));
    connect(form.Production, SIGNAL(clicked()), this, SLOT(btnProduction_Click()));
    connect(form.writeFile, SIGNAL(clicked()), this, SLOT(btnWrite_Click()));
    connect(form.writeFile_App, SIGNAL(clicked()), this, SLOT(btnWrite_App_Click()));
    connect(form.writeAll, SIGNAL(clicked()), this, SLOT(btnWrite_All_Click()));
    connect(form.eraseChip, SIGNAL(clicked()), this, SLOT(btnErase_Click()));
    connect(form.lock, SIGNAL(clicked()), this, SLOT(btnLock_Click()));
    connect(form.getStatus, SIGNAL(clicked()), this, SLOT(btnGetStatus_Click()));
    connect(form.flashCC, SIGNAL(clicked()), this, SLOT(btnFlashCC_Click()));
    connect(form.step, SIGNAL(clicked()), this, SLOT(btnStep_Click()));
    connect(form.run, SIGNAL(clicked()), this, SLOT(btnRun_Click()));
    connect(form.setPC, SIGNAL(returnPressed()), this, SLOT(btnSetPC_Click()));
    connect(form.readLocation, SIGNAL(returnPressed()), this, SLOT(btnReadLocation_Click()));
    connect(form.halt, SIGNAL(clicked()), this, SLOT(btnHalt_Click()));
    connect(form.autoConnect, SIGNAL(clicked()), this, SLOT(btnAuto_Click()));
    connect(form.erasePage, SIGNAL(clicked()), this, SLOT(btnErasePage_Click()));
    connect(form.erasePage_App, SIGNAL(clicked()), this, SLOT(btnErasePage_App_Click()));
    connect(form.verifyAfterWrite, SIGNAL(clicked()), this, SLOT(btnVerify_Click()));
    connect(form.verifyAfterWrite_App, SIGNAL(clicked()), this, SLOT(btnVerify_App_Click()));
    connect(form.writeMAC, SIGNAL(stateChanged(int)), this, SLOT(btnMACwrite_Click()));
    connect(form.autoIncMAC, SIGNAL(stateChanged(int)), this, SLOT(btnMACautoInc_Click()));
    connect(form.lowMAC, SIGNAL(textChanged(QString)), this, SLOT(btnMAClow_Click()));
    connect(form.hiMAC, SIGNAL(textChanged(QString)), this, SLOT(btnMAChi_Click()));
    
    connect(form.chipModel, SIGNAL(currentIndexChanged(int)), this, SLOT(cbChipModel_SelectedIndexChanged(int)));
    thread = new MyThread(this);
    thread->start();
    if (form.autoConnect->isChecked())
	startupclick();
    form.selectFile->setEnabled(true);
    form.selectFile_App->setEnabled(true);
    if (!form.fileName->text().isEmpty())
	form.loadFile->setEnabled(true);
    if (!form.fileName_App->text().isEmpty())
	form.loadFile_App->setEnabled(true);
    form.verifyFile->setEnabled(false);
    form.writeAll->setEnabled(false);
    form.console->setReadOnly(true);

}

void
ccloadView::idle()
{
	char buff[21];

	int i = thread->consoleRead(&buff[0], sizeof(buff)-1);
	if (i > 0) {
		buff[i] = 0;
		QString s(&buff[0]);
		consoleDisplay(s);
	}
}

void
ccloadView::consoleDisplay(QString &s)
{
     	//int p = form.console->textCursor().position();
     	form.console->moveCursor(QTextCursor::End, QTextCursor::MoveAnchor);
     	form.console->insertPlainText(s);
     	//form.console->textCursor().setPosition(p);
 	QTextCursor c = form.console->textCursor();
 	c.movePosition(QTextCursor::End);
 	form.console->setTextCursor(c);
}

void
ccloadView::setIdleTimer()
{
	QTimer::singleShot(0, this, SLOT(idle()));
}

void
ccloadView::btnErasePage_Click()
{
	settings->setValue("erasePage", form.erasePage->isChecked());
	settings->sync();
}
void
ccloadView::btnVerify_Click()
{
	settings->setValue("verifyAfterWrite", form.verifyAfterWrite->isChecked());
	settings->sync();
}
void
ccloadView::btnErasePage_App_Click()
{
	settings->setValue("erasePage_App", form.erasePage_App->isChecked());
	settings->sync();
}
void
ccloadView::btnVerify_App_Click()
{
	settings->setValue("verifyAfterWrite_App", form.verifyAfterWrite_App->isChecked());
	settings->sync();
}
void
ccloadView::btnAuto_Click()
{
	settings->setValue("autoConnect", form.autoConnect->isChecked());
	settings->sync();
}

ccloadView::~ccloadView()
{

}

QString
ccloadView::prepareCommand(QString cmd)
{
	if (!cmd.isEmpty()) {
		unsigned char sum = 0;
		int i;
		
		for (i = 0;i < cmd.length(); i++)
			sum += (unsigned char) cmd[i].unicode();
		sum = 0-~sum;
		i = (sum>>4)&0xf;
		if (i > 9) {
			cmd += (char)('A'+(i-10));
		} else {
			cmd += (char)('0'+i);
		}
		i = (sum)&0xf;
		if (i > 9) {
			cmd += (char)('A'+(i-10));
		} else {
			cmd += (char)('0'+i);
		}
	}
	return (cmd + "\r");
}

QString
ccloadView::sendCommand(QString command, QString msg)
{
	if (port < 0)
		return "";

	QString response("");
	const int retryMax = 500;
	int retry = retryMax;
	char b[100];


	for (;;) {
		if (!thread)
			break;
		if (thread->read(b, sizeof(b)) <= 0)
			break;
	}

	command = prepareCommand(command);
	std::cout << "sending: '"<<command.toStdString()<<"'\n";
	int retryCmd = 10;
	int idx = 0;
	while (--retry > 0) {
		if (idx < command.length()) {
			char c = command.at(idx++).unicode();
			::write(port, &c, 1);
		}
		if (thread->read(b, 1) <= 0) {
			Sleeper::msleep(1);
			if (command == "\r") {
				if (retryCmd-- == 0) {
					retryCmd = 10;
					idx = 0;
				}
			}
		} else {
			++retry;
			response += (char)b[0];
			if (response.length() >= 3 && response.endsWith("\r\n:")) { 
				std::cout << "response: '"<<response.toStdString()<<"'\n";
				return response;
			}
		}
	}
	return "";
}

bool
ccloadView::parseOK(QString response)
{
	return response.endsWith("\r\nOK\r\n:");
}

QString
ccloadView::getTokenREAD(QString response)
{
	return getToken("READ:", response);
}

QString
ccloadView::getToken(QString token, QString response)
{
	int i;
	for (i=0; i < (response.length()-token.length());) {
		if (response.mid(i, token.length()) == token) {
			i += token.length();
			for (int l = 0; ;l++) {
				if ((i+l) >= response.length() || response[i+l] == '\r')
					return response.mid(i, l);
			}
		}
		for (;;i++) {
			if (i >= response.length())
				break;
			if (response[i++] == '\r')
				break;
		}
		for (;;i++) {
			if (i >= response.length())
				break;
			if (response[i++] == '\n')
				break;
		}
	}
	return "";
}

bool
ccloadView::getDataByte(int index, QString data)
{
	unsigned char value;
	return getDataByte(index, data, value);
}

bool
ccloadView::getDataByte(int index, QString data, unsigned char &value)
{
	value = 0;
	if (data.isEmpty())
		return false;
	if ((index * 2 + 2) >= data.length())
		return false;
	QChar c1 = data[index * 2];
	QChar c2 = data[index * 2+1];
	if (c1 >= '0' && c1 <= '9') {
		value = (c1.toLatin1()-'0')<<4;
	} else 
	if (c1 >= 'a' && c1 <= 'f') {
		value = (c1.toLatin1()-'a'+10)<<4;
	} else 
	if (c1 >= 'A' && c1 <= 'F') {
		value = (c1.toLatin1()-'A'+10)<<4;
	} else 
		return false;
	if (c2 >= '0' && c2 <= '9') {
		value |= (c2.toLatin1()-'0');
	} else 
	if (c2 >= 'a' && c2 <= 'f') {
		value |= (c2.toLatin1()-'a'+10);
	} else 
	if (c2 >= 'A' && c2 <= 'F') {
		value |= (c2.toLatin1()-'A'+10);
	} else 
		return false;
	return true;
}

bool
ccloadView::isPageEmpty(unsigned char *buffer)
{
	for (int i = 0; i < FLASH_PAGE_SIZE; i++)
	if (buffer[i] != 0xFF)
		return false;
	return true;
}

void
ccloadView::loadChipModel(QString items)
{
		QStringList list =  items.split(";");
		form.chipModel->clear();
		foreach (const QString &item, list) 
			form.chipModel->addItem(item);
		
		if (form.chipModel->currentIndex() < 0 && form.chipModel->count() > 0) {
		    form.chipModel->setCurrentIndex(0);
		    cbChipModel_SelectedIndexChanged(0);
		}
}

void
ccloadView::addRoutine(unsigned char *routine, int &rlen, unsigned char in0)
{	
	routine += rlen;
	*routine=in0;
	rlen++;
}

void
ccloadView::addRoutine(unsigned char *routine, int &rlen, unsigned char in0, unsigned char in1)
{	
	routine += rlen;
	*routine++=in0;
	*routine=in1;
	rlen+=2;
}

void
ccloadView::addRoutine(unsigned char *routine, int &rlen, unsigned char in0, unsigned char in1, unsigned char in2)
{	
        routine += rlen;
	*routine++=in0;
	*routine++=in1;
	*routine=in2;
	rlen+=3;
}

bool 
ccloadView::parseHexByte(QString name, QLineEdit *textBox, unsigned char &value, unsigned char def, bool canEmpty, bool valid)
{
	value = def;
	QString str = textBox->text();
	if (str.isEmpty() && !canEmpty) {
	    if (valid)
		form.statusLine->setText(QString("Field %1 can't be empty").arg(name));
	} else {
		bool ok;
		value = str.toInt(&ok, 0);
		if (ok)
			return true;
		if (valid)
		    form.statusLine->setText(QString("Field %1 should be a hex value").arg(name));
	}
	return false;
}

void
ccloadView::setStatusLED(int state, QCheckBox *led)
{
	led->setChecked(state!=0);
}

void
ccloadView::setStatusLabels(int status)
{
	setStatusLED(status & 0x80, form.chipEraseDone);
	setStatusLED(status & 0x40, form.pconIdle);
	setStatusLED(status & 0x20, form.cpuHalted);
	setStatusLED(status & 0x10, form.powerMode0);
	setStatusLED(status & 0x08, form.haltStatus);
	setStatusLED(status & 0x04, form.debugLocked);
	setStatusLED(status & 0x02, form.oscillatorStable);
	setStatusLED(status & 0x01, form.stackOverflow);
}

void
ccloadView::setConfigLabels(int config)
{
	setStatusLED(config & 0x08, form.timersOff);
	setStatusLED(config & 0x04, form.dmaPause);
	setStatusLED(config & 0x02, form.timerSuspend);
	setStatusLED(config & 0x01, form.selFlashInfo);
}

void
ccloadView::setConnected()
{
	connected = 1;
	form.readLocation->setEnabled(true);
	form.setPC->setEnabled(true);
	form.run->setEnabled(true);
	form.step->setEnabled(true);
	form.halt->setEnabled(true);
	form.erasePage->setChecked(true);
	form.Connect->setText("Disconnect");
	if (maddr > 0) {
		form.readFile->setEnabled(true);
		form.writeFile->setEnabled(true);
	}
	if (app_msize > 0) {
		form.readFile_App->setEnabled(true);
		form.writeFile_App->setEnabled(true);
	}
	if (maddr > 0 && app_msize > 0) {
		form.writeAll->setEnabled(true);
		form.lockOnAll->setEnabled(true);
	}
	form.eraseChip->setEnabled(true);
	form.lock->setEnabled(true);
}

void
ccloadView::setDisconnected()
{
	connected = 0;
	if (port >= 0) {
		::close(port);
		delete lock;
		lock = 0;
		port = -1;
	}

	inDebugMode = false;
	form.Connect->setText("Connect");
	
	//cbChipModel.Items.Clear();
	form.chipModel->clear();
	form.chipModel->setEnabled(false);

	setStatusLabels(0);
	setConfigLabels(0);

	chipDefined = false;

	form.readLocation->setEnabled(false);
	form.setPC->setEnabled(false);
	form.run->setEnabled(false);
	form.step->setEnabled(false);
	form.halt->setEnabled(false);
	form.writeFile->setEnabled(false);
	form.writeFile_App->setEnabled(false);
	form.writeAll->setEnabled(false);
	form.lockOnAll->setEnabled(false);
	form.eraseChip->setEnabled(false);
	form.lock->setEnabled(false);
	form.readFile->setEnabled(false);
	form.readFile_App->setEnabled(false);
	form.chipSize->setText("");
	form.revision->setText("");
	form.chipSeries->setText("");
}
		
bool
ccloadView::DEBUG_INIT()
{
	return DEBUG_INIT(true);
}

bool
ccloadView::DEBUG_INIT(bool soft)
{
	if (soft && inDebugMode)
		return true;

	QString response = sendCommand("D", "Sending ENTER_DEBUG_MODE ...");
	if (parseOK(response)) {
		form.statusLine->setText("");
		inDebugMode = true;
		return true;
	}
	form.statusLine->setText("ENTER_DEBUG_MODE error:" + response);
	return false;
}

void
ccloadView::set_REGISTER(QLabel *lp, int v)
{
	v &= 0xff;
	lp->setText(QString("").sprintf("%02X", v));
}

bool
ccloadView::set_INSTR(QLabel *lp, unsigned char in0)
{
	unsigned char v;
	bool r = DEBUG_INSTR(in0, &v);
	set_REGISTER(lp, v);
	return r;
}

bool
ccloadView::set_INSTR(QLabel *lp, unsigned char in0, unsigned char in1)
{
	unsigned char v;
	bool r = DEBUG_INSTR(in0, in1, &v);
	set_REGISTER(lp, v);
	return r;
}
bool
ccloadView::set_INSTR(QLabel *lp, unsigned char in0, unsigned char in1, unsigned char in2)
{
	unsigned char v;
	bool r = DEBUG_INSTR(in0, in1, in2, &v);
	set_REGISTER(lp, v);
	return r;
}

bool
ccloadView::READ_REGISTERS()
{
	unsigned char a;
	DEBUG_INSTR(0x00, &a);		// nop
	set_REGISTER(form.REG_A, a);
	set_INSTR(form.REG_PSW, 0xe5, 0xd0);		// mov a, psw
	set_INSTR(form.REG_B, 0xe5, 0xf0);		// mov a, b
	set_INSTR(form.REG_SP, 0xe5, 0x81);		// mov a, sp
	set_INSTR(form.REG_DPH0, 0xe5, 0x83);		// mov a, dph0
	set_INSTR(form.REG_DPL0, 0xe5, 0x82);		// mov a, dpl0
	set_INSTR(form.REG_DPH1, 0xe5, 0x85);		// mov a, dph1
	set_INSTR(form.REG_DPL1, 0xe5, 0x84);		// mov a, dpl1
	set_INSTR(form.REG_R0, 0xe8);			// mov a, r0
	set_INSTR(form.REG_R1, 0xe9);			// mov a, r1
	set_INSTR(form.REG_R2, 0xea);			// mov a, r2
	set_INSTR(form.REG_R3, 0xeb);			// mov a, r3
	set_INSTR(form.REG_R4, 0xec);			// mov a, r4
	set_INSTR(form.REG_R5, 0xed);			// mov a, r5
	set_INSTR(form.REG_R6, 0xee);			// mov a, r6
	set_INSTR(form.REG_R7, 0xef);			// mov a, r7
	DEBUG_INSTR(0x74, a);				// mov a, #a
	int pc;
	GET_PC(pc);
        form.REG_PC->setText(QString("").sprintf("%04X", pc&0xffff));
        return true;
}

bool
ccloadView::READ_STATUS()
{
	unsigned char status;
	if (READ_STATUS(status)) {
		setStatusLabels(status);
		return true;
	}
	return false;
}

bool
ccloadView::READ_STATUS(unsigned char &status)
{
	status = 0;
	if (!DEBUG_INIT(1))
		return false;

	QString response = sendCommand("XW130R1", "Sending GET_STATUS ...");
	if (parseOK(response)) {
		if (getDataByte(0, getTokenREAD(response), status)) {
			form.statusLine->setText("");
			return true;
		}
	}
	form.statusLine->setText("GET_STATUS error:" + response);
	return false;
}

/// Activate/Deactivate RESET line
bool
ccloadView::RESET(bool state)
{
	if (!DEBUG_INIT(0))
		return false;

	QString response = sendCommand(QString("R") + (state ? "1" : "0"), "Sending RESET ...");
	if (parseOK(response)) {
		form.statusLine->setText("");
		return true;
	}
	form.statusLine->setText(QString("RESET error:") + response);
	return false;
}

bool
ccloadView::CLIENT(bool state)
{
	if (!DEBUG_INIT(1))
		return false;

	QString response = sendCommand(QString("R") + (state ? "2" : "3"), "Switching STATE ...");
	if (parseOK(response)) {
		form.statusLine->setText("");
		return true;
	}
	form.statusLine->setText(QString("CLIENT error:") + response);
	return false;
}

bool
ccloadView::LED(bool state)
{
	QString response = sendCommand(QString("L") + (state ? "1" : "0"), "Sending LED ...");
	if (parseOK(response)) {
		form.statusLine->setText("");
		return true;
	}
	form.statusLine->setText("LED error:" + response);
	return false;
}
/// Set to LOW or toggle DC line
bool
ccloadView::FLASHDC(bool state)
{
	QString response = sendCommand(QString("L") + (state ? "3" : "4"), "Sending Flash DC ...");
	if (parseOK(response)) {
		form.statusLine->setText("");
		return true;
	}
	form.statusLine->setText("Flash DC error:" + response);
	return false;
}

/// Set to LOW or toggle DD line
bool
ccloadView::FLASHDD(bool state)
{
	QString response = sendCommand(QString("L") + (state ? "5" : "6"), "Sending Flash DD ...");
	if (parseOK(response)) {
		form.statusLine->setText("");
		return true;
	}
	form.statusLine->setText("Flash DD error:" + response);
	return false;
}

/// Set to LOW or toggle RST line
bool
ccloadView::FLASHRST(bool state)
{
	QString response = sendCommand(QString("L") + (state ? "7" : "8"), "Sending Flash RST ...");
	if (parseOK(response)) {
		form.statusLine->setText("");
		return true;
	}
	form.statusLine->setText("Flash RST error:" + response);
	return false;
}
bool
ccloadView::READ_CONFIG()
{
	unsigned char config;
	return dbg_ReadConfig(config);
}

bool
ccloadView::dbg_ReadConfig(unsigned char &config)
{
	config = 0;

	if (!DEBUG_INIT(1))
		return false;

	QString response = sendCommand("XW124R1", "Sending RD_CONFIG ...");
	if (parseOK(response)) {
		if (getDataByte(0, getTokenREAD(response), config)) {
			setConfigLabels(config);
			form.statusLine->setText("");
			return true;
		}
	}
	form.statusLine->setText("RD_CONFIG error:" + response);
	return false;
}
bool
ccloadView::WRITE_CONFIG(unsigned char config)
{
	if (!DEBUG_INIT(1))
		return false;

	QString response = sendCommand(QString("XW21D") + QString("").sprintf("%02X", config) + "R1", "Sending WR_CONFIG ...");
	if (parseOK(response)) {
		form.statusLine->setText("");
		return true;
	}
	form.statusLine->setText("WR_CONFIG error:" + response);
	return false;
}

bool
ccloadView::GET_CHIP_ID()
{
	unsigned char id, revision;
	return GET_CHIP_ID(id, revision);
}

bool
ccloadView::GET_CHIP_ID(unsigned char &id, unsigned char &revision)
{
	id = 0;
	revision = 0;
	if (!DEBUG_INIT(1))
		return false;

	QString response = sendCommand(QString("XW168R2"), "Sending GET_CHIP_ID ...");
	if (parseOK(response)) {
		QString readData = getTokenREAD(response);
		if (getDataByte(0, readData, id) && getDataByte(1, readData, revision)) {
			if (id == 0 || id == 0xFF) {
				// those weird 2533's we bought, fake them out
                                if (id != 0xff || !(revision==0x11 || revision == 0x12) || !form.allowUnknowns->isChecked()) {
					form.statusLine->setText("GET_CHIP_ID error: Bad value " + QString("").sprintf("%02X", id));
					return false;
				}
			}

			form.chipID->setText(QString("").sprintf("%02X", id));
			form.revision->setText(QString("").sprintf("%02X", revision));

			chipDefined = true;

			switch (id) {
			case 0x8d:
				form.chipSeries->setText("CC2540");
				loadChipModel("CC2540F256;CC2540F128");
				form.chipModel->setEnabled(true);
				break;
			case 0x41:
				form.chipSeries->setText("CC2541");
				loadChipModel("CC2541F256;CC2541F128");
				form.chipModel->setEnabled(true);
				break;
			case 0xa5:
				form.chipSeries->setText("CC2530");
				loadChipModel("CC2530F256;CC2530F128;CC2530F64;CC2530F32");
				form.chipModel->setEnabled(true);
				break;
			case 0xb5:
				form.chipSeries->setText("CC2531");
				loadChipModel("CC2531F256;CC2531F128");
				form.chipModel->setEnabled(true);
				break;
			case 0x95:
				form.chipSeries->setText("CC2533");
				loadChipModel("CC2533F32;CC2533F64;CC2533F96");
				form.chipModel->setEnabled(true);
				break;
			case 0x91:
				form.chipSeries->setText("CC2511");
				loadChipModel("CC2511F32;CC2511F16;CC2511F08");
				form.chipModel->setEnabled(true);
				break;
			case 0x81:
				form.chipSeries->setText("CC2510");
				loadChipModel("CC2510F32;CC2510F16;CC2510F08");
				form.chipModel->setEnabled(true);
				break;
			case 0x89:
				form.chipSeries->setText("CC2431");
				loadChipModel("CC2431F128;CC2431F64;CC2431F32");
				form.chipModel->setEnabled(true);
				break;
			case 0x85:
				form.chipSeries->setText("CC2430");
				loadChipModel("CC2430F128;CC2430F64;CC2430F32");
				form.chipModel->setEnabled(true);
				break;
			case 0x01:
				form.chipSeries->setText("CC1110");
				loadChipModel("CC1110F32;CC1110F16;CC1110F08");
				form.chipModel->setEnabled(true);
				break;
			case 0xff:	// those weird 2533's we bought, fake them out
				if ((revision==0x11 || revision == 0x12) && form.allowUnknowns->isChecked()) {
					form.chipSeries->setText("CC2533");
					loadChipModel("CC2533F32;CC2533F64;CC2533F96");
					form.chipModel->setEnabled(true);
					break;
				}
				// fall thru
			default:
				chipDefined = false;
				form.chipSeries->setText("UNKNOWN");
				form.chipModel->setEnabled(false);
				form.statusLine->setText("GET_CHIP_ID error: Unknown CHIP ID " + QString("").sprintf("%02X", id));
				return false;
			}
			if (chipDefined) {
				if (READ_STATUS()) {
					form.statusLine->setText("");
					return true;
				}
				return false;
			}
		}
	}
	form.statusLine->setText("GET_CHIP_ID error:" + response);
	return false;
}

bool
ccloadView::HALT()
{
	if (!DEBUG_INIT(1))
		return false;
	QString response = sendCommand("XW140R1", "Sending HALT ...");
	if (parseOK(response)) {
		form.statusLine->setText("Halted");
		QString s("-- halt --\n");
		consoleDisplay(s);
		unsigned char d;
		if (getDataByte(0, getTokenREAD(response), d)) {
			setStatusLabels(d);
		}
		return true;
	}
	form.statusLine->setText("HALT error:" + response);
	return false;
}

bool
ccloadView::RESUME(bool run)
{
	if (!DEBUG_INIT(1))
		return false;
	QString response = sendCommand("XW148R1", "Sending RESUME ...");
	if (parseOK(response)) {
	        unsigned char d;   
		form.statusLine->setText("Running");
		if (run) {
			QString s("-- run  --\n");
			consoleDisplay(s);
		}
		if (getDataByte(0, getTokenREAD(response), d)) {
			setStatusLabels(d);
		}
		return true;
	}
	form.statusLine->setText("RESUME error:" + response);
	return false;
}
bool
ccloadView::STEP()
{
	if (!DEBUG_INIT(1))
		return false;
	QString response = sendCommand("XW158R1", "Sending STEP ...");
	if (parseOK(response)) {
		unsigned char d;
		form.statusLine->setText("Halted");
		if (getDataByte(0, getTokenREAD(response), d)) {
			setStatusLabels(d);
		}
		return true;
	}
	form.statusLine->setText("RESUME error:" + response);
	return false;
}

bool
ccloadView::MASS_ERASE_FLASH()
{
	bool result = true;
	DEBUG_INIT(1);
	HALT();
	result = result ? DEBUG_INIT(false) : false;
	result = result ? DEBUG_INSTR(0x00) : false;
	result = result ? CHIP_ERASE() : false;
	int retry = 10;
	unsigned char status;
	Sleeper::msleep(100);
	while (result && retry-- > 0) {
		if (!READ_STATUS(status))
			return false;
		setStatusLabels(status);
		if (!(status & CHIP_ERASE_DONE)) 
			return true;
		Sleeper::msleep(100);
		//Application.DoEvents();
		//Thread.Sleep(1);
	}
	return false;
}

bool
ccloadView::CHIP_ERASE()
{
	QString response = sendCommand("XW110R1", "Sending CHIP_ERASE ...");
	if (parseOK(response))
		return true;
	form.statusLine->setText("CHIP_ERASE error:" + response);
	return false;
}

bool
ccloadView::DEBUG_INSTR(unsigned char in0)
{
	unsigned char data;
	return DEBUG_INSTR(in0, &data);
}

bool
ccloadView::DEBUG_INSTR(unsigned char in0, unsigned char *data)
{
	unsigned char cmds[1];
	cmds[0] = in0;
	return dbg_DebugInstr(cmds, 1, data);
}

bool
ccloadView::DEBUG_INSTR(unsigned char in0, unsigned char in1, unsigned char *data)
{
	unsigned char cmds[2];
	cmds[0] = in0;
	cmds[1] = in1;
	return dbg_DebugInstr(cmds, 2, data);
}
bool
ccloadView::DEBUG_INSTR(unsigned char in0, unsigned char in1)
{
	unsigned char cmds[2], data;
	cmds[0] = in0;
	cmds[1] = in1;
	return dbg_DebugInstr(cmds, 2, &data);
}
bool
ccloadView::DEBUG_INSTR(unsigned char in0, unsigned char in1, unsigned char in2, unsigned char *data)
{
	unsigned char cmds[3];
	cmds[0] = in0;
	cmds[1] = in1;
	cmds[2] = in2;
	return dbg_DebugInstr(cmds, 3, data);
}
bool
ccloadView::DEBUG_INSTR(unsigned char in0, unsigned char in1, unsigned char in2)
{
	unsigned char cmds[3], data;
	cmds[0] = in0;
	cmds[1] = in1;
	cmds[2] = in2;
	return dbg_DebugInstr(cmds, 3, &data);
}
bool
ccloadView::dbg_DebugInstr(unsigned char *cmds, int len, unsigned char *data)
{
        unsigned char d;
	*data = 0;

	if (!DEBUG_INIT(1))
		return false;

	if (len > 3) {
		form.statusLine->setText("DEBUG_INSTR error: Too long commands, maximum 3");
		return false;
	}

	QString cmd = "";
	for (int i = 0; i < len; ++i)
		cmd += QString("").sprintf("%02X", cmds[i]);
	cmd = "XW" + QString("").sprintf("%d%02X", 1 + len, 0x50 + len) + cmd + "R1";
//std::cout<<"CMD='"<<cmd.toLatin1().data_ptr()<<"'\n";
	QString response = sendCommand(cmd, "Sending DEBUG_INSTR ...");
	if (parseOK(response)) {
		if (getDataByte(0, getTokenREAD(response), d)) {
			*data = d;
			form.statusLine->setText("");
			return true;
		}
	}
	form.statusLine->setText("DEBUG_INSTR error:" + response);
	return false;
}

bool
ccloadView::CLOCK_INIT()
{
	unsigned char d;
	if (DEBUG_INSTR(0x75, 0xC6, 0x00, &d)) {					//MOV CLKCON, 0x00
		int retry = 5;
		unsigned char sleepReg;
//printf("CLOCK_INIT sleeping\n");fflush(stdout);
		Sleeper::msleep(100);
		while (retry-- > 0) {
//printf("CLOCK_INIT read sleep retry=%d\n", retry);fflush(stdout);
			if (!DEBUG_INSTR(0xE5, 0x9E, &sleepReg))	//MOV A, SLEEP; (sleepReg = A)
				return false;
//printf("sleepReg=0x%x\n", sleepReg);fflush(stdout);
			if ((sleepReg & 0x40) == 0) {
				retry = 5;
				while (retry-- > 0) {
				    unsigned char status;
				    READ_STATUS(status);
				    setStatusLabels(status);
				    if (status&0x02) 
					return true;
				    Sleeper::msleep(100);
				}
				form.statusLine->setText("Oscilator not stable");
				return false;
			}
			Sleeper::msleep(100);
		}
		form.statusLine->setText("No 0x40 in CLKCON");
	}
	return false;
}

bool
ccloadView::WRITE_XDATA_MEMORY(int address, unsigned char *buffer, int length)
{
	const int PACKET_SIZE = 64;

	if (!DEBUG_INIT(1))
		return false;

	int i = 0;
	int nextAddress = address;
	while (length > 0) {
		int sentBytes = length > PACKET_SIZE ? PACKET_SIZE : length;
		QString response = QString("").sprintf("MW%04X%02X", address, sentBytes);
		nextAddress += sentBytes;
		length -= sentBytes;
		while (sentBytes-- > 0)
			response += QString("").sprintf("%02X", buffer[i++]);

		response = sendCommand(response, QString("").sprintf("Sending WRITE_XDATA %04X ...", address));
		address = nextAddress;
		if (parseOK(response)) 
			continue;
		form.statusLine->setText("WRITE_XDATA error:" + response);
		//LED(false);
		return false;
	}
	//LED(false);
	return true;
}

bool
ccloadView::READ_XDATA_MEMORY(int address, int length, unsigned char *buffer, int &outlen)
{
	const int PACKET_SIZE = 8;
	outlen = 0;
	if (!DEBUG_INIT(1))
		return false;

	int i = 0;
	int nextAddress = address;
	unsigned char data;

	while (length > 0) {
		int sentBytes = length > PACKET_SIZE ? PACKET_SIZE : length;
		QString response = QString("").sprintf("MR%04X%02X", address, sentBytes);
		nextAddress += sentBytes;
		length -= sentBytes;
		response = sendCommand(response, QString("").sprintf("Sending READ_XDATA (%04X, %d) ...", address, sentBytes));
		address = nextAddress;
		if (parseOK(response)) {
			int j = 0;
			response = getTokenREAD(response);
			while (sentBytes-- > 0)
			if (getDataByte(j++, response, data)) {
				buffer[i++] = data;
				outlen++;
			} else {
				form.statusLine->setText("READ_XDATA error: Not hex " + response.mid(j * 2, 2));
				LED(false);
				return false;
			}
		} else {
			form.statusLine->setText("READ_XDATA error:" + response);
			LED(false);
			return false;
		}
	}
	LED(false);
	return true;
}

bool
ccloadView::READ_CODE_MEMORY(int address, unsigned char bank, int length, unsigned char *buffer, int &outlen)
{
	const int PACKET_SIZE = 8;
	outlen=0;
	if (!DEBUG_INIT(1))
		return false;

	int i = 0;
	int nextAddress = address;
	unsigned char data;

	bool valid = true;
	valid = valid ? DEBUG_INSTR(0x75, 0xC7, (((bank << 4) | 0x01) & 0xFF)) : false;
	while(length > 0) {
		int sentBytes = length > PACKET_SIZE ? PACKET_SIZE : length;
		QString response = QString("").sprintf("MC%04X%02X", address, sentBytes);
		nextAddress += sentBytes;
		length -= sentBytes;
		response = sendCommand(response, QString("").sprintf("Sending READ_CODE (%04X, %d) ...", address, sentBytes));
		address = nextAddress;
		if (parseOK(response)) {
			int j = 0;
			response = getTokenREAD(response);
			while (sentBytes-- > 0)
			if (getDataByte(j++, response, data)) {
				outlen++;
				buffer[i++] = data;
			} else {
				form.statusLine->setText("READ_CODE error: Not a hex " + response.mid(j * 2, 2));
				LED(false);
				return false;
			}
		} else {
			form.statusLine->setText("READ_XDATA error:" + response);
			LED(false);
			return false;
		}
	}
	LED(false);
	return true;
}

bool
ccloadView::SET_PC(int address)
{
	if (!DEBUG_INIT(1))
		return false;
	return DEBUG_INSTR(0x02, (unsigned char)((address >> 8) & 0xFF), (unsigned char)(address & 0xFF));		//LJMP iAddr
}

bool
ccloadView::GET_PC(int &address)
{
	address = 0;
	if (!DEBUG_INIT(1))
		return false;
	QString response = sendCommand("XW128R2", "Sending GET_PC ...");
	if (parseOK(response)) {
		response = getTokenREAD(response);
		if (!response.isEmpty()) {
			unsigned char bh, bl;
			if (getDataByte(0, response, bh) && getDataByte(1, response, bl)) {
				address = ((bh << 8) & 0xFF00) | bl;
				return true;
			}
		}
	}
	form.statusLine->setText("GET_PC error:" + response);
	return false;
}

bool
ccloadView::WRITE_PAGE_FLASH(long iPageAddress, unsigned char *buffer, int length, bool erasePage)
{
	bool valid = true;
	unsigned char routine[1024]; int rlen=0;
	addRoutine(routine, rlen, 0x90, 0x62, 0x71);						 // mov DPTR, #FADDRL
	addRoutine(routine, rlen, 0x74, (iPageAddress/FLASH_WORD_SIZE)&0xff);			 // mov A, #page address lo
	addRoutine(routine, rlen, 0xf0);							 // mov @DPTR, A
	addRoutine(routine, rlen, 0xA3);							 // inc DPTR
	addRoutine(routine, rlen, 0x74, (iPageAddress/FLASH_WORD_SIZE) >> 8);	 		 // mov A, #page address hi
	addRoutine(routine, rlen, 0xf0);							 // mov @DPTR, A
	addRoutine(routine, rlen, 0x75, 0x92, 0x01);                                             // set dptr 1
	addRoutine(routine, rlen, 0x90, 0x62, 0x70);						 // mov DPTR1, #FCTL

	addRoutine(routine, rlen, 0xE0);						 	// 1:  mov A, @DPTR1
	addRoutine(routine, rlen, 0x20, 0xE7, 0xFc);					 	//     JB 0xe7, 1b
	if (erasePage) {
		addRoutine(routine, rlen, 0x74, 0x01);						 // mov A, #0x01
		addRoutine(routine, rlen, 0xf0);						 // mov @DPTR1, A
		addRoutine(routine, rlen, 0xE0);						 // 1:  mov A, @DPTR1
		addRoutine(routine, rlen, 0x20, 0xE7, 0xFc);					 //     JB 0xe7, 1b
	}
	
	addRoutine(routine, rlen, 0x74, 0x02);						 	 // mov A, #0x02
	addRoutine(routine, rlen, 0xf0);							 // mov @DPTR1, A
	addRoutine(routine, rlen, 0x90, 0x62, 0x73);						 // mov DPTR1, #FWDATA
	
	addRoutine(routine, rlen, 0x75, 0x92, 0x00);                                             // set dptr 0
	addRoutine(routine, rlen, 0x90, 0x00, 0x00);						 // mov DPTR0, #0x0000

	addRoutine(routine, rlen, 0x7F, (((length / FLASH_WORD_SIZE) >> 8) & 0xFF));	 	// mov R7, #... pages/word hi
	addRoutine(routine, rlen, 0x7E, ((length / FLASH_WORD_SIZE) & 0xFF));			 // mov R6, #... pages/word low
	addRoutine(routine, rlen, 0x7D, FLASH_WORD_SIZE);					 //2:   mov R5, #FLASH_WORD_SIZE
	    addRoutine(routine, rlen, 0xE0);							 //1:  mov A, @DPTR0
	    addRoutine(routine, rlen, 0xA3);							 //    inc DPTR
	    addRoutine(routine, rlen, 0x75, 0x92, 0x01);                                         //    set dptr 1
	    addRoutine(routine, rlen, 0xf0);							 //    mov @DPTR1, A   write to FWDATA
	    addRoutine(routine, rlen, 0x75, 0x92, 0x00);                                         //    set dptr 0
	    addRoutine(routine, rlen, 0xDD, 0xF5);						 //    djnz R5, 1b
	    
	addRoutine(routine, rlen, 0x75, 0x92, 0x01);      	                                 // set dptr 1
	addRoutine(routine, rlen, 0x90, 0x62, 0x70);						 // mov DPTR1, #FCTL
	addRoutine(routine, rlen, 0xE0);							 //1:  mov A, @DPTR1
	addRoutine(routine, rlen, 0x20, 0xE6, 0xFc);                                             //    jb 0xe6, 1b	while 'full'
	addRoutine(routine, rlen, 0x90, 0x62, 0x73);						 // mov DPTR1, #FWDATA
	addRoutine(routine, rlen, 0x75, 0x92, 0x00);                                             // set dptr 0
	
	addRoutine(routine, rlen, 0xDE, 0xe1);							 // djnz r6, 2b -31
	if ((((length / FLASH_WORD_SIZE) >> 8) & 0xFF) != 0)
		addRoutine(routine, rlen, 0xDF, 0xdf);                                           // djnz r7, 2b
	
	addRoutine(routine, rlen, 0x90, 0x62, 0x70);						 // mov DPTR1, #FCTL
	addRoutine(routine, rlen, 0x74, 0x0);						 	 // mov A, #0x00
	addRoutine(routine, rlen, 0xf0);							 // mov @DPTR1, A
	
	addRoutine(routine, rlen, 0xA5);							 // 1: invalid?
	addRoutine(routine, rlen, 0x80, 0xfd);						 	 //    jmp 1b
	
//printf("writing debug inst\n");fflush(stdout);
	valid = valid ? DEBUG_INSTR(0x75, 0x9f, (unsigned char)0x00) : false; // map flash to 0x8000
	valid = valid ? DEBUG_INSTR(0x75, 0xC7, 0x08) : false; 		      // map sram to 0x8000
//printf("routine =");for (int i=0;i<rlen; i++) printf(" %02x", routine[i]);printf("\n");fflush(stdout);
//printf("writing xdata data len=%d\n", length);fflush(stdout);
	valid = valid ? WRITE_XDATA_MEMORY(0x0000, buffer, length) : false;
//printf("writing xdata code rlen=%d\n", length);fflush(stdout);
	valid = valid ? WRITE_XDATA_MEMORY(0x0000 + FLASH_PAGE_SIZE, routine, rlen) : false;
//printf("setting PC=0x%x\n", 0x8000 + FLASH_PAGE_SIZE);fflush(stdout);
	valid = valid ? SET_PC(0x8000 + FLASH_PAGE_SIZE) : false;
//printf("resuming\n");fflush(stdout);
	valid = valid ? RESUME(0) : false;
	if (valid) {
		unsigned char status;
		int retry = 20;
		do {
			READ_STATUS(status);
			setStatusLabels(status);
//printf("read status=0x%x\n", status);fflush(stdout);
			if ((status & CPU_HALTED) == CPU_HALTED)
				return true;
			Sleeper::msleep(100);
			//Application.DoEvents();
		} while (retry-- > 0);
	}
	return false;
}

bool
ccloadView::READ_FLASH_PAGE(long iPageAddress, int length, unsigned char *code, int &clen)
{
	return READ_CODE_MEMORY((int)(iPageAddress & 0x7FFFF), (unsigned char)((iPageAddress >> 15) & 0x03), length, code, clen);
}

void
ccloadView::btnFlashDD_Click()
{
	if(Connect()) {
		int times = 5;
		while (--times > 0) {
			FLASHDD(true);
			Sleeper::msleep(2);
			FLASHDD(false);
			Sleeper::msleep(2);
		}
		setDisconnected();
	}
}

void
ccloadView::btnFlashDC_Click()
{
	if (Connect()) {
		int times = 5;
		while (--times > 0) {
			FLASHDC(true);
			Sleeper::msleep(2);
			FLASHDC(false);
			Sleeper::msleep(2);
		}
		setDisconnected();
	}
}

void
ccloadView::btnFlashRST_Click()
{
	if (Connect()) {
		int times = 5;
		while (--times > 0) {
			FLASHRST(true);
			Sleeper::msleep(2);
			FLASHRST(false);
			Sleeper::msleep(2);
		}
		setDisconnected();
	}
}

bool
ccloadView::Connect()
{
	if(port >= 0)
		return true;
	if (!form.port->text().isEmpty()) {
		form.Connect->setText("Connecting ...");
		lock = new ttylock(form.port->text());
		if (lock->lock()) {
		    port = ::open(form.port->text().toLatin1(), O_RDWR|O_NONBLOCK);
		    if (port < 0) {
			    form.statusLine->setText("Can't open port: " +form.port->text());
			    delete lock;
			    lock = 0;
			    form.Connect->setText("Connect");
			    return false;
		    }
		    struct termios t;
		    tcgetattr(port, &t);
		    cfmakeraw(&t);
		    cfsetspeed(&t, 9600);
		    t.c_iflag &= ~IXOFF;
		    t.c_iflag &= ~IXON;
		    t.c_iflag &= ~CRTSCTS;
		    t.c_cflag |= HUPCL;
		    tcsetattr(port, TCSANOW, &t);
		    ::close(port);
		    port = ::open(form.port->text().toLatin1(), O_RDWR|O_NONBLOCK);
		    t.c_cflag &= ~HUPCL;
		    tcsetattr(port, TCSANOW, &t);

		//port.BaudRate = Settings.Default.Baudrate;
		//port.Handshake = Handshake.None;
		//port.DtrEnable = true;

		    ::write(port, "+++ATRF\r\n", 9);	// switch to prog mode
		    if (!sendCommand("", "Wait for start").isEmpty()) {
			    form.Connect->setText("Disconnect");
			    CLIENT(prod);
			    return true;
		    }
		}
		delete lock;
		lock = 0;
	}
	form.Connect->setText("Connect");
	return false;
}

void
ccloadView::btnConnect_Click()
{
	if (port >= 0) {
		setDisconnected();
		return;
	}

	if (!Connect()) 
		return;
	if (GET_CHIP_ID() && READ_STATUS() && READ_REGISTERS()) {
		setConnected();
	} else {
		setDisconnected();
	}
}

void
ccloadView::cbChipModel_SelectedIndexChanged(int)
{
	form.statusLine->setText("");
//printf("cbChipModel_SelectedIndexChanged\n");fflush(stdout);
	if (form.chipModel->currentIndex() >= 0) {
		char **p;
		QString model = form.chipModel->currentText() + ";";
//printf("model='%s'\n",model.toLatin1().data_ptr());fflush(stdout);
		for(p = &ChipDescriptors[0]; *p; p++) {
			QString descriptor(*p);
//printf("descriptor='%s'\n",descriptor.toLatin1().data_ptr());fflush(stdout);
			if (descriptor.isEmpty())
				continue;
			if (descriptor.startsWith(model)) {
				bool ok1=false, ok2=false, ok3=false;
				FLASH_SIZE = descriptor.section(";", 1, 1).toULong(&ok1,16);
				FLASH_PAGE_SIZE = descriptor.section(";", 2, 2).toInt(&ok2,16);
				FLASH_WORD_SIZE = descriptor.section(";", 3, 3).toInt(&ok3,16);
					
				if (ok1&&ok2&&ok3) {
					form.chipSize->setText(QString("").sprintf("%dK", FLASH_SIZE / 1024));
					return;
				}
				form.statusLine->setText("Bad chip descriptor(s)");
				break;
			}
		}
		if (form.statusLine->text().isEmpty())
			form.statusLine->setText(QString("Chip %1 not found in chip descriptors").arg(form.chipModel->currentText()));
	}
	form.chipSize->setText("");
}

static 
int hex(QFile *f)
{
	char c1, c2;
	int r;
	if (!f->getChar(&c1))
		return -1;
	if (!f->getChar(&c2))
		return -1;
	if (c1 >= '0' && c1 <= '9') {
		r = c1-'0';
	} else
	if (c1 >= 'A' && c1 <= 'F') {
		r = c1-'A'+10;
	} else
	if (c1 >= 'a' && c1 <= 'f') {
		r = c1-'a'+10;
	} else return -1;
	r=r<<4;
	if (c2 >= '0' && c2 <= '9') {
		r += c2-'0';
	} else
	if (c2 >= 'A' && c2 <= 'F') {
		r += c2-'A'+10;
	} else
	if (c2 >= 'a' && c2 <= 'f') {
		r += c2-'a'+10;
	} else return -1;
	return r;
}

void
ccloadView::btnSelectFile_Click()
{
	QFileDialog* fd = new QFileDialog( this ,"",form.fileName->text());
	fd->setFileMode( QFileDialog::AnyFile);
	fd->show();
	if ( fd->exec() == QDialog::Accepted ) {
	    QString fileName = fd->selectedFiles()[0];
	    form.fileName->setText(fileName);
	    settings->setValue("fileName", fileName);
	    settings->sync();
	    btnSelectLoad_Click();
	}
}

void
ccloadView::btnSelectFile_App_Click()
{
	QFileDialog* fd = new QFileDialog( this ,"",form.fileName_App->text());
	fd->setFileMode( QFileDialog::AnyFile);
	fd->show();
	if ( fd->exec() == QDialog::Accepted ) {
	    QString fileName = fd->selectedFiles()[0];
	    form.fileName_App->setText(fileName);
	    settings->setValue("fileName_App", fileName);
	    settings->sync();
	    btnSelectLoad_App_Click();
	}
}

void
ccloadView::btnSelectLoad_Click()
{
        QString fileName = form.fileName->text();

	if (fileName.isEmpty()) {
		form.loadFile->setEnabled(false);
		form.writeFile->setEnabled(false);
		form.writeAll->setEnabled(false);
		form.lockOnAll->setEnabled(false);
		form.readFile->setEnabled(false);
		return;
	}
	form.loadFile->setEnabled(true);

	QFile f(fileName);
	
	if (!f.open(QIODevice::ReadOnly)) {
		form.statusLine->setText(QString("Can't open file %1").arg(fileName));
		maddr = 0;
		return;
	}
	form.startAddress->setText("0x0000");
	form.endAddress->setText("-");
	bool first = 1;
	maddr=0;
	memset(image, 0xff, sizeof(image));
	if (fileName.right(4) == ".ihx") {
	    for (;;) {
	    	char c;
	    	int i;
	    	int sum=0, len, addr;
	    	if (!f.getChar(&c)) 
		    break;
	    	if (c == '\n') 
		    continue;
	    	if (c != ':') {
		    if (first) {
			form.statusLine->setText(QString("File %1 not in intel hex format").arg(fileName));
			f.close();
			maddr = 0;
			return;
		    }
		    break;
	    	}
	    	len = hex(&f);
	    	if (len < 0) 
		    break;
	    	sum += len;
	    	addr = hex(&f);
	    	if (addr < 0)
		    break;
	    	sum += addr;
	    	i = hex(&f);
	    	if (i < 0)	
		    break;
	    	sum += i;
	    	addr = (addr<<8)+i;
	    	int type = hex(&f);
	    	if (type < 0)
		    break;
	    	sum += type;
	    	if (type == 0x01)
		    break;
	    	if (first) {
			first = 0;
			form.startAddress->setText(QString("0x%1").arg(addr, 4, 16, QLatin1Char('0')));
	    	}
	    	for (i = 0; i < len; i++) {
			int v = hex(&f);
			if (v < 0)
				break;
			image[(addr+i)&0xffff] = v;
			sum += v;
	    	}
	    	i = hex(&f);
	    	if ( i < 0)
			break;
	    	if (i != ((0x100-(sum&0xff))&0xff)) {
			form.statusLine->setText(QString("Bad checksum in file %1 @0x%2").arg(fileName).arg(addr, 4, 16, QLatin1Char('0')));
			return;
	    	}
	    	addr += len-1;
	    	if (addr > maddr)
		    	maddr = addr;
	    }	 
	} else {
		maddr = f.size();
		if (maddr > sizeof(image))
			maddr = sizeof(image);
		f.read((char*)&image[0], maddr);
	}
	form.endAddress->setText(QString("0x%1").arg(maddr, 4, 16, QLatin1Char('0')));
	f.close();

	if (maddr > 0 && connected) {
		form.writeFile->setEnabled(true);
		form.readFile->setEnabled(true);
		if (maddr > 0 && app_msize > 0) {
			form.writeAll->setEnabled(true);
			form.lockOnAll->setEnabled(true);
		}
	}
}

void
ccloadView::btnSelectLoad_App_Click()
{
        QString fileName = form.fileName_App->text();
	unsigned char k[16];
	unsigned char h[4];

	form.writeFile_App->setEnabled(false);
	form.readFile_App->setEnabled(false);
	if (fileName.isEmpty()) {
		form.loadFile_App->setEnabled(false);
		return;
	}
	form.loadFile_App->setEnabled(true);

	QFile f(fileName);
	
	if (!f.open(QIODevice::ReadOnly)) {
		form.statusLine->setText(QString("Can't open file %1").arg(fileName));
		app_msize = 0;
		return;
	}
	if (f.read((char*)&h[0], 4) != 4) {
fail:
		form.statusLine->setText(QString("Bad file format %1").arg(fileName));
		f.close();
		app_msize = 0;
		return;
	}
	if (f.read((char*)&k[0], 16) != 16) 
		goto fail;
	int s = h[0] | (h[1]<<8);
	int l = h[2] | (h[3]<<8);
	if ((s&0x3ff) != 0)
		goto fail;
	if ((s+l) > 65536)
		goto fail;
	memset(&app_image[0], 0xff, sizeof(app_image));
	if (f.read((char*)&app_image[s], l) != l) 
		goto fail;
	app_mstart = s;
	app_msize = l;
	f.close();
	form.startAddress_App->setText(QString("0x%1").arg(app_mstart, 4, 16, QLatin1Char('0')));
	form.endAddress_App->setText(QString("0x%1").arg(app_mstart+app_msize-1, 4, 16, QLatin1Char('0')));
	if (app_msize > 0 && connected) {
		form.writeFile_App->setEnabled(true);
		form.readFile_App->setEnabled(true);
		if (maddr > 0 && app_msize > 0) {
			form.writeAll->setEnabled(true);
			form.lockOnAll->setEnabled(true);
		}
	}
}

void
ccloadView::btnErase_Click()
{
	MASS_ERASE_FLASH();
}

void
ccloadView::btnLock_Click()
{
	bool valid = true;
//printf("setting DEBUG_INIT(false)\n");fflush(stdout);
	valid = valid ? DEBUG_INIT(false) : false;
//printf("gave %d\n", valid);fflush(stdout);
//printf("setting CLOCK_INIT\n");fflush(stdout);
	valid = valid ? CLOCK_INIT() : false;
//printf("gave %d\n", valid);fflush(stdout);
//printf("FLASH_PAGE_SIZE 0x%x\n", FLASH_PAGE_SIZE);fflush(stdout);

	form.progress->setValue(0);
	if (valid) {
		unsigned char val[4] = {0xff, 0xff, 0xff, 0x7f};	// lock bit
//printf("loop valid %d off %d\n", valid, off);fflush(stdout);	  
		//WRITE_PAGE_FLASH((64*1024)-4, &val[0], 4, 0);
		WRITE_PAGE_FLASH(FLASH_SIZE-4, &val[0], 4, 0);
	}
	DEBUG_INIT(false);
	form.progress->setValue(100);
}

void
ccloadView::btnWrite_Click()
{
	unsigned int machi=0, maclow=0;

	if (form.fileName->text().isEmpty()) {
	    btnSelectFile_Click();
	    if (form.fileName->text().isEmpty() || maddr == 0) 
		return;
	}
	if (form.writeMAC->isChecked()) {
		machi = form.hiMAC->text().toUInt(0, 16);
		maclow = form.lowMAC->text().toUInt(0, 16);
		image[14] = machi>>24;
		image[15] = machi>>16;
		image[16] = machi>>8;
		image[17] = machi;
		image[22] = maclow>>24;
		image[23] = maclow>>16;
		image[24] = maclow>>8;
		image[25] = maclow;
	}
	int blen=0;
	bool valid = true;
	long length = maddr+1;
//printf("setting DEBUG_INIT(false)\n");fflush(stdout);
	valid = valid ? DEBUG_INIT(false) : false;
//printf("gave %d\n", valid);fflush(stdout);
//printf("setting CLOCK_INIT\n");fflush(stdout);
	valid = valid ? CLOCK_INIT() : false;
//printf("gave %d\n", valid);fflush(stdout);
//printf("FLASH_PAGE_SIZE 0x%x\n", FLASH_PAGE_SIZE);fflush(stdout);

	form.progress->setMinimum(0);
	form.progress->setMaximum((int)(100));
	form.progress->setValue(0);

	long pageAddress = 0;
	unsigned char *buffer;
	int off = 0;
	while (valid && length > 0) {
//printf("loop valid %d off %d\n", valid, off);fflush(stdout);	  
		form.progress->setValue(100*off/(maddr+1));

		buffer = &image[off];
		if (length >= (long)FLASH_PAGE_SIZE) {
			length -= (long)FLASH_PAGE_SIZE;
			off += FLASH_PAGE_SIZE;
		} else {
			
			off += length;
			length = 0;
		}
		if (!isPageEmpty(buffer)) {
			// valid =
			WRITE_PAGE_FLASH(pageAddress, buffer, FLASH_PAGE_SIZE, form.erasePage->isChecked());
			if (valid && form.verifyAfterWrite->isChecked()) {
				unsigned char code[FLASH_PAGE_SIZE];
				memset(code, 0xff, sizeof(code));
				int clen;
				valid = READ_FLASH_PAGE(pageAddress, FLASH_PAGE_SIZE, code, clen);
				for (int i = 0; i < FLASH_PAGE_SIZE; ++i) {
					if (buffer[i] != code[i]) {
						form.statusLine->setText("Verify failed");
						valid = false;
						break;
					}
				}
				form.statusLine->setText("Verify OK");
			}
			pageAddress += (long)FLASH_PAGE_SIZE;
		}
	}
	if (form.writeMAC->isChecked() && form.autoIncMAC->isChecked()) {
		char t[10];
		maclow++;
		snprintf(t, sizeof(t), "%08X", maclow);
		form.lowMAC->setText(QString::fromLatin1(&t[0]));
	}

	DEBUG_INIT(false);
	form.progress->setValue(100);
}

void
ccloadView::btnWrite_All_Click()
{
	btnWrite_Click();
	btnWrite_App_Click();
	if (form.lockOnAll->isChecked())
		btnLock_Click();
}

void
ccloadView::btnWrite_App_Click()
{
	if (form.fileName_App->text().isEmpty()) {
	    btnSelectFile_App_Click();
	    if (form.fileName_App->text().isEmpty() || app_msize == 0) 
		return;
	}
	if (!app_msize) 
		return;
	int blen=0;
	bool valid = true;
	long length = app_msize;
//printf("setting DEBUG_INIT(false)\n");fflush(stdout);
	valid = valid ? DEBUG_INIT(false) : false;
//printf("gave %d\n", valid);fflush(stdout);
//printf("setting CLOCK_INIT\n");fflush(stdout);
	valid = valid ? CLOCK_INIT() : false;
//printf("gave %d\n", valid);fflush(stdout);
//printf("FLASH_PAGE_SIZE 0x%x\n", FLASH_PAGE_SIZE);fflush(stdout);

	form.progress->setMinimum(0);
	form.progress->setMaximum((int)(100));
	form.progress->setValue(0);

	long pageAddress = app_mstart;
	unsigned char *buffer;
	int off = 0;
	while (valid && length > 0) {
//printf("loop valid %d off %d\n", valid, off);fflush(stdout);	  
		form.progress->setValue(100*off/(app_msize));

		buffer = &app_image[app_mstart+off];
		if (length >= (long)FLASH_PAGE_SIZE) {
			length -= (long)FLASH_PAGE_SIZE;
			off += FLASH_PAGE_SIZE;
		} else {
			
			off += length;
			length = 0;
		}
		if (!isPageEmpty(buffer)) {
			// valid =
			WRITE_PAGE_FLASH(pageAddress, buffer, FLASH_PAGE_SIZE, form.erasePage_App->isChecked());
			if (valid && form.verifyAfterWrite_App->isChecked()) {
				unsigned char code[FLASH_PAGE_SIZE];
				memset(code, 0xff, sizeof(code));
				int clen;
				valid = READ_FLASH_PAGE(pageAddress, FLASH_PAGE_SIZE, code, clen);
				for (int i = 0; i < FLASH_PAGE_SIZE; ++i) {
					if (buffer[i] != code[i]) {
						form.statusLine->setText("Verify failed");
						valid = false;
						break;
					}
				}
				form.statusLine->setText("Verify OK");
			}
			pageAddress += (long)FLASH_PAGE_SIZE;
		}
	}
	DEBUG_INIT(false);
	form.progress->setValue(100);
}

void
ccloadView::btnDebug_Click()
{
    prod = 0;
    if (port >= 0)
	    CLIENT(0);
}

void
ccloadView::btnProduction_Click()
{
    prod = 1;
    if (port >= 0)
	    CLIENT(1);
}

void
ccloadView::btnRead_App_Click()
{
	if (form.fileName_App->text().isEmpty()) {
	    btnSelectFile_App_Click();
	    if (form.fileName_App->text().isEmpty()) 
		return;
	}
	return;
	FILE *fs = fopen(form.fileName_App->text().toLatin1(), "w");
	if (!fs) {
		form.statusLine->setText("Error: file create failed");
		return;
	}
	bool valid = true;
	valid = valid ? DEBUG_INIT(false) : false;
	valid = valid ? CLOCK_INIT() : false;

	form.progress->setMinimum(0);
	form.progress->setMaximum((int)(FLASH_SIZE / (long)FLASH_PAGE_SIZE));
	form.progress->setValue(0);

	long pageAddress = 0;
	int blen = 0;
	while (valid && pageAddress < FLASH_SIZE) {
		unsigned char buffer[FLASH_PAGE_SIZE];
		form.progress->setValue(form.progress->value()+1);
		valid = valid ? READ_FLASH_PAGE(pageAddress, FLASH_PAGE_SIZE, buffer, blen) : false;
		if (valid)
			fwrite(buffer, 1, blen, fs);
		pageAddress += FLASH_PAGE_SIZE;
	}
	if (fs)
		fclose(fs);
	DEBUG_INIT(false);
	form.progress->setValue(0);
}

void
ccloadView::btnRead_Click()
{
	if (form.fileName->text().isEmpty()) {
	    btnSelectFile_Click();
	    if (form.fileName->text().isEmpty()) 
		return;
	}
	return;
	FILE *fs = fopen(form.fileName->text().toLatin1(), "w");
	if (!fs) {
		form.statusLine->setText("Error: file create failed");
		return;
	}
	bool valid = true;
	valid = valid ? DEBUG_INIT(false) : false;
	valid = valid ? CLOCK_INIT() : false;

	form.progress->setMinimum(0);
	form.progress->setMaximum((int)(FLASH_SIZE / (long)FLASH_PAGE_SIZE));
	form.progress->setValue(0);

	long pageAddress = 0;
	int blen = 0;
	while (valid && pageAddress < FLASH_SIZE) {
		unsigned char buffer[FLASH_PAGE_SIZE];
		form.progress->setValue(form.progress->value()+1);
		valid = valid ? READ_FLASH_PAGE(pageAddress, FLASH_PAGE_SIZE, buffer, blen) : false;
		if (valid)
			fwrite(buffer, 1, blen, fs);
		pageAddress += FLASH_PAGE_SIZE;
	}
	if (fs)
		fclose(fs);
	DEBUG_INIT(false);
	form.progress->setValue(0);
}

void
ccloadView::btnReadLocation_Click()
{
     bool ok;
     unsigned addr;
     unsigned char buffer[16];
     int len;
     addr = form.readLocation->text().toInt(&ok, 0)&0xffff;
     if (!ok)
	 return;
     
     if (!READ_XDATA_MEMORY(addr, sizeof(buffer), &buffer[0], len))
	    return;
     QString res("");
     res.append(QString("%1").arg(addr,4,16,(QChar)'0'));
     res.append(QString(":"));
     for (int i = 0; i < len; i++)
	 res.append(QString(" %1").arg(buffer[i],2,16,(QChar)'0'));
     int p = form.console->textCursor().position();
     form.console->moveCursor(QTextCursor::End, QTextCursor::MoveAnchor);
     form.console->insertPlainText(res);
     form.console->textCursor().setPosition(p);
     addr += sizeof(buffer);
     form.readLocation->setText(QString("0x%1").arg(addr,4,16,(QChar)'0'));
}

void 
ccloadView::btnSetPC_Click()
{
    startPC = form.setPC->text().toInt(&startPCvalid, 0);
}

void
ccloadView::btnGetStatus_Click()
{
	READ_STATUS();
}
void
ccloadView::btnFlashCC_Click()
{
	DEBUG_INIT(false);
//:parseHexByte(QString name, QLineEdit *textBox, unsigned char &value, unsigned char def, bool canEmpty, bool valid)

	bool valid = true;
	unsigned char pxselbits, pxsel, pxbits, px, pxdir;
	valid &= parseHexByte("PxSELBITS",form.pxSelBits, pxselbits, 0, false, valid);
	valid &= parseHexByte("PxSEL", form.pxSel, pxsel, 0, false, valid);
	valid &= parseHexByte("PxBITS", form.pxBits, pxbits, 0, false, valid);
	valid &= parseHexByte("Px", form.px, px, 0, false, valid);
	valid &= parseHexByte("PxDIR", form.pxDir, pxdir, 0, false, valid);
	valid = valid ? DEBUG_INSTR(0x53, pxsel, (unsigned char)(~pxselbits)) : false;
	valid = valid ? DEBUG_INSTR(0x53, px, (unsigned char)(~pxbits)) : false;
	valid = valid ? DEBUG_INSTR(0x43, pxdir, pxbits) : false;
	for (int i = 0; i < 10; i++) {
		if (!valid)
			break;
		valid = valid ? DEBUG_INSTR(0x63, px, pxbits) : false;
		Sleeper::msleep(500);
	}

	DEBUG_INIT(false);
}

void
ccloadView::btnStep_Click()
    {
	DEBUG_INIT(1);
	if (startPCvalid) {
		startPCvalid = 0;
		SET_PC(startPC);
	}
	STEP();
	READ_REGISTERS();
}

void
ccloadView::btnHalt_Click()
{
	DEBUG_INIT(1);
	HALT();
	READ_REGISTERS();
}

void
ccloadView::btnRun_Click()
{
	DEBUG_INIT(1);
	if (startPCvalid) {
		startPCvalid = 0;
		SET_PC(startPC);
	}
	RESUME(1);
	inDebugMode = false;
}
void
ccloadView::btnMACwrite_Click_set()
{
	if (form.writeMAC->isChecked()) {
		form.autoIncMAC->setEnabled(true);
		form.lowMAC->setEnabled(true);
		form.hiMAC->setEnabled(true);
	} else {
		form.autoIncMAC->setEnabled(false);
		form.lowMAC->setEnabled(false);
		form.hiMAC->setEnabled(false);
	}
}
void
ccloadView::btnMACwrite_Click()
{
	btnMACwrite_Click_set();
	settings->setValue("writeMAC", form.writeMAC->isChecked());
	settings->sync();
}
void
ccloadView::btnMACautoInc_Click()
{
	settings->setValue("autoIncMAC", form.autoIncMAC->isChecked());
	settings->sync();
}

void
ccloadView::btnMAClow_Click()
{
	settings->setValue("lowMAC", form.lowMAC->text());
	settings->sync();
}
void
ccloadView::btnMAChi_Click()
{
	settings->setValue("hiMAC", form.hiMAC->text());
	settings->sync();
}
//#include "ccloadview.moc"
