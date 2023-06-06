#include <QtPlugin>

#include "../IconEditor/iconeditor.h"
#include "iconeditorplugin.h"

IconEditorPlugin::IconEditorPlugin(QObject *parent)
    : QObject(parent)
{
}

QString IconEditorPlugin::name() const//возвращает имя покдлючаемого виджета
{
    return "IconEditor";
}

QString IconEditorPlugin::includeFile() const//возвращает имя заголовочного файла для заданного виджета, который инкапсулирован в подключаемом модуле
{
    return "iconeditor.h";
}

QString IconEditorPlugin::group() const//возвращает имя группы на панели виджетов, к которой принадлежит пользовательский виджет
{
    return tr("Image Manipulation Widgets");
}

QIcon IconEditorPlugin::icon() const//возвращает пиктограмму,которая будет использоваться для представления пользоватльского виджета на панели виджетов (получаем из ресурсного файла)
{
    return QIcon(":/images/iconeditor.png");
}

QString IconEditorPlugin::toolTip() const//возвращает всплывающую подсказку которая появляется когда мышка находится над пользовательским виджетом в панели виджетов
{
    return tr("An icon editor widget");
}

QString IconEditorPlugin::whatsThis() const//возвращает текст для отображения в QtDesigner
{
    return tr("This widget is presented in Chapter 5 of <i>C++ GUI "
              "Programming with Qt 4</i> as an example of a custom Qt "
              "widget.");
}

bool IconEditorPlugin::isContainer() const//виджет не можеьт содержать другие виджеты поэтому возвращает false
{
    return false;
}

QWidget *IconEditorPlugin::createWidget(QWidget *parent)//функция вызывается для создания экземпляра класса виджета для указанного родительсокого виджета
{
    return new IconEditor(parent);
}
#if QT_VERSION < QT_VERSION_CHECK(5, 0, 0)
Q_EXPORT_PLUGIN2(iconeditorplugin, IconEditorPlugin);//макрос делает доступным виджетт для QtDesigner
#endif
