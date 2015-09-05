#ifndef PARSERHELPER_H
#define PARSERHELPER_H

#include <QString>
#include "Parser.h"

class AbstratNoterminal {
public:
    virtual ~AbstratNoterminal() = 0;
};

inline AbstratNoterminal::~AbstratNoterminal() {}

class Fieldtype: public AbstratNoterminal {
public:
    virtual QSharedPointer<Parser::Type> type() = 0;
};

class VoidType: public Fieldtype {
public:
    QSharedPointer<Parser::Type> type() override {
        QSharedPointer<Parser::VoidType> p(new Parser::VoidType);
        return p;
    }
};

class Identifier_Fieldtype: public Fieldtype {
public:
    ~Identifier_Fieldtype() override {}
    QString identifier;
    QSharedPointer<Parser::Type> type() override
    {
        QSharedPointer<Parser::IdentifierType> p(new Parser::IdentifierType);
        p->identifier = identifier;
        return p;
    }
};

class Definitiontype: public Fieldtype {
public:
};

class Basename_Definitiontype: public Definitiontype {
public:
    ~Basename_Definitiontype() override {}
    QString basetype;
    QSharedPointer<Parser::Type> type() override
    {
        QSharedPointer<Parser::BaseType> p(new Parser::BaseType);
        p->basetype = basetype;
        return p;
    }
};

class Containertype: public AbstratNoterminal {
public:
    virtual QSharedPointer<Parser::Type> type() = 0;
};

class Containertype_Definitiontype: public Definitiontype {
public:
    Containertype_Definitiontype(): containertype(nullptr) {}
    ~Containertype_Definitiontype() override { delete containertype;}
    Containertype* containertype;
    QSharedPointer<Parser::Type> type() override
    {
        if(containertype) return containertype->type();
        throw std::runtime_error("containertype == nullptr");
    }
};

class Maptype: public Containertype {
public:
    ~Maptype() override {}
    QSharedPointer<Parser::Type> type() override {
        QSharedPointer<Parser::MapType> p(new Parser::MapType);
        p->keyType = keyType;
        p->valueType = valueType;
        return p;
    }
    QSharedPointer<Parser::Type> keyType;
    QSharedPointer<Parser::Type> valueType;
};

class Listtype: public Containertype {
public:
    ~Listtype() override {}
    QSharedPointer<Parser::Type> type() override {
        QSharedPointer<Parser::ListType> p(new Parser::ListType);
        p->valueType = valueType;
        return p;
    }
    QSharedPointer<Parser::Type> valueType;
};

class Settype: public Containertype {
public:
    ~Settype() override {}
    QSharedPointer<Parser::Type> type() override {
        QSharedPointer<Parser::SetType> p(new Parser::SetType);
        p->valueType = valueType;
        return p;
    }
    QSharedPointer<Parser::Type> valueType;
};

#endif // PARSERHELPER_H
