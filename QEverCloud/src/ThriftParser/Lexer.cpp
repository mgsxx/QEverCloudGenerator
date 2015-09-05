#include "Lexer.h"
#include <QFile>
#include <QFileInfo>
#include <QTextStream>
#include <stdexcept>

Lexer::Lexer(QObject *parent) :
    QObject(parent)
{
}

void Lexer::feedFile(QString fileName)
{
    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly|QIODevice::Text)) {
        throw std::runtime_error(QString("Can't open file: %1").arg(fileName).toStdString());
    }
    QTextStream in(&file);
    in.setCodec("UTF-8");
    lex(QFileInfo(fileName).fileName(), in.readAll());
}

void Lexer::lex(QString fileName, const QString& text)
{
    int pos;
    TerminalSymbolType state = TerminalSymbolType::NoState;
    QString data = "";
    int lineNum = 1;
    int savedLineNum = 0;
    for(pos = 0; pos < text.length(); pos++) {
        QChar ch = text[pos];
        if(ch == '\n') lineNum++;
        switch(state) {
        case TerminalSymbolType::NoState:
            if(ch == ' ' || ch == '\t' || ch == '\n') break;
            if(ch == '/' && isNextChar('*', text, pos) && isNextNextChar('*', text, pos)) {
                state = TerminalSymbolType::DocComment;
                data.append(ch);
                savedLineNum = lineNum;
                break;
            }
            if(ch == '/' && isNextChar('*', text, pos)) {
                state = TerminalSymbolType::Comment;
                savedLineNum = lineNum;
                break;
            }
            if(ch == '/' && isNextChar('/', text, pos)) {
                state = TerminalSymbolType::Comment2;
                savedLineNum = lineNum;
                break;
            }
            if(ch.isLetter() || ch == '_') {
                state = TerminalSymbolType::Identifier;
                data.append(ch);
                savedLineNum = lineNum;
                break;
            }
            if(ch == '\"') {
                state = TerminalSymbolType::String;
                savedLineNum = lineNum;
                break;
            }
            if(ch == '\'') {
                state = TerminalSymbolType::String2;
                savedLineNum = lineNum;
                break;
            }
            if(ch == '(' || ch == ')' || ch == ':' || ch == '=' || ch == '{' || ch == '}' || ch == ',' || ch == '<' || ch == '>' || ch == '[' || ch == ']' || ch == ';') {
                terminals_ << TerminalSymbol(TerminalSymbolType::Delimiter, ch, fileName, lineNum);
                break;
            }
            if(ch.isDigit() || ch == '+' || ch == '-') {
                data.append(ch);
                state = TerminalSymbolType::IntegerNumber;
                savedLineNum = lineNum;
                break;
            }
            if(ch == '.') {
                data.append(ch);
                state = TerminalSymbolType::FloatNumber;
                break;
            }
            throw std::runtime_error(QString("Syntax error at line %1 of the file \"%2\" : %3").arg(lineNum).arg(fileName).arg(ch).toStdString());

            break;
        case TerminalSymbolType::DocComment:
            data.append(ch);
            if(ch == '*' && isNextChar('/', text, pos)) {
                pos++;
                data.append('/');
                terminals_ << TerminalSymbol(TerminalSymbolType::DocComment, data, fileName, savedLineNum);
                data = "";
                state = TerminalSymbolType::NoState;
            }
            break;
        case TerminalSymbolType::Comment:
            if(ch == '*' && isNextChar('/', text, pos)) {
                state = TerminalSymbolType::NoState;
                pos++;
            }
            break;
        case TerminalSymbolType::Comment2:
            if(ch == '\n') {
                state = TerminalSymbolType::NoState;
            }
            break;
        case TerminalSymbolType::Identifier:
            if(!ch.isLetterOrNumber() && ch != '_' && ch != '.') {
                pos--; if(ch == '\n') lineNum --;
                terminals_ << TerminalSymbol(TerminalSymbolType::Identifier, data, fileName, savedLineNum);
                data = "";
                state = TerminalSymbolType::NoState;
                break;
            }
            data.append(ch);
            break;
        case TerminalSymbolType::String:
            if(ch == '\"') {
                terminals_ << TerminalSymbol(TerminalSymbolType::String, "\"" + data + "\"", fileName, savedLineNum);
                data = "";
                state = TerminalSymbolType::NoState;
                break;
            }
            data.append(ch);
            break;
        case TerminalSymbolType::String2:
            if(ch == '\'') {
                terminals_ << TerminalSymbol(TerminalSymbolType::String, "\"" + data + "\"", fileName, savedLineNum);
                data = "";
                state = TerminalSymbolType::NoState;
                break;
            }
            data.append(ch);
            break;
        case TerminalSymbolType::Delimiter:
            throw std::runtime_error(QString("Internal error at line %1 of the file \"%2\" : %3").arg(lineNum).arg(fileName).arg(ch).toStdString());
            break;
        case TerminalSymbolType::IntegerNumber:
            if(!ch.isDigit()) {
                if(ch == '.') {
                    pos--;
                    state = TerminalSymbolType::NoState;
                } else if(ch == 'e' || ch == 'E') {
                    pos--;
                    state = TerminalSymbolType::FloatNumber;
                } else {
                    pos--; if(ch == '\n') lineNum--;
                    terminals_ << TerminalSymbol(TerminalSymbolType::IntegerNumber, data, fileName, savedLineNum);
                    data = "";
                    state = TerminalSymbolType::NoState;
                }
                break;
            }
            data.append(ch);
            break;
        case TerminalSymbolType::FloatNumber:
            if(!ch.isDigit()) {
                if(ch == 'e' || ch == 'E') {
                    data.append(ch);
                    if(isNextChar('+', text, pos) || isNextChar('-', text, pos)) {
                        pos++;
                        data.append(text[pos]);
                    }
                    state = TerminalSymbolType::FloatNumber2;
                } else {
                    pos--; if(ch == '\n') lineNum--;
                    terminals_ << TerminalSymbol(TerminalSymbolType::FloatNumber, data, fileName, savedLineNum);
                    data = "";
                    state = TerminalSymbolType::NoState;
                }
                break;
            }
            data.append(ch);
            break;

        case TerminalSymbolType::FloatNumber2:
            if(!ch.isDigit()) {
                pos--;  if(ch == '\n') lineNum--;
                terminals_ << TerminalSymbol(TerminalSymbolType::FloatNumber, data, fileName, savedLineNum);
                data = "";
                state = TerminalSymbolType::NoState;
                break;
            }
            data.append(ch);
            break;
        }
    }
}

bool Lexer::isNextChar(QChar testChar, QString text, int pos)
{
    if(text.length() <= (pos + 1)) return false;
    return text[pos + 1] == testChar;
}

bool Lexer::isNextNextChar(QChar testChar, QString text, int pos)
{
    if(text.length() <= (pos + 2)) return false;
    return text[pos + 2] == testChar;
}
