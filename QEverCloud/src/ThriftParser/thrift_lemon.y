/* http://thrift.apache.org/docs/idl/ */
/* http://www.hwaci.com/sw/lemon/lemon.html */

%stack_size 2000

%include {
#include <assert.h>
#include "Parser.h"
#include "ParserHelper.h"
#include <QtDebug>
}

%token_prefix TERM_

%extra_argument { Parser* pParser }

%token_type    { QString* }
%token_destructor {delete $$;}

%syntax_error
{
    pParser->setErrorFlag("Syntax error");
}
%parse_failure
{
    pParser->setErrorFlag("Parser failure");
}
%stack_overflow
{
    pParser->setErrorFlag("Stack overflow");
}

thrift ::= body END_OF_FILE.
body ::= . 
body ::= include body. 
body ::= cppinclude body.
body ::= namespace body. 
body ::= const body. 
body ::= typedef body. 
body ::= enum body. 
body ::= struct body.
body ::= union body. 
body ::= exception body.
body ::= service body. 

include ::=  INCLUDE STRING_VALUE(A).
{
  pParser->addInclude(*A);
  delete A;
}

cppinclude ::=  CPP_INCLUDE STRING_VALUE.

namespace  ::=  NAMESPACE IDENTIFIER(A) IDENTIFIER(B).
{
  pParser->addNamespace(*A, *B);
  delete A;
  delete B;
}

const      ::= constbody .
const      ::= constbody LISTSEP .
constbody  ::= DOC_COMMENT(D) CONST fieldtype(A) IDENTIFIER(B) EQ constvalue(C) .
{
  QSharedPointer<Parser::Type> t = A->type();
  pParser->addConst(t, *B, QSharedPointer<Parser::ConstValue>(C), *D);
  delete A;
  delete B;
  delete D;
}
constbody  ::= CONST fieldtype(A) IDENTIFIER(B) EQ constvalue(C) .
{
  QSharedPointer<Parser::Type> t = A->type();
  pParser->addConst(t, *B, QSharedPointer<Parser::ConstValue>(C), QString());
  delete A;
  delete B;
}


typedef    ::= DOC_COMMENT(D) TYPEDEF definitiontype(B) IDENTIFIER(C).
{
  QSharedPointer<Parser::Type> t = B->type();
  pParser->addTypedef(*C, t, *D);
  delete B;
  delete C;
  delete D;
}

typedef    ::= TYPEDEF definitiontype(B) IDENTIFIER(C).
{
  QSharedPointer<Parser::Type> t = B->type();
  pParser->addTypedef(*C, t, QString());
  delete B;
  delete C;
}

enum       ::=  ENUM IDENTIFIER(A) CURLY_OPEN enumbody(B) CURLY_CLOSE.
{
  pParser->addEnumeration(*A, *B, QString());
  delete A;
  delete B;
}

enum       ::= DOC_COMMENT(D) ENUM IDENTIFIER(A) CURLY_OPEN enumbody(B) CURLY_CLOSE.
{
  pParser->addEnumeration(*A, *B, *D);
  delete A;
  delete B;
  delete D;
}

%type enumbody {QList<QPair<QString, QString>>*}
%destructor enumbody {delete $$;}
enumbody(A)    ::= .
{
  A = new QList<QPair<QString, QString>>;
}
enumbody(A)    ::= enumitem(B) enumbody(C) .
{
  A = C;
  A->prepend(*B);
  delete B;
}

%type enumitem {QPair<QString, QString>*}
%destructor enumitem {delete $$;}
enumitem(A)    ::= enumvalue(B) enumsep . { A = B;}
enumsep     ::= .
enumsep     ::= LISTSEP.

%type enumvalue {QPair<QString, QString>*}
%destructor enumvalue {delete $$;}
enumvalue(A)   ::= IDENTIFIER(B) enuminit(C) .
{
  A = new QPair<QString, QString>(*B, *C);
  delete B;
  delete C;
}

%type enuminit {QString*}
%destructor enuminit {delete $$;}
enuminit(A) ::= .
{
  A = new QString;
}
enuminit(A) ::= EQ INTEGER_VALUE(B) .
{
  A = B;
}

union      ::=  UNION IDENTIFIER(A) CURLY_OPEN fieldlist(B) CURLY_CLOSE.
{
  pParser->addUnion(*A, *B);
  delete A;
  delete B;
}


exception  ::=  EXCEPTION IDENTIFIER(A) CURLY_OPEN fieldlist(B) CURLY_CLOSE.
{
  pParser->addException(*A, *B, QString());
  delete A;
  delete B;
}
exception  ::= DOC_COMMENT(D) EXCEPTION IDENTIFIER(A) CURLY_OPEN fieldlist(B) CURLY_CLOSE.
{
  pParser->addException(*A, *B, *D);
  delete A;
  delete B;
  delete D;
}


struct     ::= STRUCT IDENTIFIER(A) CURLY_OPEN fieldlist(B) CURLY_CLOSE.
{
  pParser->addStructure(*A, *B, QString());
  delete A;
  delete B;
}
struct     ::= DOC_COMMENT(D) STRUCT IDENTIFIER(A) CURLY_OPEN fieldlist(B) CURLY_CLOSE.
{
  pParser->addStructure(*A, *B, *D);
  delete A;
  delete B;
  delete D;
}

%type fieldlist {QList<Parser::Field>*}
%destructor fieldlist {delete $$;}
fieldlist(A)  ::= .
{
  A = new QList<Parser::Field>;
}
fieldlist(A)  ::= fieldlist(B) field(C).
{
  A = B;
  A->append(*C);
  delete C;
}

%type field {Parser::Field*}
%destructor field {delete $$;}
field(A) ::= fieldbody(B) . {A = B;}
field(A) ::= fieldbody(B) LISTSEP . {A = B;}

%type fieldbody {Parser::Field*}
%destructor fieldbody {delete $$;}
fieldbody(A) ::= fieldidoption(B) fieldreq(C) fieldtype(D) IDENTIFIER(E) fieldinitializer(F) .
{
  A = new Parser::Field;
  A->id = B;
  A->required = C;
  A->type = QSharedPointer<Parser::Type>(D->type());
  A->name = *E;
  A->initializer = QSharedPointer<Parser::ConstValue>(F);
  delete E;
}

%type fieldidoption {int}
fieldidoption(A) ::= .
{
  A = -1;
}
fieldidoption(A) ::= fieldid(B).
{
  A = B;
}

%type fieldinitializer {Parser::ConstValue*}
%destructor fieldinitializer {delete $$;}
fieldinitializer(A) ::= .
{
  A = nullptr;
}
fieldinitializer(A) ::= EQ constvalue(B).
{
  A = B;
}

%type fieldid {int}
fieldid(A)    ::=  INTEGER_VALUE(B) COLON.
{
  A = B->toInt();
  delete B;
}

%type fieldreq {Parser::Field::RequiredFlag}
fieldreq(A)   ::= .
{
  A = Parser::Field::RequiredFlag::Default;
}
fieldreq(A)   ::= REQUIRED.
{
  A = Parser::Field::RequiredFlag::Required;
}
fieldreq(A)   ::= OPTIONAL.
{
  A = Parser::Field::RequiredFlag::Optional;
}


service    ::=  SERVICE IDENTIFIER(A) extends(B) CURLY_OPEN functionlist(C) CURLY_CLOSE.
{
  pParser->addService(*A, B ? *B : QString(), *C, QString());
  delete A;
  delete B;
  delete C;
}
service    ::= DOC_COMMENT(D) SERVICE IDENTIFIER(A) extends(B) CURLY_OPEN functionlist(C) CURLY_CLOSE.
{
  pParser->addService(*A, B ? *B : QString(), *C, *D);
  delete A;
  delete B;
  delete C;
  delete D;
}

%type extends {QString*}
%destructor fieldtype {delete $$; }
extends(A)    ::= . {
  A = nullptr;
}
extends(A)    ::= EXTENDS IDENTIFIER(B) .
{
  A = B;
}

%type functionlist {QList<Parser::Function>*}
%destructor functionlist {delete $$; }
functionlist(A) ::= .
{
  A = new QList<Parser::Function>;
}
functionlist(A) ::= functionlist(B) function(C).
{
  A = B;
  B->append(*C);
  delete C;
}

%type function {Parser::Function*}
%destructor function {delete $$; }
function(A) ::= functionbody(B). {A = B;}
function(A) ::= functionbody(B) LISTSEP. {A = B;}

%type functionbody {Parser::Function*}
%destructor functionbody {delete $$; }

functionbody(A) ::= oneway(B) functiontype(C) IDENTIFIER(D) PAREN_OPEN fieldlist(E) PAREN_CLOSE throws(F).
{
  A = new Parser::Function;
  A->isOneway = B;
  A->type = C->type();
  A->name = *D;
  A->params = *E;
  A->throws = *F;
  A->docComment = "";
  delete C;
  delete D;
  delete E;
  delete F;
}
functionbody(A) ::= DOC_COMMENT(X) oneway(B) functiontype(C) IDENTIFIER(D) PAREN_OPEN fieldlist(E) PAREN_CLOSE throws(F).
{
  A = new Parser::Function;
  A->isOneway = B;
  A->type = C->type();
  A->name = *D;
  A->params = *E;
  A->throws = *F;
  A->docComment = *X;
  delete C;
  delete D;
  delete E;
  delete F;
  delete X;
}

%type oneway {bool}
oneway(A) ::= . {A = false;}
oneway(A) ::= ONEWAY. {A = true;}

%type functiontype {Fieldtype*}
%destructor functiontype {delete $$;}
functiontype(A) ::=  fieldtype(B).
{
  A = B;
}
functiontype(A) ::=  VOID.
{
  A = new VoidType;
}

%type throws {QList<Parser::Field>*}
%destructor throws {delete $$;}
throws(A)  ::= .
{
  A = new QList<Parser::Field>;
}
throws(A)  ::=  THROWS PAREN_OPEN fieldlist(B) PAREN_CLOSE.
{
  A = B;
}

%type fieldtype {Fieldtype*}
%destructor fieldtype {delete $$; }
fieldtype(A)    ::=  IDENTIFIER(B).
{
  Identifier_Fieldtype* p = new Identifier_Fieldtype();
  p->identifier = *B;
  A = p;
  delete B;
}
fieldtype(A)    ::=  definitiontype(B) .
{
  A = B;
}


%type definitiontype {Definitiontype*}
%destructor definitiontype {delete $$; }
definitiontype(A)  ::=  basetype(B) .
{
  Basename_Definitiontype* p = new Basename_Definitiontype();
  p->basetype = *B;
  A = p;
  delete B;
}
definitiontype(A)  ::=  containertype(B) .
{
  Containertype_Definitiontype* p = new Containertype_Definitiontype();
  p->containertype = B;
  A = p;
}

%type basetype {QString*}
%destructor basetype {delete $$;}
basetype(A)        ::=  BOOL. {A = new QString("bool");}
basetype(A)        ::=  BYTE. {A = new QString("byte");}
basetype(A)        ::=  I16. {A = new QString("i16");}
basetype(A)        ::=  I32. {A = new QString("i32");}
basetype(A)        ::=  I64. {A = new QString("i64");}
basetype(A)        ::=  DOUBLE. {A = new QString("double");}
basetype(A)        ::=  STRING. {A = new QString("string");}
basetype(A)        ::=  BINARY. {A = new QString("binary");}

%type containertype {Containertype*}
//%destructor containertype {delete $$;}
containertype(A)   ::=  maptype(B) .
{
  A = B;
}
containertype(A)   ::=  settype(B).
{
  A = B;
}
containertype(A)   ::=  listtype(B).
{
  A = B;
}

%type maptype {Maptype*}
%destructor maptype {delete $$;}
maptype(A)         ::=  MAP LT fieldtype(B) LISTSEP fieldtype(C) GT.
{
  A = new Maptype();
  A->keyType = B->type();
  A->valueType = C->type();
  delete B;
  delete C;
}

%type settype {Settype*}
%destructor settype {delete $$;}
settype(A)         ::=  SET LT fieldtype(B) GT.
{
  A = new Settype();
  A->valueType = B->type();
  delete B;
}

%type listtype {Listtype*}
%destructor listtype {delete $$;}
listtype(A)         ::=  LIST LT fieldtype(B) GT.
{
  A = new Listtype();
  A->valueType = B->type();
  delete B;
}

%type constvalue {Parser::ConstValue*}
%destructor constvalue {delete $$;}
constvalue(A)    ::=  INTEGER_VALUE(B) .
{
  Parser::IntegerValue* p = new Parser::IntegerValue;
  p->value = *B;
  A = p;
  delete B;
}
constvalue(A)    ::=  DOUBLE_VALUE(B) .
{
  Parser::DoubleValue* p = new Parser::DoubleValue;
  p->value = *B;
  A = p;
  delete B;
}
constvalue(A)    ::=  STRING_VALUE(B) .
{
  Parser::StringValue* p = new Parser::StringValue;
  p->value = *B;
  A = p;
  delete B;
}
constvalue(A)    ::=  IDENTIFIER(B) .
{
  Parser::IdentifierValue* p = new Parser::IdentifierValue;
  p->value = *B;
  A = p;
  delete B;
}
constvalue(A)    ::=  constlist(B) .
{
  Parser::ListValue* p = new Parser::ListValue;
  p->values = *B;
  A = p;
  delete B;
}
constvalue(A)    ::=  constmap(B) .
{
  Parser::MapValue* p = new Parser::MapValue;
  p->values = *B;
  A = p;
  delete B;
}

%type constlist {QList<QSharedPointer<Parser::ConstValue>>*}
%destructor constvaluelist {delete $$;}
%type constvaluelist {QList<QSharedPointer<Parser::ConstValue>>*}
%destructor constvaluelist {delete $$;}
constlist(A)     ::=  BRACKET_OPEN constvaluelist(B) BRACKET_CLOSE .
{
  A = B;
}
constvaluelist(A) ::= .
{
  A = new QList<QSharedPointer<Parser::ConstValue>>;
}
constvaluelist(A) ::= constvalue(B) constvaluelist(C).
{
  A = C;
  A->prepend(QSharedPointer<Parser::ConstValue>(B));
}
constvaluelist(A) ::= constvalue(B) LISTSEP constvaluelist(C).
{
  A = C;
  A->prepend(QSharedPointer<Parser::ConstValue>(B));
}

%type constmap {QList<QPair<QSharedPointer<Parser::ConstValue>, QSharedPointer<Parser::ConstValue>>>*}
%destructor constmap {delete $$;}
%type constmapvaluelist {QList<QPair<QSharedPointer<Parser::ConstValue>, QSharedPointer<Parser::ConstValue>>>*}
%destructor constmapvaluelist {delete $$;}
constmap(A)     ::=  CURLY_OPEN constmapvaluelist(B) CURLY_CLOSE .
{
  A = B;
}
constmapvaluelist(A) ::= .
{
  A = new QList<QPair<QSharedPointer<Parser::ConstValue>, QSharedPointer<Parser::ConstValue>>>;
}
constmapvaluelist(A) ::= constvalue(B) COLON constvalue(C) constmapvaluelist(D).
{
  A = D;
  auto p = qMakePair(QSharedPointer<Parser::ConstValue>(B), QSharedPointer<Parser::ConstValue>(C));
  A->prepend(p);
}
constmapvaluelist(A) ::= constvalue(B) COLON constvalue(C) LISTSEP constmapvaluelist(D).
{
  A = D;
  auto p = qMakePair(QSharedPointer<Parser::ConstValue>(B), QSharedPointer<Parser::ConstValue>(C));
  A->prepend(p);
}

