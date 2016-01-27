#include "branchmodel.h"

BranchModel::BranchModel(QObject *parent) : QStringListModel(parent)
{
    _nameToId = new QHash<QString,QString>();
    _idToName = new QHash<QString,QString>();
    _ids = new QStringList();
}

BranchModel::~BranchModel()
{
    delete _nameToId;
    delete _idToName;
    delete _ids;
}

void BranchModel::loadModel(QStringList names, QStringList ids)
{
    _nameToId->clear();
    _idToName->clear();
    this->setStringList(names);
    for(int i=0;i<names.count();i++)
    {
        _nameToId->insert(names.at(i),ids.at(i));
        _idToName->insert(ids.at(i),names.at(i));
    }
}

QStringList BranchModel::getNames()
{
    return this->stringList();
}

QStringList BranchModel::getIds()
{
    return *this->_ids;
}

QString BranchModel::idToName(QString id)
{
    return _idToName->value(id,"");
}

QString BranchModel::nameToId(QString name)
{
    return _nameToId->value(name,"");
}

QString BranchModel::getBranch(int index) const
{
    return this->stringList().at(index);
}

