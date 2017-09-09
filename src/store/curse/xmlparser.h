#ifndef XMLPARSER_H
#define XMLPARSER_H

#include <QObject>
#include <QVector>

namespace Curse {
class Addon;
}

namespace Curse {

// XmlParser for the xml file from Curse
// too fragile IMHO, should be more fault tolerant to scheme changes
class XmlParser : public QObject
{
    Q_OBJECT
public:
    explicit XmlParser(QObject* parent = 0);

    QVector<Curse::Addon*> XmlToAddonList(const QString& xml) const;
};

}
#endif // XMLPARSER_H
