#include "drawit.h"

DrawIt::DrawIt(QWidget *parent)
	: QMainWindow(parent)
{
	QDesktopWidget widget;
	
	QRect mainScreenSize = widget.availableGeometry(widget.primaryScreen());
	width = mainScreenSize.width();
	height = QApplication::desktop()->height();	
	
	drawingBoard = new DrawingBoard(100, 60, width - 200, height - 160, this);

	setupGUI();
	createActions();
	createMenus();

	freehandButton->setChecked(true);
	emptyFillButton->setDown(true);

	setMinimumSize(width, height);
	showMaximized();	
}

DrawIt::~DrawIt()
{
	
}

/*
* Sets up the Graphical user interface
*/
void DrawIt::setupGUI(){
	undoButton = new QToolButton(this);
	undoButton->setGeometry(15, 60, buttonSize, buttonSize);
	undoButton->setIcon(QIcon(":/DrawIt/ic_undo"));
	undoButton->setIconSize(QSize(buttonSize, buttonSize));
	connect(undoButton, SIGNAL(clicked()), this, SLOT(undo()));
	undoButton->setToolTip("Undo the last action");

	redoButton = new QToolButton(this);
	redoButton->setGeometry(55, 60, buttonSize, buttonSize);
	redoButton->setIcon(QIcon(":/DrawIt/ic_redo"));
	redoButton->setIconSize(QSize(buttonSize, buttonSize));
	connect(redoButton, SIGNAL(clicked()), this, SLOT(redo()));
	redoButton->setToolTip("Redo the last action");

	freehandButton = new QToolButton(this);
	freehandButton->setGeometry(15, 100, buttonSize, buttonSize);
	freehandButton->setIcon(QIcon(":/DrawIt/ic_freehand"));
	freehandButton->setIconSize(QSize(buttonSize, buttonSize));
	freehandButton->setCheckable(true);
	freehandButton->setToolTip("Draw a free hand line");

	lineButton = new QToolButton(this);
	lineButton->setGeometry(55, 100, buttonSize, buttonSize);
	lineButton->setIcon(QIcon(":/DrawIt/ic_line"));
	lineButton->setIconSize(QSize(buttonSize, buttonSize));
	lineButton->setCheckable(true);
	lineButton->setToolTip("Draw a straight line");

	circleButton = new QToolButton(this);
	circleButton->setGeometry(15, 140, buttonSize, buttonSize);
	circleButton->setIcon(QIcon(":/DrawIt/ic_circle"));
	circleButton->setIconSize(QSize(buttonSize, buttonSize));
	circleButton->setCheckable(true);
	circleButton->setToolTip("Draw a circle");

	rectangleButton = new QToolButton(this);
	rectangleButton->setGeometry(55, 140, buttonSize, buttonSize);
	rectangleButton->setIcon(QIcon(":/DrawIt/ic_rectangle"));
	rectangleButton->setIconSize(QSize(buttonSize, buttonSize));
	rectangleButton->setCheckable(true);
	rectangleButton->setToolTip("Draw a rectangle");

	QButtonGroup* modeGroup = new QButtonGroup();
	modeGroup->addButton(freehandButton, drawingBoard->modeFreehand);
	modeGroup->addButton(lineButton, drawingBoard->modeLine);
	modeGroup->addButton(circleButton, drawingBoard->modeCircle);
	modeGroup->addButton(rectangleButton, drawingBoard->modeRectangle);
	connect(modeGroup, SIGNAL(buttonClicked(int)), this, SLOT(setDrawingMode(int)));

	primaryColorButton = new QToolButton(this);
	primaryColorButton->setGeometry(100, 25, buttonSize, buttonSize);
	connect(primaryColorButton, SIGNAL(clicked()), this, SLOT(setPrimaryColor()));
	primaryColorButton->setToolTip("Set the primary drawing color");

	secondaryColorButton = new QToolButton(this);
	secondaryColorButton->setGeometry(140, 25, buttonSize, buttonSize);
	connect(secondaryColorButton, SIGNAL(clicked()), this, SLOT(setSecondaryColor()));
	secondaryColorButton->setToolTip("Set the secondary drawing color");

	emptyFillButton = new QToolButton(this);
	emptyFillButton->setGeometry(180, 25, buttonSize, buttonSize);
	emptyFillButton->setIcon(QIcon(":/DrawIt/ic_empty_fill"));
	emptyFillButton->setIconSize(QSize(buttonSize, buttonSize));
	connect(emptyFillButton, SIGNAL(clicked()), this, SLOT(setEmptyFill()));
	emptyFillButton->setToolTip("Turns off the fill function");

	colorFillButton = new QToolButton(this);
	colorFillButton->setGeometry(220, 25, buttonSize, buttonSize);
	connect(colorFillButton, SIGNAL(clicked()), this, SLOT(setColorFill()));
	colorFillButton->setToolTip("Set the fill color");

	QButtonGroup* fillColorGroup = new QButtonGroup();
	fillColorGroup->addButton(emptyFillButton, 0);
	fillColorGroup->addButton(colorFillButton, 1);
	connect(modeGroup, SIGNAL(buttonClicked(int)), this, SLOT(fillbuttonWasClicked(int)));

	penStyleBox = new QComboBox(this);
	penStyleBox->setGeometry(260, 30, 100, 10);
	penStyleBox->setSizeAdjustPolicy(QComboBox::AdjustToContents);
	penStyleBox->addItem(QIcon(":/DrawIt/ic_cb_line"), "Solid Line");
	penStyleBox->addItem(QIcon(":/DrawIt/ic_cb_da_line"), "Dashed Line");
	penStyleBox->addItem(QIcon(":/DrawIt/ic_cb_do_line"), "Dotted Line");
	penStyleBox->addItem(QIcon(":/DrawIt/ic_cb_da_do_line"), "Dashed Dotted Line");
	penStyleBox->setIconSize(QSize(80, 10));
	connect(penStyleBox, SIGNAL(activated(int)), this, SLOT(setPenStyle(int)));
	penStyleBox->setToolTip("Set the pen style");

	penSizeBox = new QComboBox(this);
	penSizeBox->setGeometry(475, 30, 100, 10);
	penSizeBox->setSizeAdjustPolicy(QComboBox::AdjustToContents);
	penSizeBox->addItem(QIcon(":/DrawIt/ic_cb_1"), "1 px");
	penSizeBox->addItem(QIcon(":/DrawIt/ic_cb_2"), "2 px");
	penSizeBox->addItem(QIcon(":/DrawIt/ic_cb_4"), "4 px");
	penSizeBox->addItem(QIcon(":/DrawIt/ic_cb_6"), "6 px");
	penSizeBox->addItem(QIcon(":/DrawIt/ic_cb_8"), "8 px");
	penSizeBox->addItem("Custom");
	penSizeBox->setIconSize(QSize(80, 10));
	connect(penSizeBox, SIGNAL(activated(int)), this, SLOT(setPenWidth(int)));
	penSizeBox->setToolTip("Set the pen size");

	QVariant vColor = drawingBoard->getPrimaryColor();
	QString color = vColor.toString();
	primaryColorButton->setStyleSheet("background-color: " + color);
	vColor = drawingBoard->getSecondaryColor();
	color = vColor.toString();
	secondaryColorButton->setStyleSheet("background-color: " + color);
}

/*
* Create the actions for the toolbar
*/
void DrawIt::createActions()
{
	openAct = new QAction(tr("&Open..."), this);
	openAct->setShortcuts(QKeySequence::Open);
	connect(openAct, SIGNAL(triggered()), this, SLOT(open()));

	foreach(QByteArray format, QImageWriter::supportedImageFormats()) {
		QString text = tr("%1...").arg(QString(format).toUpper());
		QAction *action = new QAction(text, this);
		action->setData(format);
		connect(action, SIGNAL(triggered()), this, SLOT(save()));
		saveAsActs.append(action);
	}

	exitAct = new QAction(tr("E&xit"), this);
	exitAct->setShortcuts(QKeySequence::Quit);
	connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));

	changeBackgroundColorAct = new QAction(tr("Set &Background Color..."), this);
	connect(changeBackgroundColorAct, SIGNAL(triggered()), this, SLOT(setBackgroundColor()));

	clearScreenAct = new QAction(tr("&Clear Screen"), this);
	clearScreenAct->setShortcut(tr("Ctrl+L"));
	connect(clearScreenAct, SIGNAL(triggered()),
		this, SLOT(clearImage()));

	aboutAct = new QAction(tr("&About"), this);
	connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));

	aboutQtAct = new QAction(tr("About &Qt"), this);
	connect(aboutQtAct, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
}

/*
* Create the menus for the toolbar
*/
void DrawIt::createMenus()
{
	saveAsMenu = new QMenu(tr("&Save As"), this);

	foreach(QAction *action, saveAsActs)
		saveAsMenu->addAction(action);

	fileMenu = new QMenu(tr("&File"), this);
	fileMenu->addAction(openAct);
	fileMenu->addMenu(saveAsMenu);
	fileMenu->addSeparator();
	fileMenu->addAction(exitAct);

	optionMenu = new QMenu(tr("&Options"), this);
	optionMenu->addAction(changeBackgroundColorAct);
	optionMenu->addAction(clearScreenAct);

	helpMenu = new QMenu(tr("&Help"), this);
	helpMenu->addAction(aboutAct);
	helpMenu->addAction(aboutQtAct);

	menuBar()->addMenu(fileMenu);
	menuBar()->addMenu(optionMenu);
	menuBar()->addMenu(helpMenu);
}

/*
* Sets the drawing mode. The buttonId values are set in
* the setupGui function
* @param int buttonId - the button id that corresponds to a drawing mode
*/
void DrawIt::setDrawingMode(int buttonId){
	drawingBoard->setPaintMode(buttonId);
}

/*
* Sets the pen style
* @param int index - the index of the option from the combobox penStyleBox
*/
void DrawIt::setPenStyle(int index)
{
	drawingBoard->setPenStyle(index);
}

/*
* Sets the primary color to draw with
*/
void DrawIt::setPrimaryColor()
{
	QColor newColor = QColorDialog::getColor(drawingBoard->getPrimaryColor());
	if (newColor.isValid()){
		drawingBoard->setPrimaryColor(newColor);
		QVariant v = newColor;
		QString color = v.toString();
		primaryColorButton->setStyleSheet("background-color: " + color);
	}
}

/*
* Sets the secondary color to draw with
*/
void DrawIt::setSecondaryColor()
{
	QColor newColor = QColorDialog::getColor(drawingBoard->getSecondaryColor());
	if (newColor.isValid()){
		drawingBoard->setSecondaryColor(newColor);
		QVariant v = newColor;
		QString color = v.toString();
		secondaryColorButton->setStyleSheet("background-color: " + color);
	}
}

/*
* Sets the pen width
* @param int index - the index of the option from the combobox penSizeBox
*/
void DrawIt::setPenWidth(int index)
{
	switch (index){
		case 0:
			drawingBoard->setPenWidth(1);
			break;
		case 1: 
			drawingBoard->setPenWidth(2);
			break;
		case 2:
			drawingBoard->setPenWidth(4);
			break;
		case 3: 
			drawingBoard->setPenWidth(6);
			break;
		case 4: 
			drawingBoard->setPenWidth(8);
			break;
		case 5:
			bool ok;
			int newWidth = QInputDialog::getInt(this, tr("Draw It"),
				tr("Select pen width:"),
				drawingBoard->getPenWidth(),
				1, 50, 1, &ok);
			if (ok){
				drawingBoard->setPenWidth(newWidth);
			}
			break;
	}			
}

/*
* Undo the last action
*/
void DrawIt::undo()
{
	drawingBoard->undo();
}

/*
* Redo the last action
*/
void DrawIt::redo()
{
	drawingBoard->redo();
}

/*
* Sets the fill option to empty
*/
void DrawIt::setEmptyFill()
{
	drawingBoard->setEmptyFill();
	colorFillButton->setStyleSheet("");
	emptyFillButton->setDown(true);
}

/*
* Sets the fill option to the selected color
*/
void DrawIt::setColorFill()
{
	QColor newColor = QColorDialog::getColor(drawingBoard->getFillColor());
	if (newColor.isValid()){
		drawingBoard->setColorFill(newColor);
		QVariant v = newColor;
		QString color = v.toString();
		colorFillButton->setStyleSheet("background-color: " + color);
		emptyFillButton->setDown(false);
	}
}

/*
* Handles the close event so a unsaved image isn't lost
* @param QCloseEvent event - Pointer to the close event
*/
void DrawIt::closeEvent(QCloseEvent *event)
 {
	 if (maybeSave()) {
		 event->accept();
	 }
	 else {
		 event->ignore();
	 }
 }

/*
* Opens a file for editing via file selector dialog
*/
void DrawIt::open()
 {
	 if (maybeSave()) {
		 QString fileName = QFileDialog::getOpenFileName(this,
			 tr("Open File"), QDir::currentPath());
		 if (!fileName.isEmpty()){
			 drawingBoard->openImage(fileName);
		 }		 
	 }
 }

/*
* Saves the image in the choosen format via file selector dialog
*/
void DrawIt::save()
 {
	 QAction *action = qobject_cast<QAction *>(sender());
	 QByteArray fileFormat = action->data().toByteArray();
	 saveFile(fileFormat);
 }

/*
* If the image is edited a dialog will appear to ask if you want to save your changes first.
* @return bool - returns if the action was accepted
*/
bool DrawIt::maybeSave()
{
	if (drawingBoard->isModified()) {
		QMessageBox::StandardButton ret;
		ret = QMessageBox::warning(this, tr("Scribble"),
			tr("The image has been modified.\n"
			"Do you want to save your changes?"),
			QMessageBox::Save | QMessageBox::Discard
			| QMessageBox::Cancel);
		if (ret == QMessageBox::Save) {
			return saveFile("png");
		}
		else if (ret == QMessageBox::Cancel) {
			return false;
		}
	}
	return true;
}

/*
* Saves the image. Separate function from save() so it can be called from maybeSave()
* @return bool - returns if the action succeeded
*/
bool DrawIt::saveFile(const QByteArray &fileFormat)
{
	QString initialPath = QDir::currentPath() + "/untitled." + fileFormat;

	QString fileName = QFileDialog::getSaveFileName(this, tr("Save As"),
		initialPath,
		tr("%1 Files (*.%2);;All Files (*)")
		.arg(QString(fileFormat.toUpper()))
		.arg(QString(fileFormat)));
	if (fileName.isEmpty()) {
		return false;
	}
	else {
		return drawingBoard->saveImage(fileName, fileFormat);
	}
}

/*
* Showes the about dialog
*/
void DrawIt::about()
 {
	 QMessageBox::about(this, tr("About Draw It"),
		 tr("<p>The <b>Draw It</b> app is a drawing application "
		 "with basic drawing functions. Freehand, lines, "
		 "circles and rectangles. The user is able to save and "
		 "load images as well as redo and undo actions. It is based on " 
		 "the QT example scribble."));
 }

/*
* Clears the image and sets the background to the choosen color
*/
void DrawIt::setBackgroundColor(){
	QColor newColor = QColorDialog::getColor(Qt::white);
	if (newColor.isValid()){
		drawingBoard->setBackgroundColor(newColor);
	}
	
}

/*
* Clears the image and sets the background to the choosen color
*/
void DrawIt::clearImage(){
	drawingBoard->setBackgroundColor();
}
