#ifndef LEXER_H
#define LEXER_H

#include <QObject>

class Lexer : public QObject
{
    Q_OBJECT
public:

    enum class TerminalSymbolType {
        Comment2 = -2,
        Comment = -1,
        NoState = 0,
        Identifier = 1,
        IntegerNumber = 2,
        FloatNumber = 3,
        FloatNumber2 = 4,
        String = 5,
        String2 = 6,
        Delimiter = 7,
        DocComment = 8
    };

    struct TerminalSymbol {
        TerminalSymbolType type;
        QString data;
        QString file;
        int line;
        TerminalSymbol(TerminalSymbolType type, QString data, QString file, int line): type(type), data(data), file(file), line(line) {}
    };


    explicit Lexer(QObject *parent = 0);

    QList<TerminalSymbol> terminals() {return terminals_;}

    void feedFile(QString fileName);

private:
    QList<TerminalSymbol> terminals_;

    void lex(QString fileName, const QString &text);
    bool isNextChar(QChar testChar, QString text, int pos);
    bool isNextNextChar(QChar testChar, QString text, int pos);
};

#endif // LEXER_H
