#include <QBuffer>
#include <QPushButton>
#include <QToolButton>
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
    
    if (!m_params.text.isEmpty())
    {
      testButton->setText(m_params.text);
    }

    m_testWidget = qobject_cast<QWidget*>(testButton);
  }
  else if (m_params.control == "label")
  {
    QLabel* testLabel = new QLabel(this);

    if (!m_params.text.isEmpty())
    {
      testLabel->setText(m_params.text);
    }

    m_testWidget = qobject_cast<QWidget*>(testLabel);
  }
  else if (m_params.control == "toolbutton")
  {
    QToolButton* testButton = new QToolButton(this);
    testButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    if (!m_params.iconPath.isEmpty())
    {
      testButton->setIcon(QIcon(m_params.iconPath));
    }
    testButton->setCheckable(true);
    testButton->setChecked(m_params.checked);
    
    if (!m_params.text.isEmpty())
    {
      testButton->setText(m_params.text);
    }
    
    m_testWidget = qobject_cast<QWidget*>(testButton);
  }
  
  if (!m_params.fontSize.isEmpty())
  {
    QFont font = m_testWidget->font();
    font.setPixelSize(m_params.fontSize.toInt());
    m_testWidget->setFont(font);
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
  
  if (m_params.control == "button" || m_params.control == "toolbutton")
  {
    QRect rect = pixmap.rect();
    rect.setLeft(rect.left() + 10);
    rect.setRight(rect.right() - 10);
    
    pixmap = pixmap.copy(rect);
  }

  if (m_params.fileName.isEmpty())
  {
    m_params.fileName = m_params.text + ".png";
  }

  pixmap.save(m_params.fileName, "PNG"); // writes pixmap into bytes in PNG format
  close();
}

#include "themes_generator.moc"
