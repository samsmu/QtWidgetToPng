#ifndef QARROWTABBAR_H
#define QARROWTABBAR_H

#include <QTabBar>
#include <QTemporaryDir>

class QArrowTabBar : public QTabBar
{
  Q_OBJECT

  int borderWidth;
  int borderImageHalfWidth;
  int borderImageHalfHeight;
  int borderImageWidth;
  int borderImageHeight;
  int lastBorderImageWidth;
  QTemporaryDir tempDirectory; // QTemporaryDir will automatically remove the directory during destruction
  QString imagesDirectory;
  void drawPreviousTabPart(QPainter* painter, QColor previousTabColorName);
  void drawNextTabPart(QPainter* painter, QColor nextTabColorName);
  void drawTabLeftBorder(QPainter* painter, QColor borderColor);
  void drawTabRightBorder(QPainter* painter, QColor borderColor);
  void drawLastTabRightBorder(QPainter* painter, QColor borderColor);
  QString getBorderImageFilename(QString imageFileName, QColor previousTabColor, QColor nextTabColor, QColor borderColor);
  QString getLastTabBorderImageFilename(QString imageName, QColor previousTabColor, QColor borderColor);
  void initStyleSheetImages();
public:
  explicit QArrowTabBar(QWidget *parent = 0);
};

#endif // QARROWTABBAR_H