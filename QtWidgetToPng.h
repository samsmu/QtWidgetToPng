#pragma once

#include <QWidget>

struct GeneratorParams
{
  QString control;
  QString text;
  QString font;
  QString fontSize;
  QString fileName;
  QString iconPath;
  int size;
  bool checked;
  bool autoplanCase;
  bool disabled;
  bool tabActive;
};

class QtWidgetToPng : public QWidget
{
  Q_OBJECT

public:
  QtWidgetToPng(const GeneratorParams& params);
  virtual ~QtWidgetToPng();

  void generate();

private:

  GeneratorParams m_params;
  QWidget* m_testWidget;
};
