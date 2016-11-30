// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include <QDir>
#include <QPixmap>
#include <QPainter>

#include "QArrowTabBar.h"

QArrowTabBar::QArrowTabBar(QWidget* parent) :
  QTabBar(parent),
  tempDirectory()
{
  setDrawBase(false);
  borderWidth = 7; // must be odd number
  borderImageHeight = 35; // must be odd number
  borderImageHalfHeight = borderImageHeight / 2;
  borderImageWidth = borderImageHalfHeight + borderWidth;
  borderImageHalfWidth = borderImageWidth / 2;
  lastBorderImageWidth = borderImageHalfWidth + borderImageHalfHeight;

  if (tempDirectory.isValid()) {
    imagesDirectory = tempDirectory.path();
    initStyleSheetImages();
  }
}

void QArrowTabBar::drawPreviousTabPart(QPainter* painter, const QColor &previousTabColor)
{
  painter->setPen(QPen(previousTabColor));
  int leftTopStartY = borderImageHalfHeight - borderImageHalfWidth + 1;
  int leftBottomStartY = borderImageHalfHeight + borderImageHalfWidth;
  int leftEndX = borderImageHalfWidth - 1;
  int leftEndY = borderImageHeight - borderImageHalfHeight;
  for (int i = borderWidth; i < borderImageHalfWidth; ++i) {
    painter->drawLine(0, leftTopStartY + i, leftEndX - i, borderImageHalfHeight);
    painter->drawLine(0, leftBottomStartY - i, leftEndX - i, leftEndY);
  }
}

void QArrowTabBar::drawNextTabPart(QPainter* painter, const QColor &nextTabColor)
{
  painter->setPen(QPen(nextTabColor));
  int rightEndY = borderImageHeight - borderImageHalfWidth;
  for (int i = borderWidth; i < borderImageHalfWidth; ++i) {
    painter->drawLine(borderImageHalfWidth + i, 0, borderImageWidth, borderImageHalfWidth - i);
    painter->drawLine(borderImageHalfWidth + i, borderImageHeight, borderImageWidth, rightEndY + i);
  }
}

void QArrowTabBar::drawTabLeftBorder(QPainter* painter, const QColor &backgroundColor)
{
  // Setting pen width does not work in our case because pen join style is not flexible enought
  // to achieve sharp 90 degree corners. We have to draw border line-by-line to achieve that.
  painter->setPen(QPen(backgroundColor));
  int leftTopStartY = borderImageHalfHeight - borderImageHalfWidth + 1;
  int leftBottomStartY = borderImageHalfHeight + borderImageHalfWidth;
  int leftEndX = borderImageHalfWidth - 1;
  int leftEndY = borderImageHeight - borderImageHalfHeight;
  for (int i = 0; i < borderWidth; ++i) {
    painter->drawLine(0, leftTopStartY + i, leftEndX - i, borderImageHalfHeight);
    painter->drawLine(0, leftBottomStartY - i, leftEndX - i, leftEndY);
  }
}

void QArrowTabBar::drawTabRightBorder(QPainter* painter, const QColor &borderColor)
{
  painter->setPen(QPen(borderColor));
  int rightEndY = borderImageHeight - borderImageHalfWidth;
  for (int i = 0; i < borderWidth; ++i) {
    painter->drawLine(borderImageHalfWidth + i, 0, borderImageWidth, borderImageHalfWidth - i);
    painter->drawLine(borderImageHalfWidth + i, borderImageHeight, borderImageWidth, rightEndY + i);
  }
}

void QArrowTabBar::drawLastTabRightBorder(QPainter* painter, const QColor &borderColor)
{
  painter->setPen(QPen(borderColor));
  int endY = borderImageHeight - borderImageHalfHeight;
  for (int i = 0; i < borderImageHalfHeight; ++i) {
    painter->drawLine(borderImageHalfWidth + i, 0, lastBorderImageWidth + i, borderImageHalfHeight);
    painter->drawLine(borderImageHalfWidth + i, borderImageHeight, lastBorderImageWidth + i, endY);
  }
}

QString QArrowTabBar::getBorderImageFilename
  ( QString imageName
  , const QColor &previousTabColor
  , const QColor &nextTabColor
  , const QColor &borderColor)
{
  QPixmap pixmap(borderImageWidth, borderImageHeight);
  pixmap.fill(Qt::transparent);
  QPainter painter(&pixmap);

  drawTabLeftBorder(&painter, borderColor);
  drawTabRightBorder(&painter, borderColor);
  drawPreviousTabPart(&painter, previousTabColor);
  drawNextTabPart(&painter, nextTabColor);

  QString imageFileName = QDir(imagesDirectory).filePath(imageName + ".png");
  pixmap.save(imageFileName);
  return imageFileName;
}

QString QArrowTabBar::getLastTabBorderImageFilename(QString imageName, const QColor &previousTabColor, const QColor &borderColor)
{
  QPixmap pixmap(lastBorderImageWidth, borderImageHeight);
  pixmap.fill(Qt::transparent);
  QPainter painter(&pixmap);

  drawTabLeftBorder(&painter, borderColor);
  drawLastTabRightBorder(&painter, borderColor);
  drawPreviousTabPart(&painter, previousTabColor);

  QString imageFileName = QDir(imagesDirectory).filePath(imageName + ".png");
  pixmap.save(imageFileName);
  return imageFileName;
}

void QArrowTabBar::initStyleSheetImages()
{
  QDir().mkpath(imagesDirectory);
  QPalette currentPalette = palette();
  QColor baseColor = currentPalette.color(QPalette::Active, QPalette::Button);
  QColor activeBackgroundColor = currentPalette.color(QPalette::Active, QPalette::Window);
  QColor inactiveBackgroundColor = currentPalette.color(QPalette::Inactive, QPalette::Window);
  QColor tabTextColor;
  QColor tabColor;
  QColor tabColorSelected;
  QColor tabTextColorDisabled;
  if (baseColor.value() < 128) { // dark theme
    tabColor = baseColor.lighter(140);
    tabColorSelected = baseColor.lighter(185);
    tabTextColor = currentPalette.color(QPalette::Active, QPalette::ButtonText);
  } else { // light theme
    tabColor = baseColor.darker(140);
    tabColorSelected = baseColor.darker(185);
    tabTextColor = currentPalette.color(QPalette::Active, QPalette::BrightText);
  }
  tabTextColorDisabled = tabColor.darker(185);
  QColor tabTextColorSelected = tabTextColor;

  setStyleSheet(QString(
    "QTabBar { outline: none; } "
    "QTabBar::tab { background: [tab-color]; color: [tab-text-color]; padding-top: 10px; padding-bottom: 10px; padding-left: 5px; min-width: 150px; border-image: url([tab-border]) 0 [borderWidth/2] 0 [borderWidth/2]; } "
    "QTabBar::tab:middle { border-width: 0 [borderWidth/2]px 0 [borderWidth/2]px; } "
    "QTabBar::tab:first { border-width: 0 [borderWidth/2]px 0 0; } "
    "QTabBar::tab:last { border-image: url([tab-border-last]); border-width: 0 [lastBorderWidth]px 0 [borderWidth/2]px; } "
    "QTabBar::tab:last:previous-selected { border-image: url([tab-border-last-previous-selected]); border-width: 0 [lastBorderWidth]px 0 [borderWidth/2]px; } "
    "QTabBar::tab:selected { background: [tab-color-selected]; } "
    "QTabBar::tab:previous-selected { border-image: url([tab-border-previous-selected]) 0 [borderWidth/2] 0 [borderWidth/2]; } "
    "QTabBar::tab:next-selected { border-image: url([tab-border-next-selected]) 0 [borderWidth/2] 0 [borderWidth/2]; } "
    "QTabBar::tab:!active { border-image: url([tab-border-inactive]) 0 [borderWidth/2] 0 [borderWidth/2]; } "
    "QTabBar::tab:!active:last { border-image: url([tab-border-inactive-last]); } "
    "QTabBar::tab:!active:last:previous-selected { border-image: url([tab-border-inactive-last-previous-selected]); } "
    "QTabBar::tab:!active:previous-selected { border-image: url([tab-border-inactive-previous-selected]) 0 [borderWidth/2] 0 [borderWidth/2]; } "
    "QTabBar::tab:!active:next-selected { border-image: url([tab-border-inactive-next-selected]) 0 [borderWidth/2] 0 [borderWidth/2]; } "
    "QTabBar::tab:disabled { color: [tab-text-color-disabled]; } "
    "QTabBar QToolButton { background: [tab-color]; border: 1px solid palette(window); border-radius: 1px; } "
    "QTabBar QToolButton::left-arrow { color: [tab-color]; } "
    "QTabBar QToolButton::right-arrow { color: [tab-color]; } "
  ).replace("[tab-color]", tabColor.name())
   .replace("[tab-text-color]", tabTextColor.name())
   .replace("[tab-color-selected]", tabColorSelected.name())
   .replace("[tab-text-color-selected]", tabTextColorSelected.name())
   .replace("[tab-text-color-disabled]", tabTextColorDisabled.name())
   .replace("[tab-border]", getBorderImageFilename("tab-border", tabColor, tabColor, activeBackgroundColor))
   .replace("[tab-border-previous-selected]", getBorderImageFilename("tab-border-previous-selected", tabColorSelected, tabColor, activeBackgroundColor))
   .replace("[tab-border-next-selected]", getBorderImageFilename("tab-border-next-selected", tabColor, tabColorSelected, activeBackgroundColor))
   .replace("[tab-border-last]", getLastTabBorderImageFilename("tab-border-last", tabColor, activeBackgroundColor))
   .replace("[tab-border-last-previous-selected]", getLastTabBorderImageFilename("tab-border-last-previous-selected", tabColorSelected, activeBackgroundColor))
   .replace("[tab-border-inactive]", getBorderImageFilename("tab-border-inactive", tabColor, tabColor, inactiveBackgroundColor))
   .replace("[tab-border-inactive-previous-selected]", getBorderImageFilename("tab-border-inactive-previous-selected", tabColorSelected, tabColor, inactiveBackgroundColor))
   .replace("[tab-border-inactive-next-selected]", getBorderImageFilename("tab-border-inactive-next-selected", tabColor, tabColorSelected, inactiveBackgroundColor))
   .replace("[tab-border-inactive-last]", getLastTabBorderImageFilename("tab-border-inactive-last", tabColor, inactiveBackgroundColor))
   .replace("[tab-border-inactive-last-previous-selected]", getLastTabBorderImageFilename("tab-border-inactive-last-previous-selected", tabColorSelected, inactiveBackgroundColor))
   .replace("[borderWidth/2]", QString::number(borderImageHalfWidth))
   .replace("[lastBorderWidth]", QString::number(borderImageHalfHeight))
  );
}
