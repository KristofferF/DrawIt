#ifndef DRAWINGBOARD_H
#define DRAWINGBOARD_H

#include <QMouseEvent>
#include <QPainter>
#include <QWidget>
#include <QColor>
#include <QImage>
#include <QLineEdit>
#include <QtWidgets/QMainWindow>

class DrawingBoard : public QWidget
{
	Q_OBJECT

public:
	DrawingBoard(int posX, int posY, int width, int height, QWidget *parent = 0);
	~DrawingBoard();	
	void setPrimaryColor(const QColor &newColor);
	void setSecondaryColor(const QColor &newColor);
	void setPenWidth(int newWidth);
	void setPenStyle(int newPenStyle);
	void setColorFill(const QColor &newColor);
	void setEmptyFill();
	void setBackgroundColor(const QColor &newColor = Qt::white);
	QColor getPrimaryColor();
	QColor getSecondaryColor();
	QColor getFillColor();
	int getPenWidth();
	void undo();
	void redo();	
	void setPaintMode(int newPaintMode);
	bool openImage(const QString &fileName);
	bool saveImage(const QString &fileName, const char *fileFormat);
	bool isModified();
	
	
	//Sets the modes to constant numbers. Public to be reachable from the DrawIt class
	static const int modeFreehand = 0;
	static const int modeLine = 1;
	static const int modeCircle = 2;
	static const int modeRectangle = 3;

	static const int styleSolidLine = 0;
	static const int styleDashedLine = 1;
	static const int styleDottedLine = 2;	
	static const int styleDashedDottedLine = 3;
	
public slots:
	void mousePressEvent(QMouseEvent* event);
	void mouseMoveEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
	void paintEvent(QPaintEvent * event);
	void Draw(QMouseEvent *event);
	
private:	
	int paintMode;
	bool modified;
	bool undoing;
	bool scribbling;
	bool fill;
	int penWidth;
	QColor penColor;
	QColor primaryColor;
	QColor secondaryColor;
	QColor fillColor;
	Qt::PenStyle penStyle;
	QImage tempImage;
	QImage currentImage[10];
	int undoImageCounter;
	int currentImageCounter;
	QPoint lastPoint;
	QPoint startPoint;

	void drawFreehand(const QPoint &endPoint);
	void drawShape(const QPoint &endPoint, int mode);
	double calculateHypotenuse(const QPoint &endPoint);
	QPointF calculateMiddlePoint(const QPoint &endPoint);
	void checkImageCount();
	void rearrangeImages();
	void resizeImage(QImage *image, const QSize &newSize);	
};

#endif // DRAWINGBOARD_H