#ifndef QEVERCLOUD_IMPL_H
#define QEVERCLOUD_IMPL_H

#include "exceptions.h"
#include "globals.h"
#include "http.h"
#include "thrift.h"
#include "Optional.h"


/**

@mainpage QEverCloud

### Unofficial Evernote Cloud API for Qt

Hosted on [GitHub](https://github.com/mgsxx/QEverCloud)

This library presents complete Evernote SDK for Qt.
All the functionality that is described on [Evernote developers site](http://dev.evernote.com/doc/)
is implemented and ready to use. In particular OAuth autentication is implemented.

Most of the library is an implementation of the [Thrift Evernote API](http://dev.evernote.com/doc/reference/).

- @ref edamstruct
- @ref edamconst
- @ref edamtypes
- @ref edamservices
- @ref exceptions


There are only little differences with [the official Thrift generated C++ library](https://github.com/evernote/evernote-sdk-cpp) that were introduced
with intent to make it more convenient to use:

- Optional values in Evernote API structures are explicitly reperesented as such with @link qevercloud::Optional Optional @endlink template as opposed to having two different
structures, one for values and one for value existence flags.
- `authenticationToken` parameter is used mostly with the same value in all service functions calls so I've added a facility to specify this value as a defualt.
As a result `authenticationToken` parameter is moved from the first to the last position in functions prototypes.
- @ref page_async "Qt-style asynchronous variants" of Evernote services functions.

The mentioned official C++ SDK does not provide all the programmer needs when using Evernote and there is some Evernote functionality
that is not available via Thrift interface.

- @ref oauth "OAuth authorization"
- @link qevercloud::Thumbnail Thumbnail @endlink downloading

#### Using QEverCloud

As QEverCloud depends on Qt 5 it is very easy to compile and use.
To use to the compiled library in your project do the following:

- Link compiled library to your project in the usual way, something like this:
@code
libpath = ... # path to the library
libpath = $$clean_path($$libpath)
LIBS += $${libpath}
PRE_TARGETDEPS += $${libpath}
@endcode
- Add QEverCloud's `include` subdir to your app INCLUDEPATH qmake variable:
@code
path = $$absolute_path($$PWD/../../some/path/QEverCloud/include)
path = $$clean_path($$path)
INCLUDEPATH += $$path
@endcode
- Add to QT variabe the `network` module. If you use OAuth functionality than add also `widgets` and `webkitwidgets` modules.

Include *QEverCloud.h* or *QEverCloudOAuth.h* to use the library. The latter header is needed if you use OAuth functionality.

Qt uses OpenSSL to implement https protocol. As a result OpenSSL dynamically linked libraries (libeay32 and ssleay32) must be availabe in the PATH for your app to run successfully.
*/

/** @page page_async About asynchronous API

Asynchronous function variants let you use Qt signals/slots mechanism to call the functions in a non-blocking way.
Instead of waiting for a request completion and then returnung a result of the appropriate type asynchrounus functioins returns immediately
with @link qevercloud::AsyncResult AsyncResult @endlink as the result.
When the operation completes @link AsyncResult::finished @endlink signal is emitted.

@code
NoteStore* ns;
Note note;
...
QObject::connect(ns->createNoteAsync(note), &AsyncResult::finished, [](QVariant result, QSharedPointer<EverCloudExceptionData> error) {
    if(!error.isNull()) {
        // do something in case of an error
    } else {
        Note note = result.value<Note>();
        // process returned result
    }
});
@endcode

The result is returned through a QVariant so you have to cast it to the appropriate type. I've considered to implement different AsyncResult
types for different result types but found it too troublesome. Signals and templates do not mix well.

Asynchronous functions do not throw but report errors throw `error` parameter.
See @link qevercloud::EverCloudExceptionData EverCloudExceptionData documentation @endlink for details.

*/

/** @defgroup edamstruct Evernote API structures */

/** @defgroup edamconst Evernote API constants */

/** @defgroup edamtypes Evernote API enums and typedefs */

/** @defgroup edamservices Evernote API services */



/** @defgroup extensions Other extensions */

/** @defgroup exceptions Exception classes */



namespace qevercloud {

/** @cond HIDDEN_SYMBOLS  */

ThriftException readThriftException(ThriftBinaryBufferReader& r);

void throwEDAMSystemException(const EDAMSystemException &e);

/** @endcond */
}

#endif // QEVERCLOUD_IMPL_H
