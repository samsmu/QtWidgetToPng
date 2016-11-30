// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include <QBuffer>
#include <QPushButton>
#include <QToolButton>
#include <QLabel>

#include "QArrowTabBar.h"

#include <QDebug>

#include "QtWidgetToPng.h"

QtWidgetToPng::QtWidgetToPng(const GeneratorParams& params) : QWidget()
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
    if (!m_params.checked)
    {
      testButton->setStyleSheet("border:none;");
    }
    
    if (params.size > 0)
    {
      testButton->setFixedHeight(params.size);
      testButton->setFixedWidth(params.size);
      testButton->setIconSize(QSize(params.size, params.size));
    }
    
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
  else if (m_params.control == "arrowtabbar")
  {
    QArrowTabBar* testTabBar = new QArrowTabBar(this);
    testTabBar->addTab("Test 1");
    int tabIndex = testTabBar->addTab(!m_params.text.isEmpty() ? m_params.text : "");
    testTabBar->setTabEnabled(tabIndex, true);
    
    if (params.tabActive)
    {
      testTabBar->setCurrentIndex(tabIndex);
    }
    
    m_testWidget = qobject_cast<QWidget*>(testTabBar);
  }
  
  if (!m_params.fontSize.isEmpty())
  {
    QFont font = m_testWidget->font();
    font.setPixelSize(m_params.fontSize.toInt());
    m_testWidget->setFont(font);
  }
  if (m_params.disabled) m_testWidget->setDisabled(true);
}

QtWidgetToPng::~QtWidgetToPng()
{
}

void QtWidgetToPng::generate()
{
  if (m_testWidget == nullptr)
  {
    return;
  }

  QPixmap pixmap(m_testWidget->size());
  m_testWidget->render(&pixmap);
  
  if ((m_params.control == "button") || (m_params.control == "toolbutton" && !m_params.autoplanCase && m_params.checked))
  {
    QRect rect = pixmap.rect();
    rect.setLeft(rect.left() + 10);
    rect.setRight(rect.right() - 10);
    
    pixmap = pixmap.copy(rect);
  }
    
  if (m_params.control == "arrowtabbar")
  {
    QRect rect = pixmap.rect();
    rect.setLeft(rect.left() + rect.width() / 2 + 20);
    rect.setRight(rect.right() - 20);

    pixmap = pixmap.copy(rect);
  }

  if (m_params.fileName.isEmpty())
  {
    m_params.fileName = m_params.text + ".png";
  }

  pixmap.save(m_params.fileName, "PNG"); // writes pixmap into bytes in PNG format
  close();
}

#include "QtWidgetToPng.moc"
