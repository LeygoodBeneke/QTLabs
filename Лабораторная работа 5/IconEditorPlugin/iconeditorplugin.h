#ifndef ICONEDITORPLUGIN_H
#define ICONEDITORPLUGIN_H

#include <QDesignerCustomWidgetInterface>

class IconEditorPlugin : public QObject, //данный подкласс представляет собой фабрику класса, который инкапсулирует виджет iconEditor
                         public QDesignerCustomWidgetInterface
{
    Q_OBJECT
    Q_INTERFACES(QDesignerCustomWidgetInterface)//макрос указывает что переданный класс представляет собой подключаемый интерфейс. функции данного класса испольуются QtDesigner для создания экземпляров класса и получения информации о нем

public:
    IconEditorPlugin(QObject *parent = 0);

    QString name() const;
    QString includeFile() const;
    QString group() const;
    QIcon icon() const;
    QString toolTip() const;
    QString whatsThis() const;
    bool isContainer() const;
    QWidget *createWidget(QWidget *parent);
};

#endif
