
#include "Generator.h"

#include <QDir>
#include <QFile>

namespace {
    QStringList includeList;
    QMap<QString, QString> typedefMap;
    QStringList baseTypes;
    QSet<QString> allstructs;
    QSet<QString> allenums;
}

QString clearInclude(QString s)
{
    for(const QString& inc : includeList) {
        if(s.startsWith(inc)) {
            return s.mid(inc.length());
        }
    }
    return s;
}

QString clearTypedef(QString s)
{
    if(typedefMap.contains(s)) return typedefMap.value(s);
    return s;
}


const QString disclaimer = "// This file is generated from Evernote Thrift API and is a part of the QEverCloud project";
void writeHeaderHeader(QTextStream& out, QString fileName, QStringList moreIncludes = QStringList())
{
    out << disclaimer << endl;
    out << endl;
    QString guard = QString("QEVERCLOUD_GENERATED_%1_H").arg(fileName.split('.')[0].toUpper());
    out << "#ifndef " << guard << endl;
    out << "#define " << guard << endl;
    out << endl;

    if(fileName != "EDAMErrorCode.h") {
        QStringList includes;
        includes << "QMap" << "QList" << "QSet" << "QString" << "QStringList" << "QByteArray" << "QDateTime";
        for(QString include: includes) {
            out << "#include <" << include << ">" << endl;
        }
        out << "#include \"../Optional.h\"" << endl;
        for(QString include : moreIncludes) {
            if(include.startsWith('<')) {
                out << "#include " << include << endl;
            } else {
                out << "#include \"" << include << "\"" << endl;
            }
        }
        out << endl;
    }
    out << "namespace qevercloud {";
    out << endl;
    out << endl;
}

void writeHeaderFooter(QTextStream& out, QString fileName)
{
    out << endl;
    out << "}" << endl;
    QString guard = QString("QEVERCLOUD_GENERATED_%1_H").arg(fileName.split('.')[0].toUpper());
    out << "#endif // " << guard << endl;
}

void writeBodyHeader(QTextStream& out, QString headerFileName, QStringList moreIncludes = QStringList()) {
    out << disclaimer << endl;
    out << endl;
    out << "#include \"" << headerFileName << "\"" << endl;
    out << "#include \"../impl.h\"" << endl;
    for(QString include : moreIncludes) {
        if(include.startsWith('<')) {
            out << "#include " << include << endl;
        } else {
            out << "#include \"" << include << "\"" << endl;
        }
    }
    out << endl;
    out << "namespace qevercloud {";
    out << endl;
    out << endl;
}

void writeBodyFooter(QTextStream& out)
{
    out << endl;
    out << "}" << endl;
}

enum class MethodType {TypeName, WriteMethod, ReadMethod, ThriftFieldType, ReadTypeName, FuncParamType};
QString typeToStr(QSharedPointer<Parser::Type> type, QString identifier, MethodType methodType = MethodType::TypeName)
{
    QSharedPointer<Parser::BaseType> basetype = type.dynamicCast<Parser::BaseType>();
    QSharedPointer<Parser::VoidType> voidtype = type.dynamicCast<Parser::VoidType>();
    QSharedPointer<Parser::IdentifierType> identifiertype = type.dynamicCast<Parser::IdentifierType>();
    QSharedPointer<Parser::MapType> maptype = type.dynamicCast<Parser::MapType>();
    QSharedPointer<Parser::SetType> settype = type.dynamicCast<Parser::SetType>();
    QSharedPointer<Parser::ListType> listtype = type.dynamicCast<Parser::ListType>();
    QString result;

    QString justTypeName;
    if(methodType == MethodType::FuncParamType) {
        justTypeName = typeToStr(type, identifier, MethodType::TypeName);
    }

    if(basetype) {
        if(basetype->basetype == "bool") {
            switch(methodType) {
            case MethodType::TypeName: case MethodType::ReadTypeName: result = "bool"; break;
            case MethodType::WriteMethod: result = "w.writeBool("; break;
            case MethodType::ReadMethod: result = "r.readBool("; break;
            case MethodType::ThriftFieldType: result = "ThriftFieldType::T_BOOL"; break;
            case MethodType::FuncParamType: result = justTypeName; break;
            default: result = "";
            }
        } else if(basetype->basetype == "string") {
            switch(methodType) {
            case MethodType::TypeName: case MethodType::ReadTypeName: result = "QString"; break;
            case MethodType::WriteMethod: result = "w.writeString("; break;
            case MethodType::ReadMethod: result = "r.readString("; break;
            case MethodType::ThriftFieldType: result = "ThriftFieldType::T_STRING"; break;
            case MethodType::FuncParamType: result = justTypeName; break;
            default: result = "";
            }
        } else if(basetype->basetype == "double") {
            switch(methodType) {
            case MethodType::TypeName: case MethodType::ReadTypeName: result = "double"; break;
            case MethodType::WriteMethod: result = "w.writeDouble("; break;
            case MethodType::ReadMethod: result = "r.readDouble("; break;
            case MethodType::ThriftFieldType: result = "ThriftFieldType::T_DOUBLE"; break;
            case MethodType::FuncParamType: result = justTypeName; break;
            default: result = "";
            }
        } else if(basetype->basetype == "binary") {
            switch(methodType) {
            case MethodType::TypeName: case MethodType::ReadTypeName: result = "QByteArray"; break;
            case MethodType::WriteMethod: result = "w.writeBinary("; break;
            case MethodType::ReadMethod: result = "r.readBinary("; break;
            case MethodType::ThriftFieldType: result = "ThriftFieldType::T_STRING"; break;
            case MethodType::FuncParamType: result = justTypeName; break;
            default: result = "";
            }
        } else if(basetype->basetype == "byte") {
            switch(methodType) {
            case MethodType::TypeName: case MethodType::ReadTypeName: result = "quint8"; break;
            case MethodType::WriteMethod: result = "w.writeByte("; break;
            case MethodType::ReadMethod: result = "r.readByte("; break;
            case MethodType::ThriftFieldType: result = "ThriftFieldType::T_BYTE"; break;
            case MethodType::FuncParamType: result = justTypeName; break;
            default: result = "";
            }
        } else if(basetype->basetype == "i16") {
            switch(methodType) {
            case MethodType::TypeName: case MethodType::ReadTypeName: result = "qint16"; break;
            case MethodType::WriteMethod: result = "w.writeI16("; break;
            case MethodType::ReadMethod: result = "r.readI16("; break;
            case MethodType::ThriftFieldType: result = "ThriftFieldType::T_I16"; break;
            case MethodType::FuncParamType: result = justTypeName; break;
            default: result = "";
            }
        } else if(basetype->basetype == "i32") {
            switch(methodType) {
            case MethodType::TypeName: case MethodType::ReadTypeName: result = "qint32"; break;
            case MethodType::WriteMethod: result = "w.writeI32("; break;
            case MethodType::ReadMethod: result = "r.readI32("; break;
            case MethodType::ThriftFieldType: result = "ThriftFieldType::T_I32"; break;
            case MethodType::FuncParamType: result = justTypeName; break;
            default: result = "";
            }
        } else if(basetype->basetype == "i64") {
            switch(methodType) {
            case MethodType::TypeName: case MethodType::ReadTypeName: result = "qint64"; break;
            case MethodType::WriteMethod: result = "w.writeI64("; break;
            case MethodType::ReadMethod: result = "r.readI64("; break;
            case MethodType::ThriftFieldType: result = "ThriftFieldType::T_I64"; break;
            case MethodType::FuncParamType: result = justTypeName; break;
            default: result = "";
            }
        }
    } else if(voidtype) {
        switch(methodType) {
        case MethodType::TypeName: case MethodType::ReadTypeName: result = "void"; break;
        default: result = "";
        }
    } else if(identifiertype) {
        QString nameOfType = clearInclude(identifiertype->identifier);
        if(methodType == MethodType::FuncParamType) {
            if(allenums.contains(nameOfType)) {
                result = justTypeName;
            } else {
                QString nameOfType2 = clearTypedef(nameOfType);
                if(nameOfType2 != nameOfType) {
                    result = justTypeName;
                } else {
                    result = "const " + justTypeName + "&";
                }
            }
        } else if(methodType == MethodType::TypeName) {
            result = nameOfType;
            if(allenums.contains(result)) result = result + "::type";
        } else if(methodType == MethodType::ReadTypeName) {
            result = nameOfType == "Timestamp" ? "qint64" : nameOfType;
            if(allenums.contains(result)) result = result + "::type";
        } else {
            QString nameOfType2 = clearTypedef(nameOfType);
            if(nameOfType2 != nameOfType) {
                if(!baseTypes.contains(nameOfType2)) {
                    throw std::runtime_error("typdefs are supported for base types only");
                }
                QSharedPointer<Parser::BaseType> type2(new Parser::BaseType);
                type2->basetype = nameOfType2;
                result = typeToStr(type2, identifier, methodType);
            } else {
                if(allstructs.contains(nameOfType)) {
                    switch(methodType) {
                    case MethodType::WriteMethod: result = "write" + nameOfType + "(w, "; break;
                    case MethodType::ReadMethod: result = "read" + nameOfType + "(r, "; break;
                    case MethodType::ThriftFieldType: result = "ThriftFieldType::T_STRUCT"; break;
                    default: result = "";
                    }
                } else if(allenums.contains(nameOfType)) {
                    switch(methodType) {
                    case MethodType::WriteMethod: result = "w.writeI32(static_cast<qint32>("; break;
                    case MethodType::ReadMethod: result = "readEnum" + nameOfType + "(r, "; break;
                    case MethodType::ThriftFieldType: result = "ThriftFieldType::T_I32"; break;
                    default: result = "";
                    }
                }
            }
        }
    } else if(maptype) {
        switch(methodType) {
        case MethodType::TypeName: case MethodType::ReadTypeName: result = "QMap< " + typeToStr(maptype->keyType, identifier) + ", " + typeToStr(maptype->valueType, identifier) + " >"; break;
        case MethodType::WriteMethod: result = "w.writeMapBegin("; break;
        case MethodType::ReadMethod: result = "r.readMapBegin("; break;
        case MethodType::ThriftFieldType: result = "ThriftFieldType::T_MAP"; break;
        case MethodType::FuncParamType: result = justTypeName; break;
        default: result = "";
        }
    } else if(settype) {
        switch(methodType) {
        case MethodType::TypeName: case MethodType::ReadTypeName: result = "QSet< " + typeToStr(settype->valueType, identifier) + " >"; break;
        case MethodType::WriteMethod: result = "w.writeSetBegin("; break;
        case MethodType::ReadMethod: result = "r.readSetBegin("; break;
        case MethodType::ThriftFieldType: result = "ThriftFieldType::T_SET"; break;
        case MethodType::FuncParamType: result = justTypeName; break;
        default: result = "";
        }
    } else if(listtype) {
        switch(methodType) {
        case MethodType::TypeName: case MethodType::ReadTypeName: {
            // list<string> => QStringList
            QString valueType = typeToStr(listtype->valueType, identifier);
            if(valueType == "QString") {
                result = "QStringList";
            } else {
              result = "QList< " + valueType + " >";
            }
            break;
        }
        case MethodType::WriteMethod: result = "w.writeListBegin("; break;
        case MethodType::ReadMethod: result = "r.readListBegin("; break;
        case MethodType::ThriftFieldType: result = "ThriftFieldType::T_LIST"; break;
        case MethodType::FuncParamType: result = justTypeName; break;
        default: result = "";
        }
    }
    if(result.isEmpty()) {
        if(methodType == MethodType::TypeName || methodType == MethodType::ReadTypeName || methodType == MethodType::FuncParamType) {
          throw std::runtime_error(QString("Error! unrecognized type (%1)").arg(identifier).toStdString());
        }
    }
    return result;
}

QString valueToStr(QSharedPointer<Parser::ConstValue> value, QSharedPointer<Parser::Type> type, QString identifier)
{
    if(value.isNull()) return QString();

    QSharedPointer<Parser::MapType> maptype = type.dynamicCast<Parser::MapType>();
    QSharedPointer<Parser::SetType> settype = type.dynamicCast<Parser::SetType>();
    QSharedPointer<Parser::ListType> listtype = type.dynamicCast<Parser::ListType>();

    QSharedPointer<Parser::LiteralValue> literalvalue = value.dynamicCast<Parser::LiteralValue>();
    QSharedPointer<Parser::ListValue> listvalue = value.dynamicCast<Parser::ListValue>();
    QSharedPointer<Parser::MapValue> mapvalue = value.dynamicCast<Parser::MapValue>();

    QString result;
    if(literalvalue) {
        result = literalvalue->value;
    } else if(listvalue) {
        if(!settype && !listtype) {
            throw std::runtime_error(QString("List initializer for a unsupported type for (%1)").arg(identifier).toStdString());
        }
        result = typeToStr(type, identifier) + "()";
        for(QSharedPointer<Parser::ConstValue> v: listvalue->values) {
            result += " << " + valueToStr(v, QSharedPointer<Parser::Type>(nullptr), identifier);
        }
    } else if(mapvalue) {
        throw std::runtime_error(QString("map constants are not implemented (%1)").arg(identifier).toStdString());
    }
    if(result.isEmpty()) {
        throw std::runtime_error(QString("Error! unrecognized constant value (%1)").arg(identifier).toStdString());
    }
    return result;
}


void generateConstants(Parser* parser, QString outPath)
{
    const QString headerFileName = "constants.h";
    QFile headerFile(QDir(outPath).absoluteFilePath(headerFileName));
    if(!headerFile.open(QIODevice::WriteOnly|QIODevice::Text)) {
        throw std::runtime_error(QString("Can't open file: %1").arg(headerFile.fileName()).toStdString());
    }
    QTextStream hout(&headerFile);
    hout.setCodec("UTF-8");
    writeHeaderHeader(hout, headerFileName);
    QString file;
    for(const Parser::Constant& c: parser->constants()) {
        if(file != c.file) {
            file = c.file;
            hout << endl << "// " << c.file << endl;
        }
        if(!c.docComment.isEmpty()) {
            hout << c.docComment << endl;
        }
        hout << "extern const " << typeToStr(c.type, c.name) << " " << c.name << ";" << endl << endl;
    }
    writeHeaderFooter(hout, headerFileName);

    const QString bodyFileName = "constants.cpp";
    QFile bodyFile(QDir(outPath).absoluteFilePath(bodyFileName));
    if(!bodyFile.open(QIODevice::WriteOnly|QIODevice::Text)) {
        throw std::runtime_error(QString("Can't open file: %1").arg(bodyFile.fileName()).toStdString());
    }
    QTextStream bout(&bodyFile);
    bout.setCodec("UTF-8");
    writeBodyHeader(bout, headerFileName);
    file = "";
    for(const Parser::Constant& c: parser->constants()) {
        if(file != c.file) {
            file = c.file;
            bout << endl << "// " << c.file << endl << endl;
        }
        if(c.value.isNull()) {
            throw std::runtime_error(QString("Constant without a value: %1").arg(c.name).toStdString());
        }
        bout << "/** @ingroup edamconst */" << endl;
        bout << "const " << typeToStr(c.type, c.name) << " " << c.name << " = " << valueToStr(c.value, c.type, c.name) << ";" << endl;
    }
    writeBodyFooter(bout);
}

QString fieldToStr(const Parser::Field& field)
{
   QString s = typeToStr(field.type, field.name);
   if(field.required == Parser::Field::RequiredFlag::Optional) {
       s = "Optional< " + s + " >";
   }
   s += " " + field.name;
   if(field.initializer) {
       s += " = " + valueToStr(field.initializer, field.type, field.name);
   }
   return s;
}

QString getIdentifier(const QSharedPointer<Parser::Type>& type)
{
    auto it = type.dynamicCast<Parser::IdentifierType>();
    return it ? clearInclude(it->identifier) : QString();
}

void writeFields(QTextStream& out, const QList<Parser::Field>& fields, QString identPrefix, QString fieldPrefix)
{
    for(const Parser::Field& field : fields) {
        bool optional = field.required == Parser::Field::RequiredFlag::Optional;
        QString ident = "";
        if(optional) {
            ident = "    ";
            out << "    if(" << fieldPrefix + field.name << ".isSet()) {" << endl;
        }
        out << ident << "    w.writeFieldBegin(\"" << field.name << "\", " << typeToStr(field.type, identPrefix + ". " + field.name, MethodType::ThriftFieldType) << ", " << field.id << ");" << endl;
        QString fieldMoniker = fieldPrefix + field.name + (optional ? ".ref()" : "");
        QString writeMethod = typeToStr(field.type, identPrefix + "," + field.name, MethodType::WriteMethod);
        if(writeMethod.contains("writeListBegin")) {
            QSharedPointer<Parser::Type> valueType = field.type.dynamicCast<Parser::ListType>()->valueType;
            out << ident << "    w.writeListBegin(" << typeToStr(valueType, identPrefix + "," + field.name, MethodType::ThriftFieldType) << ", " << fieldMoniker << ".length());" << endl;
            out << ident << "    Q_FOREACH(const " + typeToStr(valueType, identPrefix + "," + field.name) + "& elem, " << fieldMoniker << ") {" << endl;
            QString writeMethod = typeToStr(valueType, identPrefix + "," + field.name, MethodType::WriteMethod);
            out << ident << "        " << writeMethod << "elem" << (writeMethod.contains("static_cast<") ? ")" : "") << ");" << endl;
            out << ident << "    }" << endl;
            out << ident << "    w.writeListEnd();" << endl;
        } else if(writeMethod.contains("writeSetBegin")) {
            QSharedPointer<Parser::Type> valueType = field.type.dynamicCast<Parser::SetType>()->valueType;
            out << ident << "    w.writeSetBegin(" << typeToStr(valueType, identPrefix + "," + field.name, MethodType::ThriftFieldType) << ", " << fieldMoniker << ".count());" << endl;
            out << ident << "    Q_FOREACH(const " + typeToStr(valueType, identPrefix + "," + field.name) + "& elem,  " << fieldMoniker << ") {" << endl;
            QString writeMethod = typeToStr(valueType, identPrefix + "," + field.name, MethodType::WriteMethod);
            out << ident << "        " << writeMethod << "elem" << (writeMethod.contains("static_cast<") ? ")" : "") << ");" << endl;
            out << ident << "    }" << endl;
            out << ident << "    w.writeSetEnd();" << endl;
        } else if(writeMethod.contains("writeMapBegin")) {
            QSharedPointer<Parser::Type> keyType = field.type.dynamicCast<Parser::MapType>()->keyType;
            QSharedPointer<Parser::Type> valueType = field.type.dynamicCast<Parser::MapType>()->valueType;
            out << ident << "    w.writeMapBegin(" << typeToStr(keyType, identPrefix + "," + field.name, MethodType::ThriftFieldType) << ", " << typeToStr(valueType, identPrefix + "," + field.name, MethodType::ThriftFieldType) << ", " << fieldMoniker << ".keys().length());" << endl;
            out << ident << "    Q_FOREACH(const " + typeToStr(keyType, identPrefix + "," + field.name) + "& elem, " << fieldMoniker << ".keys()) {" << endl;
            QString keyWriteMethod = typeToStr(keyType, identPrefix + "," + field.name, MethodType::WriteMethod);
            QString valueWriteMethod = typeToStr(valueType, identPrefix + "," + field.name, MethodType::WriteMethod);
            out << ident << "        " << keyWriteMethod << "elem" << (keyWriteMethod.contains("static_cast<") ? ")" : "") << ");" << endl;
            out << ident << "        " << valueWriteMethod << fieldMoniker << ".value(elem)" << (valueWriteMethod.contains("static_cast<") ? ")" : "") << ");" << endl;
            out << ident << "    }" << endl;
            out << ident << "    w.writeMapEnd();" << endl;
        } else {
            out << ident << "    " << writeMethod << fieldMoniker << (writeMethod.contains("static_cast<") ? ")" : "") << ");" << endl;
        }
        out << ident << "    w.writeFieldEnd();" << endl;
        if(optional) {
            out << "    }" << endl;
        }
    }
}

void readField(QTextStream& out, const Parser::Field& field, QString identPrefix, QString fieldParent)
{
    out << "                " << typeToStr(field.type, identPrefix + field.name, MethodType::ReadTypeName) << " v;" << endl;
    QString readMethod = typeToStr(field.type, identPrefix + field.name, MethodType::ReadMethod);
    if(readMethod.contains("readListBegin")) {
        QSharedPointer<Parser::Type> valueType = field.type.dynamicCast<Parser::ListType>()->valueType;
        QString valueReadMethod = typeToStr(valueType,  identPrefix + field.name, MethodType::ReadMethod);
        QString valueThriftType = typeToStr(valueType,  identPrefix + field.name, MethodType::ThriftFieldType);
        out << "                quint32 size;" << endl;
        out << "                ThriftFieldType::type elemType;" << endl;
        out << "                r.readListBegin(elemType, size);" << endl;
        out << "                v.reserve(size);" << endl;
        out << "                if(elemType != " << valueThriftType << ") throw ThriftException(ThriftException::Type::INVALID_DATA, \"Incorrect list type (" << identPrefix + field.name <<")\");" << endl;
        out << "                for(quint32 i = 0; i < size; i++) {" << endl;
        out << "                    " << typeToStr(valueType, identPrefix + field.name, MethodType::ReadTypeName)  << " elem;"<< endl;
        out << "                    " << valueReadMethod << "elem);" << endl;
        out << "                    v.append(elem);" << endl;
        out << "                }" << endl;
        out << "                r.readListEnd();" << endl;
    } else if(readMethod.contains("readSetBegin")) {
        QSharedPointer<Parser::Type> valueType = field.type.dynamicCast<Parser::SetType>()->valueType;
        QString valueReadMethod = typeToStr(valueType,  identPrefix + field.name, MethodType::ReadMethod);
        QString valueThriftType = typeToStr(valueType,  identPrefix + field.name, MethodType::ThriftFieldType);
        out << "                quint32 size;" << endl;
        out << "                ThriftFieldType::type elemType;" << endl;
        out << "                r.readSetBegin(elemType, size);" << endl;
        out << "                v.reserve(size);" << endl;
        out << "                if(elemType != " << valueThriftType << ") throw ThriftException(ThriftException::Type::INVALID_DATA, \"Incorrect set type (" << identPrefix + field.name <<")\");" << endl;
        out << "                for(quint32 i = 0; i < size; i++) {" << endl;
        out << "                    " << typeToStr(valueType, identPrefix + field.name, MethodType::ReadTypeName)  << " elem;"<< endl;
        out << "                    " << valueReadMethod << "elem);" << endl;
        out << "                    v.insert(elem);" << endl;
        out << "                }" << endl;
        out << "                r.readSetEnd();" << endl;
    } else if(readMethod.contains("readMapBegin")) {
        QSharedPointer<Parser::Type> keyType = field.type.dynamicCast<Parser::MapType>()->keyType;
        QString keyReadMethod = typeToStr(keyType, identPrefix + field.name, MethodType::ReadMethod);
        QString keyThriftType = typeToStr(keyType, identPrefix + field.name, MethodType::ThriftFieldType);
        QSharedPointer<Parser::Type> valueType = field.type.dynamicCast<Parser::MapType>()->valueType;
        QString valueReadMethod = typeToStr(valueType, identPrefix + field.name, MethodType::ReadMethod);
        QString valueThriftType = typeToStr(valueType, identPrefix + field.name, MethodType::ThriftFieldType);
        out << "                quint32 size;" << endl;
        out << "                ThriftFieldType::type keyType;" << endl;
        out << "                ThriftFieldType::type elemType;" << endl;
        out << "                r.readMapBegin(keyType, elemType, size);" << endl;
        out << "                if(keyType != " << keyThriftType << ") throw ThriftException(ThriftException::Type::INVALID_DATA, \"Incorrect map key type (" << identPrefix + field.name <<")\");" << endl;
        out << "                if(elemType != " << valueThriftType << ") throw ThriftException(ThriftException::Type::INVALID_DATA, \"Incorrect map value type (" << identPrefix + field.name <<")\");" << endl;
        out << "                for(quint32 i = 0; i < size; i++) {" << endl;
        out << "                    " << typeToStr(keyType, identPrefix + field.name, MethodType::ReadTypeName)  << " key;"<< endl;
        out << "                    " << keyReadMethod << "key);" << endl;
        out << "                    " << typeToStr(valueType, identPrefix + field.name, MethodType::ReadTypeName)  << " value;"<< endl;
        out << "                    " << valueReadMethod << "value);" << endl;
        out << "                    v[key] = value;" << endl;
        out << "                }" << endl;
        out << "                r.readMapEnd();" << endl;
    } else {
        out << "                " << readMethod << "v);" << endl;
    }
    out << "                " << fieldParent << field.name << " = v;" << endl;
}

void generateTypes(Parser* parser, QString outPath)
{
    const QString headerFileName = "types.h";
    QFile headerFile(QDir(outPath).absoluteFilePath(headerFileName));
    if(!headerFile.open(QIODevice::WriteOnly|QIODevice::Text)) {
        throw std::runtime_error(QString("Can't open file: %1").arg(headerFile.fileName()).toStdString());
    }
    QTextStream hout(&headerFile);
    hout.setCodec("UTF-8");
    const QString EDAMErrorCodeHeaderFileName = "EDAMErrorCode.h";
    writeHeaderHeader(hout, headerFileName, QStringList() << EDAMErrorCodeHeaderFileName << "<QSharedPointer>");

    QFile EDAMErrorCodeHeaderFile(QDir(outPath).absoluteFilePath(EDAMErrorCodeHeaderFileName));
    if(!EDAMErrorCodeHeaderFile.open(QIODevice::WriteOnly|QIODevice::Text)) {
        throw std::runtime_error(QString("Can't open file: %1").arg(EDAMErrorCodeHeaderFile.fileName()).toStdString());
    }
    QTextStream houtEDAMErrorCode(&EDAMErrorCodeHeaderFile);
    houtEDAMErrorCode.setCodec("UTF-8");
    writeHeaderHeader(houtEDAMErrorCode, EDAMErrorCodeHeaderFileName);

    for(const Parser::Enumeration& e: parser->enumerations()) {
        if(e.name == "EDAMErrorCode") {
            if(!e.docComment.isEmpty()) {
                houtEDAMErrorCode << e.docComment << endl;
            }
            houtEDAMErrorCode << "/** @ingroup edamtypes */" << endl;
            houtEDAMErrorCode << "struct " << e.name << " {" << endl;
            houtEDAMErrorCode << "    enum type {" << endl;
            for(int i = 0; i< e.values.length(); i++) {
                const QPair<QString, QString>& v = e.values[i];
                houtEDAMErrorCode << "        " << v.first;
                if(!v.second.isEmpty()) {
                    houtEDAMErrorCode << " = " << v.second;
                }
                if(i < (e.values.length() - 1)) {
                    houtEDAMErrorCode << ",";
                }
                houtEDAMErrorCode << endl;
            }
            houtEDAMErrorCode << "    };" << endl;
            houtEDAMErrorCode << "};" << endl << endl;
        } else {
            if(!e.docComment.isEmpty()) {
                hout << e.docComment << endl;
            }
            hout << "/** @ingroup edamtypes */" << endl;
            hout << "struct " << e.name << " {" << endl;
            hout << "    enum type {" << endl;
            for(int i = 0; i< e.values.length(); i++) {
                const QPair<QString, QString>& v = e.values[i];
                hout << "        " << v.first;
                if(!v.second.isEmpty()) {
                    hout << " = " << v.second;
                }
                if(i < (e.values.length() - 1)) {
                    hout << ",";
                }
                hout << endl;
            }
            hout << "    };" << endl;
            hout << "};" << endl << endl;
        }
    }
    hout << endl;
    houtEDAMErrorCode << endl;

    for(const Parser::TypeDefinition& t : parser->typedefs()) {
/*        if(t.name == "Timestamp") {
            if(!t.docComment.isEmpty()) {
                QString docComment = t.docComment;
                hout << "/** \\class Timestamp\n" + docComment.remove("/**") << endl << endl;
            }
        } else*/ {
            if(!t.docComment.isEmpty()) {
                hout << t.docComment << endl;
            }
            hout << "/** @ingroup edamtypes */" << endl;
            hout << "typedef " << typeToStr(t.type, t.name) << " " << t.name << ";" << endl << endl;
        }
    }
    hout << endl;

    QSet<QString> safe;
    QList<Parser::Structure> ordered;
    QList<Parser::Structure> heap = parser->structures();
    int count = heap.count();
    while(!heap.isEmpty()) {
        int i = 0;
        while(i < heap.count()) {
            const Parser::Structure s = heap[i];
            bool safeStruct = true;
            for(const Parser::Field& f : s.fields) {
                QString typeName = getIdentifier(f.type);
                QString typeName2;
                if(typeName.isEmpty()) {
                  if(f.type.dynamicCast<Parser::SetType>()) {
                    typeName = getIdentifier(f.type.dynamicCast<Parser::SetType>()->valueType);
                  } else if(f.type.dynamicCast<Parser::ListType>()) {
                    typeName = getIdentifier(f.type.dynamicCast<Parser::ListType>()->valueType);
                  } else if(f.type.dynamicCast<Parser::MapType>()) {
                    typeName = getIdentifier(f.type.dynamicCast<Parser::MapType>()->valueType);
                    typeName2 = getIdentifier(f.type.dynamicCast<Parser::MapType>()->keyType);
                  }
                }
                if(!typeName.isEmpty() && allstructs.contains(typeName) && !safe.contains(typeName)) {
                    safeStruct = false;
                    break;
                }
                if(!typeName2.isEmpty() && allstructs.contains(typeName2) && !safe.contains(typeName2)) {
                    safeStruct = false;
                    break;
                }
            }
            if(safeStruct) {
                safe << s.name;
                ordered << s;
                heap.removeAt(i);
            } else {
              i++;
            }
        }
        if(count == heap.count()) {
            throw std::runtime_error("Struct sorting is in infinite loop!");
        }
    }

    for(const Parser::Structure& s : ordered) {
        if(!s.docComment.isEmpty()) {
            hout << s.docComment << endl;
        } else {
            hout << "/** NO DOC COMMENT ID FOUND */" << endl;
        }
        hout << "/** @ingroup edamstruct */" << endl;
        hout << "struct " << s.name << " {" << endl;
        for(const Parser::Field& f : s.fields) {
            if(s.fieldComments.contains(f.name)) {
                QStringList lines = s.fieldComments[f.name].split('\n');
                for(QString line : lines) {
                    hout << "    " << line << endl;
                }
            } else {
                hout << "    " << "/** NOT DOCUMENTED */" << endl;
            }
            hout << "    " << fieldToStr(f) << ";" << endl;
        }
        hout << endl;
        hout << QStringLiteral("    bool operator==(const %1& other) const").arg(s.name) << endl;
        hout << "    {" << endl;
        bool first = true;
        for(const Parser::Field& f : s.fields) {
            if(first) {
                first = false;
                hout << "        " << "return ";
            } else {
                hout << "        " << "    && ";
            }
            if(f.required == Parser::Field::RequiredFlag::Optional) {
                hout << QStringLiteral("%1.isEqual(other.%1)").arg(f.name) << endl;
            } else {
                hout << QStringLiteral("(%1 == other.%1)").arg(f.name) << endl;
            }
        }
        hout << "        ;" << endl << "    }" << endl << endl;
        hout << QStringLiteral("    bool operator!=(const %1& other) const").arg(s.name) << endl;
        hout << "    {" << endl;
        hout << QStringLiteral("        return !(*this == other);") << endl;
        hout << "    }" << endl << endl;

        hout << "};" << endl << endl;

    }
    hout << endl;

    for(const Parser::Structure& e : parser->exceptions()) {
        if(!e.docComment.isEmpty()) {
            hout << e.docComment << endl;
        }
        hout << "/** @ingroup exceptions */" << endl;
        hout << "class " << e.name << ": public EvernoteException {" << endl;
        hout << "public:" << endl;
        for(const Parser::Field& f : e.fields) {
            hout << "    " << fieldToStr(f) << ";" << endl;
        }
        hout << endl;
        hout << "    " << e.name << "() {}" << endl;
        hout << "    ~" << e.name << "() throw() {}" << endl;
        hout << "    const char* what() const throw() Q_DECL_OVERRIDE;" << endl;
        hout << "    virtual QSharedPointer<EverCloudExceptionData> exceptionData() const Q_DECL_OVERRIDE;" << endl;
        hout << "};" << endl << endl;
    }

    writeHeaderFooter(houtEDAMErrorCode, EDAMErrorCodeHeaderFileName);
    //writeHeaderFooter(hout, headerFileName);

    hout << endl;
    hout << "}" << endl<< endl;

    for(const Parser::Structure& s : ordered) {
        hout << "Q_DECLARE_METATYPE(qevercloud::" << s.name << ")" << endl;
    }
    hout << endl;

    QString guard = QString("QEVERCLOUD_GENERATED_%1_H").arg(headerFileName.split('.')[0].toUpper());
    hout << "#endif // " << guard << endl;


    const QString headerFileName2 = "types_impl.h";
    QFile headerFile2(QDir(outPath).absoluteFilePath(headerFileName2));
    if(!headerFile2.open(QIODevice::WriteOnly|QIODevice::Text)) {
        throw std::runtime_error(QString("Can't open file: %1").arg(headerFile2.fileName()).toStdString());
    }
    QTextStream hout2(&headerFile2);
    hout2.setCodec("UTF-8");
    writeHeaderHeader(hout2, headerFileName2, QStringList() << "../impl.h" << "types.h");

    hout2 << "/** @cond HIDDEN_SYMBOLS  */" << endl << endl;

    for(const Parser::Structure& s : parser->structures()) {
        hout2 << "void write" << s.name << "(ThriftBinaryBufferWriter& w, const " << s.name << "& s);" << endl;
        hout2 << "void read" << s.name << "(ThriftBinaryBufferReader& r, " << s.name << "& s);" << endl;
    }
    hout2 << endl;

    for(const Parser::Structure& e : parser->exceptions()) {
        hout2 << "void read" << e.name << "(ThriftBinaryBufferReader& r, " << e.name << "& e);" << endl;
    }
    hout2 << endl;
    for(const Parser::Enumeration& e : parser->enumerations()) {
        hout2 << "void readEnum" << e.name << "(ThriftBinaryBufferReader& r, " << e.name << "::type& e);" << endl;
    }
    hout2 << endl;
    hout2 << "/** @endcond */" << endl;

    writeHeaderFooter(hout2, headerFileName2);

//    QList<Parser::Structure> resultStructs = parser->structures();
//    for(const Parser::Service& serv : parser->services()) {
//        for(const Parser::Function &func : serv.functions) {
//            if(!func.type.dynamicCast<Parser::VoidType>() && func.throws.length() > 0) {
//                Parser::Structure s;
//                s.file = serv.file;
//                s.name = func.name + "_result";
//                Parser::Field field;
//                field.id = 1;
//                s.fields << field;
//            }
//        }
//    }

    const QString bodyFileName = "types.cpp";
    QFile bodyFile(QDir(outPath).absoluteFilePath(bodyFileName));
    if(!bodyFile.open(QIODevice::WriteOnly|QIODevice::Text)) {
        throw std::runtime_error(QString("Can't open file: %1").arg(bodyFile.fileName()).toStdString());
    }
    QTextStream bout(&bodyFile);
    bout.setCodec("UTF-8");
    writeBodyHeader(bout, headerFileName, QStringList() << "types_impl.h");
    bout << "/** @cond HIDDEN_SYMBOLS  */" << endl << endl;
    for(const Parser::Structure& s : parser->structures()) {
        bout << "void write" << s.name << "(ThriftBinaryBufferWriter& w, const " << s.name << "& s) {" << endl;
        bout << "    w.writeStructBegin(\"" << s.name  << "\");" << endl;
        writeFields(bout, s.fields, s.name, "s.");
        bout << "    w.writeFieldStop();" << endl;
        bout << "    w.writeStructEnd();" << endl;
        bout << "}" << endl << endl;

        bout << "void read" << s.name << "(ThriftBinaryBufferReader& r, " << s.name << "& s) {" << endl;
        bout << "    QString fname;" << endl;
        bout << "    ThriftFieldType::type fieldType;" << endl;
        bout << "    qint16 fieldId;" << endl;
        for(const Parser::Field& field : s.fields) {
            if(field.required != Parser::Field::RequiredFlag::Optional) {
                bout << "    bool " << field.name << "_isset = false;" << endl;
            }
        }
        bout << "    r.readStructBegin(fname);" << endl;
        bout << "    while(true) {" << endl;
        bout << "        r.readFieldBegin(fname, fieldType, fieldId);" << endl;
        bout << "        if(fieldType == ThriftFieldType::T_STOP) break;" << endl;
        for(const Parser::Field& field : s.fields) {
            bool optional = field.required == Parser::Field::RequiredFlag::Optional;
            bout << "        if(fieldId == " << field.id << ") {" << endl;
            bout << "            if(fieldType == " << typeToStr(field.type, s.name + "." + field.name, MethodType::ThriftFieldType) << ") {" << endl;
            if(!optional) {
                bout << "                " << field.name << "_isset = true;" << endl;
            }
            readField(bout, field, s.name + ".", "s.");
            bout << "            } else {" << endl;
            bout << "                r.skip(fieldType);" << endl;
            bout << "            }" << endl;
            bout << "        } else" << endl;
        }
        bout << "        {" << endl;
        bout << "            r.skip(fieldType);" << endl;
        bout << "        }" << endl;
        bout << "        r.readFieldEnd();" << endl;
        bout << "    }" << endl;
        bout << "    r.readStructEnd();" << endl;
        for(const Parser::Field& field : s.fields) {
            if(field.required != Parser::Field::RequiredFlag::Optional) {
                bout << "    if(!" << field.name << "_isset) throw ThriftException(ThriftException::Type::INVALID_DATA, \"" << s.name << "." << field.name << " has no value\");" << endl;
            }
        }
        bout << "}" << endl << endl;
    }
    bout << endl;

    for(const Parser::Enumeration& e : parser->enumerations()) {
        bout <<  "void readEnum" << e.name << "(ThriftBinaryBufferReader& r, " << e.name << "::type& e) {" << endl;
        bout << "    qint32 i;" << endl;
        bout << "    r.readI32(i);" << endl;
        bout << "    switch(i) {" << endl;
        for(const QPair<QString, QString>& v : e.values) {
            QString value = e.name + "::" + v.first;
            bout << "    case static_cast<int>(" << value << "): e = " << value << "; break;" << endl;
        }
        bout << "    default: throw ThriftException(ThriftException::Type::INVALID_DATA, \"Incorrect value for enum " << e.name << "\");" << endl;
        bout << "    }" << endl;
        bout << "}" << endl << endl;
    }
    bout << "/** @endcond */" << endl << endl;
    bout << endl;
    writeBodyFooter(bout);
}

void generateServices(Parser* parser, QString outPath)
{
    const QString headerFileName = "services.h";
    QFile headerFile(QDir(outPath).absoluteFilePath(headerFileName));
    if(!headerFile.open(QIODevice::WriteOnly|QIODevice::Text)) {
        throw std::runtime_error(QString("Can't open file: %1").arg(headerFile.fileName()).toStdString());
    }
    QTextStream hout(&headerFile);
    hout.setCodec("UTF-8");
    writeHeaderHeader(hout, headerFileName, QStringList() << "<QObject>" << "constants.h" << "types.h" << "../AsyncResult.h");

    for(const Parser::Service& s : parser->services()) {
        if(!s.extends.isEmpty()) {
            throw std::runtime_error("extending services are not supported");
        }
        if(!s.docComment.isEmpty()) {
            hout << s.docComment << endl;
        }
        hout << "/** @ingroup edamservices */" << endl;
        hout << "class " << s.name << ": public QObject {" << endl;
        //hout << "    Q_OBJECT" << endl;
        hout << "    Q_DISABLE_COPY(" << s.name << ")"<< endl;
        hout << "public:" << endl;
        if(s.name == "UserStore") {
            hout << "    explicit UserStore(QString host, QString authenticationToken = QString(), QObject *parent = 0);" << endl << endl;

        } else {
            hout << "    explicit NoteStore(QString noteStoreUrl = QString(), QString authenticationToken = QString(), QObject *parent = 0);" << endl;
            hout << "    explicit NoteStore(QObject *parent);" << endl << endl;
            hout << "    void setNoteStoreUrl(QString noteStoreUrl) {url_ = noteStoreUrl;}" << endl;
            hout << "    QString noteStoreUrl() {return url_;}" << endl << endl;
        }
        hout << "    void setAuthenticationToken(QString authenticationToken) {authenticationToken_ = authenticationToken;}" << endl;
        hout << "    QString authenticationToken() {return authenticationToken_ ;}" << endl << endl;
        for(const Parser::Function& func : s.functions) {
            if(func.isOneway) {
                throw std::runtime_error("oneway functions are not supported");
            }
            if(!func.docComment.isEmpty()) {
                QStringList lines = func.docComment.split('\n');
                for(QString line : lines) {
                    hout << "    " << line << endl;
                }
            }
            hout << "    " << typeToStr(func.type, func.name) << " " << func.name << "(";
            int lastId = func.params.last().id;
            bool tokenParamIsPresent = false;
            for(const Parser::Field& param : func.params) {
                if(param.name == "authenticationToken") {
                    tokenParamIsPresent = true;
                } else {
                    hout << typeToStr(param.type, func.name + ", " + param.name, MethodType::FuncParamType) << " " << param.name;
                    if(param.initializer) {
                        hout << " = " << valueToStr(param.initializer, param.type, func.name + ", " + param.name);
                    }
                    if(param.id != lastId || tokenParamIsPresent) hout << ", ";
                }
            }
            if(tokenParamIsPresent) {
                hout << "QString authenticationToken = QString()";
            }
            hout << ");" << endl << endl;

            hout << "    /** Asynchronous version of @link " << func.name << " @endlink */" << endl;
            hout << "    AsyncResult* " << func.name << "Async(";
            tokenParamIsPresent = false;
            for(const Parser::Field& param : func.params) {
                if(param.name == "authenticationToken") {
                    tokenParamIsPresent = true;
                } else {
                    hout << typeToStr(param.type, func.name + ", " + param.name, MethodType::FuncParamType) << " " << param.name;
                    if(param.initializer) {
                        hout << " = " << valueToStr(param.initializer, param.type, func.name + ", " + param.name);
                    }
                    if(param.id != lastId || tokenParamIsPresent) hout << ", ";
                }
            }
            if(tokenParamIsPresent) {
                hout << "QString authenticationToken = QString()";
            }
            hout << ");" << endl << endl;
        }
        hout << "private:" << endl;
        hout << "    QString url_;" << endl;
        hout << "    QString authenticationToken_;" << endl;
        hout << "};" << endl << endl;
    }
    writeHeaderFooter(hout, headerFileName);

    const QString bodyFileName = "services.cpp";
    QFile bodyFile(QDir(outPath).absoluteFilePath(bodyFileName));
    if(!bodyFile.open(QIODevice::WriteOnly|QIODevice::Text)) {
        throw std::runtime_error(QString("Can't open file: %1").arg(bodyFile.fileName()).toStdString());
    }
    QTextStream bout(&bodyFile);
    bout.setCodec("UTF-8");
    writeBodyHeader(bout, headerFileName, QStringList() << "types_impl.h");

    bout << "/** @cond HIDDEN_SYMBOLS  */" << endl;

    for(const Parser::Service& s : parser->services()) {
        for(const Parser::Function& func : s.functions) {
            QString prepareParamsName = s.name + "_" + func.name + "_prepareParams";
            QString readReplyName = s.name + "_" + func.name + "_readReply";
            int lastId = func.params.last().id;
            bool isVoidResult = !func.type.dynamicCast<Parser::VoidType>().isNull();

            bout << "QByteArray " << prepareParamsName << "(";
            for(const Parser::Field& param : func.params) {
                bout << typeToStr(param.type, func.name + ", " + param.name, MethodType::FuncParamType) << " " << param.name;
                if(param.id != lastId) bout << ", ";
            }
            bout << ")" << endl;
            bout << "{" << endl;
            bout << "    ThriftBinaryBufferWriter w;" << endl;
            bout << "    qint32 cseqid = 0;" << endl;
            bout << "    w.writeMessageBegin(\"" << func.name << "\", ThriftMessageType::T_CALL, cseqid);" << endl;
            bout << "    w.writeStructBegin(\"" << s.name << "_" << func.name << "_pargs" << "\");" << endl;
            writeFields(bout, func.params, func.name, "");
            bout << "    w.writeFieldStop();" << endl;
            bout << "    w.writeStructEnd();" << endl;
            bout << "    w.writeMessageEnd();" << endl;
            bout << "    return w.buffer();" << endl;
            bout << "}" << endl << endl;

            bout << (isVoidResult ? QStringLiteral("void") : typeToStr(func.type, func.name)) << " " << readReplyName << "(QByteArray reply)" << endl;
            bout << "{" << endl;
            if(!isVoidResult) {
                bout << "    bool resultIsSet = false;" << endl;
                bout << "    " << typeToStr(func.type, func.name) << " result = " << typeToStr(func.type, func.name) << "();" << endl;
            }
            bout << "    ThriftBinaryBufferReader r(reply);" << endl;
            bout << "    qint32 rseqid = 0;" << endl;
            bout << "    QString fname;" << endl;
            bout << "    ThriftMessageType::type mtype;" << endl;
            bout << "    r.readMessageBegin(fname, mtype, rseqid);" << endl;
            bout << "    if (mtype == ThriftMessageType::T_EXCEPTION) {" << endl;
            bout << "      ThriftException e = readThriftException(r);" << endl;
            bout << "      r.readMessageEnd();" << endl;
            bout << "      throw e;" << endl;
            bout << "    } " << endl;
            bout << "    if (mtype != ThriftMessageType::T_REPLY) {" << endl;
            bout << "      r.skip(ThriftFieldType::T_STRUCT);" << endl;
            bout << "      r.readMessageEnd();" << endl;
            bout << "      throw ThriftException(ThriftException::Type::INVALID_MESSAGE_TYPE);" << endl;
            bout << "    }" << endl;
            bout << "    if (fname.compare(\"" << func.name << "\") != 0) {" << endl;
            bout << "      r.skip(ThriftFieldType::T_STRUCT);" << endl;
            bout << "      r.readMessageEnd();" << endl;
            bout << "      throw ThriftException(ThriftException::Type::WRONG_METHOD_NAME);" << endl;
            bout << "    }" << endl << endl;

            bout << "    ThriftFieldType::type fieldType;" << endl;
            bout << "    qint16 fieldId;" << endl;
            bout << "    r.readStructBegin(fname);" << endl;
            bout << "    while(true) {" << endl;
            bout << "        r.readFieldBegin(fname, fieldType, fieldId);" << endl;
            bout << "        if(fieldType == ThriftFieldType::T_STOP) break;" << endl;
            if(!isVoidResult) {
                Parser::Field result;
                result.id = 0;
                result.name = "result";
                result.required = Parser::Field::RequiredFlag::Required;
                result.type = func.type;
                bout << "        if(fieldId == 0) {" << endl;
                bout << "            if(fieldType == " << typeToStr(func.type, func.name, MethodType::ThriftFieldType) << ") {" << endl;
                bout << "                resultIsSet = true;" << endl;
                readField(bout, result, func.name + ".", "");
                bout << "            } else {" << endl;
                bout << "                r.skip(fieldType);" << endl;
                bout << "            }" << endl;
                bout << "        }" << endl;
            }
            bool firstThrow = isVoidResult;
            for(const Parser::Field& th : func.throws) {
                if(firstThrow) {
                    firstThrow = false;
                    bout << "        ";
                } else {
                    bout << "       else ";
                }
                bout << "if(fieldId == "  << th.id << ") {" << endl;
                QString exceptionType = typeToStr(th.type, func.name + ", " + th.name);
                bout << "            if(fieldType == ThriftFieldType::T_STRUCT) {" << endl;
                bout << "                " << exceptionType << " e;" << endl;
                bout << "                read" << exceptionType << "(r, e);" << endl;
                if(exceptionType == "EDAMSystemException") {
                    bout << "                throwEDAMSystemException(e);" << endl;
                } else {
                    bout << "                throw e;" << endl;
                }
                bout << "            } else {" << endl;
                bout << "                r.skip(fieldType);" << endl;
                bout << "            }" << endl;
                bout << "        }" << endl;
            }
            bout << "        else {" << endl;
            bout << "            r.skip(fieldType);" << endl;
            bout << "        }" << endl;
            bout << "        r.readFieldEnd();" << endl;
            bout << "    }" << endl;
            bout << "    r.readStructEnd();" << endl;

            bout << "    r.readMessageEnd();" << endl;

            if(!isVoidResult) {
                bout << "    if(!resultIsSet) throw ThriftException(ThriftException::Type::MISSING_RESULT, QStringLiteral(\"" << func.name << ": missing result\"));" << endl;
                bout << "    return result;" << endl;
            }
            bout << "}" << endl << endl;

            QString asyncReadFunctionName = readReplyName + "Async";
            bout << "QVariant " << asyncReadFunctionName << "(QByteArray reply)" << endl;
            bout << "{" << endl;
            if(isVoidResult) {
                bout << "    " << readReplyName << "(reply);" << endl;
                bout << "    return QVariant();" << endl;
            } else {
                bout << "    return QVariant::fromValue(" << readReplyName << "(reply));" << endl;
            }
            bout << "}" << endl << endl;

            bout << typeToStr(func.type, func.name) << " " << s.name << "::" << func.name << "(";
            bool tokenParamIsPresent = false;
            for(const Parser::Field& param : func.params) {
                if(param.name == "authenticationToken") {
                    tokenParamIsPresent = true;
                } else {
                    bout << typeToStr(param.type, func.name + ", " + param.name, MethodType::FuncParamType) << " " << param.name;
                    if(param.id != lastId || tokenParamIsPresent) bout << ", ";
                }
            }
            if(tokenParamIsPresent) {
                bout << "QString authenticationToken";
            }
            bout << ")" << endl;
            bout << "{" << endl;
            if(tokenParamIsPresent) {
                bout << "    if(authenticationToken.isEmpty()) authenticationToken = this->authenticationToken_;" << endl;
            }

            bout << "    QByteArray params = " << prepareParamsName << "(";
            for(const Parser::Field& param : func.params) {
                bout << param.name;
                if(param.id != lastId) bout << ", ";
            }
            bout << ");" << endl;

            bout << "    QByteArray reply = askEvernote(url_, params);" << endl;
            if(isVoidResult) {
                bout << "    " << readReplyName << "(reply);" << endl;
            } else {
                bout << "    return " << readReplyName << "(reply);" << endl;
            }

            bout << "}" << endl << endl;


            bout << "AsyncResult* " << s.name << "::" << func.name << "Async(";
            tokenParamIsPresent = false;
            for(const Parser::Field& param : func.params) {
                if(param.name == "authenticationToken") {
                    tokenParamIsPresent = true;
                } else {
                    bout << typeToStr(param.type, func.name + ", " + param.name, MethodType::FuncParamType) << " " << param.name;
                    if(param.id != lastId || tokenParamIsPresent) bout << ", ";
                }
            }
            if(tokenParamIsPresent) {
                bout << "QString authenticationToken";
            }
            bout << ")" << endl;
            bout << "{" << endl;
            if(tokenParamIsPresent) {
                bout << "    if(authenticationToken.isEmpty()) authenticationToken = this->authenticationToken_;" << endl;
            }

            bout << "    QByteArray params = " << prepareParamsName << "(";
            for(const Parser::Field& param : func.params) {
                bout << param.name;
                if(param.id != lastId) bout << ", ";
            }
            bout << ");" << endl;
            bout << "    return new AsyncResult(url_, params, " << asyncReadFunctionName << ");" << endl;

            bout << "}" << endl << endl;
        }
    }
    bout << "/** @endcond */" << endl;
    writeBodyFooter(bout);

}

void generateSources(Parser* parser, QString outPath)
{
    if(parser->unions().count() > 0) {
        throw std::runtime_error("unions are not suported.");
    }

    baseTypes << "bool" << "byte" << "i16" << "i32" << "i64" << "double" << "string" << "binary";

    for(const Parser::Structure& s : parser->structures()) {
        allstructs << s.name;
    }

    for(const Parser::Enumeration& e : parser->enumerations()) {
        allenums << e.name;
    }

    for(const Parser::Include& inc : parser->includes()) {
        QString s = inc.name;
        s.replace(QChar('\"'), QString(""));
        s.chop(QString("thrift").length());
        includeList << s;
    }

    for(const Parser::TypeDefinition& td : parser->typedefs()) {
        if(td.type.dynamicCast<Parser::BaseType>()) {
            typedefMap[td.name] = td.type.dynamicCast<Parser::BaseType>()->basetype;
        }
    }

    generateConstants(parser, outPath);
    generateTypes(parser, outPath);
    generateServices(parser, outPath);
}

