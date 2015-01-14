#ifndef DRAWIT_H
#define DRAWIT_H

#include <QtWidgets/QMainWindow>
#include "drawingboard.h"
#include <QDesktopWidget>
#include <QApplication>
#include <QPushButton>
#include <QToolButton>
#include <QColorDialog>
#include <QInputDialog>
#include <QButtonGroup>
#include <QToolTip>
#include <QComboBox>
#include <QVariant>
#include <QString>
#include <QFileDialog>
#include <QAction>
#include <QMessageBox>
#include <QMenu>
#include <QImageWriter>
#include <QMenuBar>

class DrawIt : public QMainWindow
{
	Q_OBJECT

public:
	DrawIt(QWidget *parent = 0);
	~DrawIt();

private:
	DrawingBoard* drawingBoard;

	int const buttonSize = 30;
	int height;
	int width;

	QToolButton* undoButton;
	QToolButton* redoButton;	
	QToolButton* freehandButton;
	QToolButton* lineButton;
	QToolButton* circleButton;
	QToolButton* rectangleButton;
	QToolButton* primaryColorButton;
	QToolButton* secondaryColorButton;
	QToolButton* emptyFillButton;
	QToolButton* colorFillButton;
	QComboBox* penStyleBox;
	QComboBox* penSizeBox;

	QMenu *saveAsMenu;
	QMenu *fileMenu;
	QMenu *optionMenu;
	QMenu *helpMenu;
	QAction *openAct;
	QList<QAction *> saveAsActs;
	QAction *exitAct;
	QAction *changeBackgroundColorAct;
	QAction *clearScreenAct;
	QAction *aboutAct;
	QAction *aboutQtAct;

	void setupGUI();
	void createActions();
	void createMenus();
	bool maybeSave();
	bool saveFile(const QByteArray &fileFormat);
	void closeEvent(QCloseEvent *event);

public slots:
	void open();
	void save();
	void setBackgroundColor();
	void clearImage();
	void about();
	void setPrimaryColor();
	void setSecondaryColor();
	void setPenWidth(int index);
	void setPenStyle(int index);
	void setEmptyFill();
	void setColorFill();
	void setDrawingMode(int);
	void undo();
	void redo();
};

#endif // DRAWIT_H
