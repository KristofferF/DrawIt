#include "drawingboard.h"

DrawingBoard::DrawingBoard(int posX, int posY, int width, int height, QWidget *parent)
	: QWidget(parent)
{
	setGeometry(posX, posY, width, height);

	modified = false;
	scribbling = false;
	fill = false;
	
	undoImageCounter = 0;
	currentImageCounter = 0;
	penWidth = 1;
	primaryColor = Qt::black;
	secondaryColor = Qt::white;
	penColor = primaryColor;
	penStyle = Qt::SolidLine;
	paintMode = modeFreehand;

	

	currentImage[0] = QImage(QSize(width, height), QImage::Format_RGB32);
	currentImage[0].fill(qRgb(255, 255, 255));

	tempImage = QImage(QSize(width, height), QImage::Format_ARGB32);
	tempImage.fill(qRgba(0, 0, 0, 0));

	setCursor(Qt::CrossCursor);
}

DrawingBoard::~DrawingBoard()
{

}

/**
* Sets the primary color thats being used when the left mouse button is hold down
* @param Qcolor newColor - Color to use
*/
void DrawingBoard::setPrimaryColor(const QColor &newColor)
{
	primaryColor = newColor;
}

/**
* Sets the secondary color thats being used when the right mouse button is hold down
* @param Qcolor newColor - Color to use
*/
void DrawingBoard::setSecondaryColor(const QColor &newColor)
{
	secondaryColor = newColor;
}

/**
* Sets the width of the pen
* @param int newWidth - The new width of the pen
*/
void DrawingBoard::setPenWidth(int newWidth)
{
	penWidth = newWidth;
}

/**
* Turns on and sets the color to use to fill shapes
* @param Qcolor newColor - Color to use
*/
void DrawingBoard::setColorFill(const QColor &newColor)
{
	fillColor = newColor;
	fill = true;
}

/**
* Turns off the fill option
*/
void DrawingBoard::setEmptyFill()
{
	fill = false;
}

/**
* Clears the image
*/
void DrawingBoard::setBackgroundColor(const QColor &newColor)
{
	checkImageCount();
	tempImage.fill(qRgba(0, 0, 0, 0));
	currentImage[currentImageCounter].fill(newColor);
	update();
	modified = true;
}

/**
* Returns the primary color
* @return QColor - The primary color
*/
QColor DrawingBoard::getPrimaryColor(){
	return primaryColor;
}

/**
* Returns the secondary color
* @return QColor - The secondary color
*/
QColor DrawingBoard::getSecondaryColor(){
	return secondaryColor;
}

/**
* Returns the fill color
* @return QColor - The fill color
*/
QColor DrawingBoard::getFillColor(){
	return fillColor;
}

/**
* Returns the pen width
* @return int - The pen width
*/
int DrawingBoard::getPenWidth(){
	return penWidth;
}

/**
* @Override
* Is called when update() is used
* @param QPaintEvent* event - Pointer to QPaintEvent
*/
void DrawingBoard::paintEvent(QPaintEvent *event){
	QPainter painter(this);
	QRect dirtyRect = event->rect();
	painter.drawImage(dirtyRect, currentImage[currentImageCounter], dirtyRect);
	painter.drawImage(dirtyRect, tempImage, dirtyRect);
}

/**
* Handles mouseclicks
* @param QMouseEvent* event - Pointer to QMouseEvent
*/
void DrawingBoard::mousePressEvent(QMouseEvent* event){
	checkImageCount();
	if (event->button() == Qt::LeftButton) {
		penColor = primaryColor;
		lastPoint = event->pos();
		startPoint = event->pos();
		scribbling = true;
	}
	else if (event->button() == Qt::RightButton){
		penColor = secondaryColor;
		lastPoint = event->pos();
		startPoint = event->pos();
		scribbling = true;
	}
}

/**
* Handles mousemovements
* @param QMouseEvent* event - Pointer to QMouseEvent
*/
void DrawingBoard::mouseMoveEvent(QMouseEvent *event)
{
	if ((event->buttons() & Qt::LeftButton) && scribbling){
		Draw(event);
	}
	else if ((event->buttons() & Qt::RightButton) && scribbling){
		Draw(event);
	}
}

/**
* Handles mouseclick releases
* @param QMouseEvent* event - Pointer to QMouseEvent
*/
void DrawingBoard::mouseReleaseEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton && scribbling) {
		scribbling = false;
		Draw(event);
	}
	else if (event->button() == Qt::RightButton && scribbling) {
		scribbling = false;
		Draw(event);
	}
	modified = true;
}

/**
* Check the image count if the array of undo images is full rearrange them
* Otherwise create a new one
*/
void DrawingBoard::checkImageCount(){
	undoImageCounter = 0;
	undoing = false;
	if (currentImageCounter < 9){
		currentImage[currentImageCounter + 1] = currentImage[currentImageCounter];
		++currentImageCounter;
	}
	else{
		rearrangeImages();
	}
}

/**
* Rearrange the array of images that is used for the undo and redo function
*/
void DrawingBoard::rearrangeImages(){
	for (int i = 0; i < currentImageCounter; ++i){
		currentImage[i] = currentImage[i + 1];
	}
}

/**
* Set and call the relevant drawing mode
* @param QMouseEvent* event - Pointer to QMouseEvent
*/
void DrawingBoard::Draw(QMouseEvent *event){
	switch (paintMode){
		case modeFreehand:
			drawFreehand(event->pos());
			break;
		case modeLine:
			drawShape(event->pos(), modeLine);
			break;
		case modeCircle:
			drawShape(event->pos(), modeCircle);
			break;
		case modeRectangle:
			drawShape(event->pos(), modeRectangle);
			break;
	}
}

/**
* Draws the freehand line
* @param QPoint endPoint - endpoint to draw to
*/
void DrawingBoard::drawFreehand(const QPoint &endPoint)
{
	QPainter painter(&currentImage[currentImageCounter]);
	painter.setPen(QPen(penColor, penWidth, Qt::SolidLine, Qt::RoundCap,
		Qt::RoundJoin));
	painter.drawLine(lastPoint, endPoint);

	int rad = (penWidth / 2) + 2;
	update(QRect(lastPoint, endPoint).normalized()
		.adjusted(-rad, -rad, +rad, +rad));
	lastPoint = endPoint;
}

/**
* Draws the selected shape
* @param QPoint endPoint - endpoint to draw to
* @param int mode - drawing mode to use
*/
void DrawingBoard::drawShape(const QPoint &endPoint, int mode){
	QPainter painter;
	if (scribbling){
		tempImage.fill(qRgba(0, 0, 0, 0));
		update();
		painter.begin(&tempImage);
	}
	else{
		painter.begin(&currentImage[currentImageCounter]);
	}
	if (fill){
		painter.setBrush(QBrush(fillColor, Qt::SolidPattern));
	}	
	painter.setPen(QPen(penColor, penWidth, penStyle, Qt::RoundCap,
		Qt::RoundJoin));
	double const hypotenuse = calculateHypotenuse(endPoint);
	QPointF const middlePoint = calculateMiddlePoint(endPoint);
	int const rad = (penWidth / 2) + 2;
	switch (paintMode){
		case modeLine:
			painter.drawLine(startPoint, endPoint);
			break;
		case modeCircle:
			painter.drawEllipse(middlePoint, hypotenuse / 2, hypotenuse / 2);		
			break;
		case modeRectangle:		
			painter.drawRect(startPoint.x(), startPoint.y(), endPoint.x() - startPoint.x(), endPoint.y() - startPoint.y());
			break;
	}
	update(QRect(startPoint, endPoint).normalized()
		.adjusted(-rad, -rad, +rad, +rad));
}

/**
* Calculates the hypotenuse of the triangle thats is made up of the 
startingpoint, the endpoint and the delta distance in the y direction.
Used to get the length between the start and endpoint
* @param QPoint endPoint - endpoint to calculate distance with
*/
double DrawingBoard::calculateHypotenuse(const QPoint &endPoint){	
	const double x = abs(endPoint.x() - startPoint.x());
	const double y = abs(endPoint.y() - startPoint.y());
	return hypot(x, y);
}

/**
* Calculates the middlepoint between the start and the endpoint
* @param QPoint endPoint - endpoint to calculate distance with
*/
QPointF DrawingBoard::calculateMiddlePoint(const QPoint &endPoint){
	const double x = (double)(endPoint.x() + startPoint.x()) / 2;
	const double y = (double)(endPoint.y() + startPoint.y()) / 2;
	const QPointF middlePoint(x, y);
	return middlePoint;
}
 
/**
* Undo the last action
*/
void DrawingBoard::undo(){
	if (!undoing){
		undoImageCounter = currentImageCounter;
		undoing = true;
	}
	if (currentImageCounter > 0){		
		--currentImageCounter;
		tempImage.fill(qRgba(0, 0, 0, 0));
		update();
		
	}	
}

/**
* Redo the last action
*/
void DrawingBoard::redo(){
	if (currentImageCounter < undoImageCounter){
		++currentImageCounter;
		update();	
	}
}

/**
* Sets the new paint mode
* @param int newPaintMode - The new paint mode
*/
void DrawingBoard::setPaintMode(int newPaintMode){
	paintMode = newPaintMode;
}

/**
* Sets the pen style to draw with
* @param int newPenStyle - The new pen style
*/
void DrawingBoard::setPenStyle(int newPenStyle){
	
	switch (newPenStyle){
		case styleSolidLine:
			penStyle = Qt::SolidLine;
			break;
		case styleDashedLine:
			penStyle = Qt::DashLine;
			break;
		case styleDottedLine:
			penStyle = Qt::DotLine;
			break;
		case styleDashedDottedLine:
			penStyle = Qt::DashDotLine;
			break;
	}
}

/**
* Resizes the given image to the given size
* @param QImage* image - The image to be resized
* @param Qsize* newSize - The size to set the image to
*/
void DrawingBoard::resizeImage(QImage *image, const QSize &newSize)
{
	if (image->size() == newSize)
	return;

	QImage newImage(newSize, QImage::Format_RGB32);
	newImage.fill(qRgb(255, 255, 255));
	QPainter painter(&newImage);
	painter.drawImage(QPoint(0, 0), *image);
	*image = newImage;
}

/**
* Opens the image file
* @param QString fileName - The image filename to be loaded
* @return bool - if the load succeeded
*/
bool DrawingBoard::openImage(const QString &fileName)
{
	QImage loadedImage;
	if (!loadedImage.load(fileName)){
		return false;
	}	
	QSize newSize = loadedImage.size().expandedTo(size());
	resizeImage(&loadedImage, newSize);
	currentImageCounter = 0;
	currentImage[currentImageCounter] = loadedImage;
	modified = false;
	update();
	return true;
}

/**
* Saves the image file
* @param QString fileName - The image filename to be loaded
* @return bool - if the save succeeded
*/
bool DrawingBoard::saveImage(const QString &fileName, const char *fileFormat)
{
	QImage visibleImage = currentImage[currentImageCounter];

	if (visibleImage.save(fileName, fileFormat)) {
		modified = false;
		return true;
	}
	else {
		return false;
	}
}

/**
* Checks if the image is modified since the last save
* @return bool - true if changed
*/
bool DrawingBoard::isModified(){
	return modified;
}