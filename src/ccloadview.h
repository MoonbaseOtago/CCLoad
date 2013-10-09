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

#ifndef CCLOADVIEW_H
#define CCLOADVIEW_H

#include <QtGui/QWidget>
#include <QSettings>
#include "ttylock.h"
#include "mythread.h"

#include "ui_ccloadview_base.h"

class QPainter;
class KUrl;

/**
 * This is the main view class for ccload.  Most of the non-menu,
 * non-toolbar, and non-statusbar (e.g., non frame) GUI code should go
 * here.
 *
 * @short Main view
 * @author %{AUTHOR} <%{EMAIL}>
 * @version %{VERSION}
 */

#include "mythread.h"

class MyThread;


//class ccloadView : public QWidget, public Ui::Form
class ccloadView : public QWidget
{
    Q_OBJECT
public:
    /**
     * Default constructor
     */
    ccloadView(QWidget *parent);

    /**
     * Destructor
     */
    virtual ~ccloadView();

    int port;
    Ui::Form form;
    void setIdleTimer();

private:

	static const unsigned char SEL_FLASH_INFO = 0x01;
	static const unsigned char CHIP_ERASE_DONE = 0x80;
	static const unsigned char PCON_IDLE = 0x40;
	static const unsigned char CPU_HALTED = 0x20;
	static const unsigned char POWER_MODE_0 = 0x10;
	static const unsigned char HALT_STATUS = 0x08;
	static const unsigned char DEBUG_LOCKED = 0x04;
	static const unsigned char OSCILATOR_STABLE = 0x02;
	static const unsigned char STACK_OVERFLOW = 0x01;

	// Chip Name, FlashSize, FlashPageSize, FlashWordSize
	static char *ChipDescriptors[];

	bool waiting;
	bool chipDefined;
	bool inDebugMode;

	long FLASH_SIZE;
	int FLASH_PAGE_SIZE;
	int FLASH_WORD_SIZE;
	MyThread *thread;
	int maddr;
	unsigned char image[0x10000];
	int app_mstart;
	int app_msize;
	unsigned char app_image[0x10000];

private:
	QString prepareCommand(QString cmd);
	QString sendCommand(QString command, QString msg);
	bool parseOK(QString response);
	QString getTokenREAD(QString response);
	QString getToken(QString token, QString response);
	bool getDataByte(int index, QString data, unsigned char &value);
	bool getDataByte(int index, QString data);
	bool isPageEmpty(unsigned char *buffer);
	void loadChipModel(QString items);
	void addRoutine(unsigned char *routine, int &rlen, unsigned char in0);
	void addRoutine(unsigned char *routine, int &rlen, unsigned char in0, unsigned char in1);
	void addRoutine(unsigned char *routine, int &rlen, unsigned char in0, unsigned char in1, unsigned char in2);
	bool parseHexByte(QString s, QLineEdit *textBox, unsigned char &value, unsigned char def, bool canEmpty, bool valid);
	void setStatusLED(int state, QCheckBox *led);
	void setStatusLabels(int status);
	void setConfigLabels(int config);
	void setConnected();
	void setDisconnected();
	void btnMACwrite_Click_set();
	bool DEBUG_INIT();
	bool DEBUG_INIT(bool soft);
	void set_REGISTER(QLabel *, int v);
	bool READ_REGISTERS();
	bool READ_STATUS();
	bool READ_STATUS(unsigned char &status);
	bool RESET(bool state);
	bool LED(bool state);
	bool FLASHDC(bool state);
	bool FLASHDD(bool state);
	bool FLASHRST(bool state);
	bool READ_CONFIG();
	bool dbg_ReadConfig(unsigned char &config);
	bool WRITE_CONFIG(unsigned char config);
	bool GET_CHIP_ID();
	bool GET_CHIP_ID(unsigned char &id, unsigned char &revision);
	bool HALT();
	bool RESUME(bool run);
	bool STEP();
	bool MASS_ERASE_FLASH();
	bool CHIP_ERASE();
	bool DEBUG_INSTR(unsigned char in0);
	bool DEBUG_INSTR(unsigned char in0, unsigned char *data);
	bool DEBUG_INSTR(unsigned char in0, unsigned char in1, unsigned char *data);
	bool DEBUG_INSTR(unsigned char in0, unsigned char in1);
	bool DEBUG_INSTR(unsigned char in0, unsigned char in1, unsigned char in2, unsigned char *data);
	bool DEBUG_INSTR(unsigned char in0, unsigned char in1, unsigned char in2);
	bool dbg_DebugInstr(unsigned char *cmds, int len, unsigned char *data);
	bool CLOCK_INIT();
	bool WRITE_XDATA_MEMORY(int address, unsigned char *buffer, int length);
	bool READ_XDATA_MEMORY(int address, int length, unsigned char *buffer, int &outlen);
	bool READ_CODE_MEMORY(int address, unsigned char bank, int length, unsigned char *buffer, int &outlen);
	bool SET_PC(int address);
	bool GET_PC(int &address);
	bool WRITE_PAGE_FLASH(long iPageAddress, unsigned char *buffer, int length, bool erasePage);
	bool READ_FLASH_PAGE(long iPageAddress, int length, unsigned char *code, int &clen);
	bool Connect();
	bool set_INSTR(QLabel *lp, unsigned char in0);
	bool set_INSTR(QLabel *lp, unsigned char in0, unsigned char in1);
	bool set_INSTR(QLabel *lp, unsigned char in0, unsigned char in1, unsigned char in2);
	bool CLIENT(bool state);
	
	ttylock *lock;
	bool prod;
	QSettings *settings;
	bool startPCvalid;
	int startPC;
	bool connected;
	void consoleDisplay(QString &s);
	

signals:
	void startupclick();
private slots:
	void btnFlashDD_Click();
	void btnFlashDC_Click();
	void btnFlashRST_Click();
	void btnConnect_Click();
	void cbChipModel_SelectedIndexChanged(int);
	void btnSelectFile_Click();
	void btnSelectFile_App_Click();
	void btnWrite_Click();
	void btnWrite_App_Click();
	void btnDebug_Click();
	void btnProduction_Click();
	void btnRead_Click();
	void btnRead_App_Click();
	void btnGetStatus_Click();
	void btnFlashCC_Click();
	void btnRun_Click();
	void btnStep_Click();
	void btnHalt_Click();
	void btnSelectLoad_Click();
	void btnSelectLoad_App_Click();
	void btnAuto_Click();
	void btnVerify_Click();
	void btnVerify_App_Click();
	void btnErasePage_Click();
	void btnErasePage_App_Click();
	void btnErase_Click();
	void btnReadLocation_Click();
	void btnSetPC_Click();
	void btnMACwrite_Click();
	void btnMACautoInc_Click();
	void btnMAClow_Click();
	void btnMAChi_Click();
	void idle();
};

#endif // ccloadVIEW_H
