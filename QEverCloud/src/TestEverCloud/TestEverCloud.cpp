#include <QString>
#include <QtTest>

#include <QtDebug>
#include <QEverCloud.h>
#include <utility>

class TestEverCloudTest : public QObject
{
    Q_OBJECT

public:
    TestEverCloudTest();

private Q_SLOTS:
    //void testCase1();
    //void testThumbnail();
    void testOptional();
    //void testThumbnailAsync();
};

TestEverCloudTest::TestEverCloudTest()
{
}

using namespace qevercloud;

QString sandboxDevToken = "insert your's";
QString realDevToken = "insert your's";


//void TestEverCloudTest::testCase1()
//{
//    QObject obj;
//    try {
//        UserStore* uc = new UserStore("sandbox.evernote.com", "", &obj);
//        QVERIFY(uc->checkVersion("QEverCloud test"));
//        QString noteStorePath =  uc->getNoteStoreUrl(sandboxDevToken);
//        NoteStore* nc = new NoteStore(noteStorePath, sandboxDevToken, &obj);
//        Notebook notebook = nc->getDefaultNotebook();
//        qDebug() << notebook.name << notebook.guid;
//    } catch(const std::exception& e) {
//        qDebug() << e.what();
//        throw;
//    }
//}

void TestEverCloudTest::testOptional()
{
    Optional<int> i;
    QVERIFY(!i.isSet());

    i = 10;
    QVERIFY(i.isSet());
    QVERIFY(i == 10);
    i.clear();
    QVERIFY(!i.isSet());

    i.init().ref() = 11;
    QVERIFY(i == 11);
    static_cast<int&>(i) = 12;
    QVERIFY(i == 12);

    const Optional<int> ic = ' ';
    QVERIFY(ic == 32);

    i.clear();
    i.init();
    QVERIFY2(i.isSet() && i == int(), "i.isSet() && i == int()");

    i.clear();
    bool exception = false;
    try {
        qDebug() << i;
    } catch(const EverCloudException&) {
        exception = true;
    }
    QVERIFY(exception);

    Optional<int> y, k = 10;
    y = k;
    QVERIFY(y == 10);
    Optional<double> d;
    d = y;
    QVERIFY(d == 10);
    d = ' ';
    QVERIFY(d == 32);

    Optional<double> d2(y), d3(' '), d4(d);
    QVERIFY(d2 == 10);
    QVERIFY(d3 == 32);
    QVERIFY(d4 == d);

    Optional<int> oi;
    Optional<double> od;
    QVERIFY(oi.isEqual(od));
    oi = 1;
    QVERIFY(!oi.isEqual(od));
    od = 1;
    QVERIFY(oi.isEqual(od));
    oi = 2;
    QVERIFY(!oi.isEqual(od));

    Note n1, n2;
    QVERIFY(n1 == n2);
    n1.guid = "12345";
    QVERIFY(n1 != n2);
    n2.guid = n1.guid;
    QVERIFY(n1 == n2);

    Optional<int> oi1, oi2;
    oi1 = 10;
    oi2 = std::move(oi1);
    QVERIFY(oi2 == 10);
    QVERIFY(!oi1.isSet());

    // move semantics for struct, does not work for VS 2012
//    Note note1, note2;
//    note1.guid = "12345";
//    QVERIFY(note1.guid.isSet());
//    note2 = std::move(note1);
//    QVERIFY(note2.guid.isSet());
//    QVERIFY(!note1.guid.isSet());


//    Optional<Timestamp> t;
//    t = 0;
//    t = Timestamp(0);
//    QVERIFY(t->toDateTime() == QDateTime::fromMSecsSinceEpoch(0));
//    QVERIFY(t.ref() == Timestamp(0));
//    t = Timestamp(QDateTime(QDate(1980, 3, 19)));
//    qDebug() << t.ref();
}

//void TestEverCloudTest::testThumbnail()
//{
//    Thumbnail thumb("www.evernote.com", "s41", realDevToken);
//    QByteArray data = thumb.download("2d48caeb-2452-485a-8b86-23f501d5ea43");
//    QFile f("d:/2.png");
//    f.open(QIODevice::WriteOnly);
//    f.write(data);
//    f.close();
//}

//void TestEverCloudTest::testThumbnailAsync()
//{
//    Thumbnail thumb("www.evernote.com", "s41", realDevToken);
//    AsyncResult* ar = thumb.downloadAsync("16c01e3b-d997-4e31-ba02-82c4147a8897");
//    connect(ar, &AsyncResult::finished, [](QVariant result, QSharedPointer<EverCloudExceptionData> error){
//        if(error)  {
//            qDebug() << error->errorMessage;
//        } else {
//            QByteArray data = result.toByteArray();
//            QFile f("d:/1.png");
//            f.open(QIODevice::WriteOnly);
//            f.write(data);
//            f.close();
//        }
//    });
//    QVERIFY(!ar->waitForFinished(1));
//    QVERIFY(ar->waitForFinished());
// }


QTEST_MAIN(TestEverCloudTest)

#include "TestEverCloud.moc"
