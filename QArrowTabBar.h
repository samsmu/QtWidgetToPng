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
  void drawPreviousTabPart(QPainter* painter, const QColor &previousTabColor);
  void drawNextTabPart(QPainter* painter, const QColor &nextTabColor);
  void drawTabLeftBorder(QPainter* painter, const QColor &backgroundColor);
  void drawTabRightBorder(QPainter* painter, const QColor &borderColor);
  void drawLastTabRightBorder(QPainter* painter, const QColor &borderColor);
  QString getBorderImageFilename
    ( QString imageName
    , const QColor &previousTabColor
    , const QColor &nextTabColor
    , const QColor &borderColor);
  QString getLastTabBorderImageFilename(QString imageName, const QColor &previousTabColor, const QColor &borderColor);
  void initStyleSheetImages();
public:
  explicit QArrowTabBar(QWidget *parent = 0);
};

#endif // QARROWTABBAR_H
