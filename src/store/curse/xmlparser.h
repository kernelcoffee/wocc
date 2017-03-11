#ifndef WOWCURSEXMLPARSER_H
#define WOWCURSEXMLPARSER_H

#include <QObject>
#include <QVector>

class WowAddon;


// XmlParser for the xml file from Curse
// too fragile IMHO, should be more fault tolerant to scheme changes
class WowCurseXmlParser : public QObject
{
    Q_OBJECT
public:
    explicit WowCurseXmlParser(QObject *parent = 0);

    QVector<WowAddon*> XmlToAddonList(const QString &xml) const;
};

#endif // WOWCURSEXMLPARSER_H
