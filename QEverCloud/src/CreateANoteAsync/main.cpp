#include <QCoreApplication>
#include <QTextStream>
#include <QEverCloud.h>

using namespace qevercloud;

QTextStream cout(stdout);

int main(int argc, char *argv[])
{   
    QCoreApplication a(argc, argv);
    NoteStore* ns = new NoteStore(&a);

    // вставьте сюда свой developer token
    // https://www.evernote.com/api/DeveloperToken.action
    ns->setAuthenticationToken("S=s41:U=427a0c:E=14761d37b39:C=1400a224f39:P=1cd:A=en-devtoken:V=2:H=7bceeb201764aa47d687fd0d52478ff3");

    // там же узнайте свой NoteStore URL
    ns->setNoteStoreUrl("https://www.evernote.com/shard/s41/notestore");

    Note note;
    note.title = QString("Тестовая заметка");
    note.content = QString("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
             "<!DOCTYPE en-note SYSTEM \"http://xml.evernote.com/pub/enml2.dtd\">\n"
             "<en-note>"
             "<b>Хорошо живет на свете Винни-Пух!</b><br /><br /><p>Хм, похоже, <a href=\"https://github.com/mgsxx/QEverCloud\">QEverCloud</a> таки да работает...</p>"
             "</en-note>");

    QSharedPointer<EverCloudExceptionData> error;
    QVariant result;
    QObject::connect(ns->createNoteAsync(note), &AsyncResult::finished, [ns](QVariant result, QSharedPointer<EverCloudExceptionData> error) {
        if(!error.isNull()) {
            cout << QStringLiteral("Error: ") << error->errorMessage << endl;
            qApp->quit();
        } else {
            Note note = result.value<Note>();
            cout << QStringLiteral("The new note guid: ") << note.guid << endl;

            QObject::connect(ns->getNotebookAsync(note.notebookGuid), &AsyncResult::finished, [](QVariant result, QSharedPointer<EverCloudExceptionData> error) {
               if(error.isNull()) {
                   Notebook notebook = result.value<Notebook>();
                   cout << QStringLiteral("The note is created in the notebook '") << notebook.name << QStringLiteral("'") << endl;
               } else {
                   cout << QStringLiteral("Error 2: ") << error->errorMessage << endl;

                   // пример обработки ошибок по их типу
                   QSharedPointer<EDAMNotFoundExceptionData> errorNotFound = error.objectCast<EDAMNotFoundExceptionData>();
                   if(!errorNotFound.isNull()) {
                       cout << QStringLiteral("The notebook is not found!!!") << endl;
                   }
               }
               qApp->quit();
            });
        }
    });

    return a.exec();
}

