#include <QCoreApplication>
#include <QTextStream>
#include <exception>
#include <QEverCloud.h>

using namespace qevercloud;


int main(int argc, char *argv[])
{   
    QCoreApplication a(argc, argv);
    QTextStream cout(stdout);
    try {
        NoteStore* ns = new NoteStore(&a);

        // вставьте сюда свой developer token
        // https://www.evernote.com/api/DeveloperToken.action
        ns->setAuthenticationToken("S=s41:U=427a0c:E=14761d37b39:C=1400a224f39:P=1cd:A=en-devtoken:V=2:H=7bceeb201764aa47d687fd0d52478ff3");

        // там же узнайте свой NoteStore URL
        ns->setNoteStoreUrl("https://www.evernote.com/shard/s41/notestore");

        Note note;
        note.title = "Тестовая заметка";
        //note.updated = QDateTime::currentMSecsSinceEpoch();
        //
        note.content = QString("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n")
                + "<!DOCTYPE en-note SYSTEM \"http://xml.evernote.com/pub/enml2.dtd\">\n"
                + "<en-note>"
                + "<b>Хорошо живет на свете Винни-Пух!</b><br /><br /><p>Хм, похоже, <a href=\"https://github.com/mgsxx/QEverCloud\">QEverCloud</a> таки да работает...</p>"
                + "</en-note>";
        note = ns->createNote(note);

//        Note note2;
//        note2.guid = note.guid;
//        note2.updated = 0;
//        note2.title = note.title;
//        ns->updateNote(note2);
    } catch(const std::exception& e) {
        cout << "exception occured: " << e.what() << endl;
        return 1;
    } catch(...) {
        cout << "unknown exception occured!" << endl;
        return 1;
    }
    return 0;
}

