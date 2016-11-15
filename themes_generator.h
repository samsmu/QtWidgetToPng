#pragma once

#include <QWidget>

struct GeneratorParams
{
  QString control;
  QString text;
  QString font;
  QString fontSize;
  QString fileName;
  bool checked;
  QString iconPath;
};

class themes_generator : public QWidget
{
  Q_OBJECT

public:
  themes_generator(const GeneratorParams& params);
  virtual ~themes_generator();

  void generate();
  
private:

  GeneratorParams m_params;
  QWidget* m_testWidget;
};
