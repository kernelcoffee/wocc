#include "abstractaddon.h"

AbstractAddon::AbstractAddon(QObject *parent) : QObject(parent)
{

}

QString AbstractAddon::name() const
{
    return m_name;
}

QString AbstractAddon::author() const
{
    return m_author;
}

void AbstractAddon::setName(const QString &name)
{
    if (m_name == name)
        return;

    m_name = name;
    emit nameChanged(name);
}

void AbstractAddon::setAuthor(const QString &author)
{
    if (m_author == author)
        return;

    m_author = author;
    emit authorChanged(author);
}
