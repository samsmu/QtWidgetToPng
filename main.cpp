#include <QApplication>
#include <QCommandLineParser>
#include <QDebug>

#include "themes_generator.h"

int main(int argc, char** argv)
{
  QApplication app(argc, argv);

  app.setApplicationName("themes_generator");
  app.setApplicationVersion("1.0");

  QCommandLineParser parser;
  parser.setApplicationDescription("themes_generator");
  parser.addHelpOption();
  parser.addVersionOption();

  QCommandLineOption controlOption(QStringList() << "c" << "conrol",
    QCoreApplication::translate("main", "Control to generate."),
    QCoreApplication::translate("main", "control"));
  parser.addOption(controlOption);

  QCommandLineOption textOption(QStringList() << "t" << "text",
    QCoreApplication::translate("main", "Text for control to generate."),
    QCoreApplication::translate("main", "text"));
  parser.addOption(textOption);

  /*QCommandLineOption fontOption(QStringList() << "f" << "font",
    QCoreApplication::translate("main", "Set font to use."),
    QCoreApplication::translate("main", "font"));
  parser.addOption(fontOption);*/

  QCommandLineOption fontSizeOption(QStringList() << "s" << "font size",
    QCoreApplication::translate("main", "Set font size to use."),
    QCoreApplication::translate("main", "font size"));
  parser.addOption(fontSizeOption);

  QCommandLineOption fileNameOption(QStringList() << "o" << "Output file name",
    QCoreApplication::translate("main", "Set Output file name to use."),
    QCoreApplication::translate("main", "Output file name"));
  parser.addOption(fileNameOption);

  QCommandLineOption checkedOption(QStringList() << "checked",
    QCoreApplication::translate("main", "Set toolbutton to checked state"));
  parser.addOption(checkedOption);
  
  QCommandLineOption iconOption(QStringList() << "i" << "icon",
    QCoreApplication::translate("main", "Set toolbutton icon to use."),
    QCoreApplication::translate("main", "Set toolbutton icon"));
  parser.addOption(iconOption);

  QCommandLineOption sizeOption(QStringList() << "size" << "size",
    QCoreApplication::translate("main", "Set toolbutton size to use."),
    QCoreApplication::translate("main", "Set toolbutton size"));
  parser.addOption(sizeOption);
  
  QCommandLineOption caseOption(QStringList() << "case",
    QCoreApplication::translate("main", "Set case style"));
  parser.addOption(caseOption);
  
  QCommandLineOption tabActiveOption(QStringList() << "tab_active",
    QCoreApplication::translate("main", "Set tab to active state"));
  parser.addOption(tabActiveOption);
  
  // Process the actual command line arguments given by the user
  parser.process(app);

  GeneratorParams params;

  params.control = parser.value(controlOption);
  params.text = parser.value(textOption);
  //params.font = parser.value(fontOption);
  params.fontSize = parser.value(fontSizeOption);
  params.fileName = parser.value(fileNameOption);
  params.checked = parser.isSet(checkedOption);
  params.iconPath = parser.value(iconOption);
  params.size = parser.value(sizeOption).toInt();
  params.autoplanCase = parser.isSet(caseOption);
  params.tabActive = parser.isSet(tabActiveOption);

  themes_generator themes_generator(params);
  themes_generator.show();

  themes_generator.generate();

  return 0;
}
