#include <QCoreApplication>
#include "Lexer.h"
#include <QDir>
#include <QtDebug>
#include "Parser.h"
#include "Generator.h"


int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    try {
        if(qApp->arguments().length() != 3) {
            throw std::runtime_error("Incorrect arguments (thriftDir generatedDir)");
        }
        QString thriftDir = qApp->arguments().at(1);
        QString generatedDir = qApp->arguments().at(2);

//        QString thriftDir = "D:/sources/lib/QEverCloud/src/QEverCloud/thrift/src";
//        QString generatedDir = "D:/tmp/2";

        Lexer* lexer = new Lexer(&app);
        QDir dir(thriftDir);
        for(QString thriftFile : dir.entryList(QStringList() << "*.thrift", QDir::Files, QDir::Name)) {
            lexer->feedFile(dir.absoluteFilePath(thriftFile));
        }

        /*QFile outFile("D:/tmp/2/lexer.txt");
        outFile.open(QIODevice::WriteOnly);
        QTextStream out(&outFile);
        out.setCodec("UTF-8");
        for(const Lexer::TerminalSymbol& term : lexer->terminals()) {
            out << "[" << term.line << "] " << static_cast<int>(term.type) << " " << term.data << endl;
        }*/

        Parser* parser = new Parser(&app);
        for(const Lexer::TerminalSymbol& term : lexer->terminals()) {
            parser->setFile(term.file);
            //qDebug() << term.file << term.line << term.data;
            parser->feed(term.type, term.data);
            if(parser->isError()) {
                throw std::runtime_error(QString("%4 in file %1 at line %2: %3\ndetected token type: %5").arg(term.file).arg(term.line).arg(term.data)
                                         .arg(parser->errorMessage()).arg(static_cast<int>(term.type)).toStdString());
            }
        }
        parser->complete();
        if(parser->isError()) {
            throw std::runtime_error(QString("Parser error at completion: %1").arg(parser->errorMessage()).toStdString());
        }

//        qDebug() << "=========== NAMESPACES ==============";
//        for(const Parser::Namespace& n : parser->namespaces()) {
//            qDebug() << n.name << n.scope << n.file;
//        }

//        qDebug() << "=========== INCLUDES ==============";
//        for(const Parser::Include& i : parser->includes()) {
//            qDebug() << i.name << i.file;
//        }

//        qDebug() << "=========== TYPEDEFS ==============";
//        for(const Parser::TypeDefinition& td : parser->typedefs()) {
//            QString s;
//            if(td.type.dynamicCast<Parser::BaseType>()) {
//                s = td.type.dynamicCast<Parser::BaseType>()->basetype;
//            }
//            qDebug() << td.name << s << td.file;
//        }

//        qDebug() << "=========== CONSTANTS ==============";
//        for(const Parser::Constant& c : parser->constants()) {
//            QString s;
//            if(c.type.dynamicCast<Parser::BaseType>()) {
//                s = c.type.dynamicCast<Parser::BaseType>()->basetype;
//            }
//            if(c.type.dynamicCast<Parser::IdentifierType>()) {
//                s = c.type.dynamicCast<Parser::IdentifierType>()->identifier;
//            }
//            if(c.type.dynamicCast<Parser::MapType>()) {
//                s = "MAP";
//            }
//            if(c.type.dynamicCast<Parser::SetType>()) {
//                s = "SET";
//            }
//            if(c.type.dynamicCast<Parser::ListType>()) {
//                s = "LIST";
//            }
//            QString v;
//            if(c.value && c.value.dynamicCast<Parser::LiteralValue>()) {
//                v = c.value.dynamicCast<Parser::LiteralValue>()->value;
//            }
//            qDebug() << c.name << s << v << c.file;
//        }

//        qDebug() << "=========== STRUCTURES ==============";
//        for(const Parser::Structure& s : parser->structures()) {
//            QString fields;
//            for(const Parser::Field& f: s.fields) {
//                fields += f.name + (f.required == Parser::Field::RequiredFlag::Optional ? "*" : "") + " ";
//            }
//            qDebug() << s.name << fields << s.file;
//        }

//        qDebug() << "=========== UNIONS ==============";
//        for(const Parser::Structure& s : parser->unions()) {
//            QString fields;
//            for(const Parser::Field& f: s.fields) {
//                fields += f.name + (f.required == Parser::Field::RequiredFlag::Optional ? "*" : "") + " ";
//            }
//            qDebug() << s.name << fields << s.file;
//        }

//        qDebug() << "=========== EXCEPTIONS ==============";
//        for(const Parser::Structure& s : parser->exceptions()) {
//            QString fields;
//            for(const Parser::Field& f: s.fields) {
//                fields += f.name + (f.required == Parser::Field::RequiredFlag::Optional ? "*" : "") + " ";
//            }
//            qDebug() << s.name << fields << s.file;
//        }

//        qDebug() << "=========== SERVICES ==============";
//        for(const Parser::Service& s : parser->services()) {
//            qDebug() << "******** " << s.name << "       " << s.file;
//            for(const Parser::Function& f: s.functions) {
//                qDebug() << f.name << f.isOneway;
//            }
//        }

//        qDebug() << "=========== ENUMS ==============";
//        for(const Parser::Enumeration& e : parser->enumerations()) {
//            QString values;
//            for(auto v: e.values) {
//                values += v.first + "=" + v.second + " ";
//            }
//            qDebug() << e.name << values << e.file;
//        }

//        qDebug() << "=========== FILES ==============";
//        for(QString file : parser->files()) {
//            qDebug() << file;
//        }

        generateSources(parser, generatedDir);


    } catch(const std::exception& e) {
        qDebug() << "\nFAILURE!!!";
        qDebug() << e.what();
        return 1;
    } catch(...) {
        qDebug() << "\nFAILURE!!! Unknown exception\n";
        return 2;
    }

    return 0;
}
