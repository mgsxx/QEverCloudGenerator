#ifndef PARSER_H
#define PARSER_H

#include <QObject>
#include "thrift_lemon.h"
#include "Lexer.h"
#include <QtDebug>
#include <QString>
#include <QStringList>
#include <QSharedPointer>

typedef QString Term;

class Parser : public QObject
{
    Q_OBJECT
public:
    explicit Parser(QObject *parent = 0);
    ~Parser();

    void feed(Lexer::TerminalSymbolType type, QString value);
    void setFile(QString file) {file_ = file; if(!files_.contains(file)) files_ << file;}
    void complete();


    struct Namespace {
        QString file;
        QString scope;
        QString name;
    };
    struct Include {
        QString file;
        QString name;
    };

    class Type {
    public:
        virtual ~Type() = 0;
    };

    class VoidType: public Type {
    public:
        ~VoidType() override {}
    };

    class BaseType: public Type {
    public:
        QString basetype;
        ~BaseType() override {}
    };

    class IdentifierType: public Type {
    public:
        QString identifier;
        ~IdentifierType() override {}
    };

    class MapType: public Type {
    public:
        QSharedPointer<Type> keyType;
        QSharedPointer<Type> valueType;
        ~MapType() override {}
    };

    class SetType: public Type {
    public:
        QSharedPointer<Type> valueType;
        ~SetType() override {}
    };

    class ListType: public Type {
    public:
        QSharedPointer<Type> valueType;
        ~ListType() override {}
    };

    struct TypeDefinition {
        QString file;
        QString name;
        QString docComment;
        QSharedPointer<Type> type;
    };

    class ConstValue {
    public:
        virtual ~ConstValue() = 0;
    };

    class LiteralValue: public ConstValue {
    public:
        QString value;
    };

    class IntegerValue: public LiteralValue {
    public:
        ~IntegerValue() override {}
    };

    class DoubleValue: public LiteralValue {
    public:
        ~DoubleValue() override {}
    };

    class StringValue: public LiteralValue {
    public:
        ~StringValue() override {}
    };

    class IdentifierValue: public LiteralValue {
    public:
        ~IdentifierValue() override {}
    };

    class ListValue: public ConstValue {
    public:
        QList<QSharedPointer<ConstValue>> values;
        ~ListValue() override {}
    };

    class MapValue: public ConstValue {
    public:
        QList<QPair<QSharedPointer<ConstValue>,QSharedPointer<ConstValue>>> values;
        ~MapValue() override {}
    };

    struct Field {
        int id;
        enum class RequiredFlag {Default, Optional, Required} required;
        QSharedPointer<Type> type;
        QString name;
        QSharedPointer<ConstValue> initializer;
    };
    struct Structure {
        QString file;
        QString name;
        QString docComment;
        QList<Field> fields;
        QMap<QString, QString> fieldComments;
        void parseStuctComment(QString rawComment);
    };

    struct Enumeration {
        QString file;
        QString name;
        QString docComment;
        QList<QPair<QString, QString>> values;
    };

    struct Function {
        bool isOneway;
        QSharedPointer<Type> type;
        QString name;
        QList<Field> params;
        QList<Field> throws;
        QString docComment;
    };
    struct Service {
        QString file;
        QString name;
        QString extends;
        QString docComment;
        QList<Function> functions;
    };

    struct Constant {
        QString file;
        QSharedPointer<Type> type;
        QString name;
        QSharedPointer<ConstValue> value;
        QString docComment;
    };

    QStringList files() {return files_;}
    QList<Namespace> namespaces() {return namespaces_;}
    QList<Include> includes() {return includes_;}
    QList<TypeDefinition> typedefs() {return typedefs_;}
    QList<Structure> structures() {return structures_;}
    QList<Enumeration> enumerations() {return enumerations_;}
    QList<Structure> exceptions() {return exceptions_;}
    QList<Service> services() {return services_;}
    QList<Constant> constants() {return constants_;}
    QList<Structure> unions() {return unions_;}

    bool isError() {return isError_;}
    QString errorMessage() {return errorMessage_;}

    void setErrorFlag(QString errorMessage) {isError_ = true; errorMessage_ = errorMessage;}

    void addTypedef(QString name, QSharedPointer<Type> type, QString docComment);
    void addNamespace(QString scope, QString name);
    void addConst(QSharedPointer<Type> type, QString name, QSharedPointer<ConstValue> value, QString docComment);
    void addInclude(QString name);
    void addStructure(QString name, QList<Field> fields, QString docComment);
    void addUnion(QString name, QList<Field> fields);
    void addException(QString name, QList<Field> fields, QString docComment);
    void addService(QString name, QString extends, QList<Function> functions, QString docComment);
    void addEnumeration(QString name, QList<QPair<QString, QString>> values, QString docComment);
private:
    void* parser;
    bool isError_;
    QString file_;
    QStringList files_;
    QString errorMessage_;

    QList<Namespace> namespaces_;
    QList<Include> includes_;
    QList<TypeDefinition> typedefs_;
    QList<Structure> structures_;
    QList<Enumeration> enumerations_;
    QList<Structure> exceptions_;
    QList<Service> services_;
    QList<Constant> constants_;
    QList<Structure> unions_;

};

inline Parser::Type::~Type() {}
inline Parser::ConstValue::~ConstValue() {}

#endif // PARSER_H
