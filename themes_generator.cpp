#include <QBuffer>
#include <QPushButton>
#include <QLabel>

#include <QDebug>

#include "themes_generator.h"

themes_generator::themes_generator(const GeneratorParams& params) : QWidget()
{
  m_testWidget = nullptr;
  setMinimumSize(640, 480);

  m_params = params;

  if (m_params.control == "button")
  {
    QPushButton* testButton = new QPushButton(this);
    testButton->setStyleSheet("border:none;");

    if (!m_params.fontSize.isEmpty())
    {
      QFont font = testButton->font();
      font.setPixelSize(m_params.fontSize.toInt());
      testButton->setFont(font);
    }

    if (!m_params.text.isEmpty())
    {
      testButton->setText(m_params.text);
    }

    m_testWidget = qobject_cast<QWidget*>(testButton);
  }
  else if (m_params.control == "label")
  {
    QLabel* testLabel = new QLabel(this);

    if (!m_params.fontSize.isEmpty())
    {
      QFont font = testLabel->font();
      font.setPixelSize(m_params.fontSize.toInt());
      testLabel->setFont(font);
    }

    if (!m_params.text.isEmpty())
    {
      testLabel->setText(m_params.text);
    }

    m_testWidget = qobject_cast<QWidget*>(testLabel);
  }
}

themes_generator::~themes_generator()
{
}

void themes_generator::generate()
{
  if (m_testWidget == nullptr)
  {
    return;
  }

  QPixmap pixmap(m_testWidget->size());
  m_testWidget->render(&pixmap);

  if (m_params.fileName.isEmpty())
  {
    m_params.fileName = m_params.text + ".png";
  }

  pixmap.save(m_params.fileName, "PNG"); // writes pixmap into bytes in PNG format
  close();
}

#include "themes_generator.moc"
