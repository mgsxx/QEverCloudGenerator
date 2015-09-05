# QEverCloudGenerator
The code that was used to generate [QEverCloud](https://github.com/mgsxx/QEverCloud)

Due to a radical change in my interests in programming and also due to the fact that I personaly mostly migrated out of Evernote I do not maintain QEverCloud anymore. So I've decided to upload the whole code that was used to generate QEverCloud sources from the Thrift files Evernote distributes, despite that the sources are somewhat messy and with no comments and are not portable and genarally won't buld right of the bat. But if someone will want to update QEverCloud to support new API's Evernote might introduce or will wan't to change the Thrift protocol implementation I've devised or even create his own generator that do not use Qt but some other library or even language then he/she will definately will want this sources.

As of time of writing there are people who use QEverCloud in their projects. Some of them have created forks and maintain them. You should use their forks and not my repository and contact them about pull request and bug reports. The list of the forks is posted on [QEverCloud](https://github.com/mgsxx/QEverCloud) main page. If you want your fork to appear in the list or disappear from it - contact me. That much I can do)

## Some explanations about the sources

This is subdirs project with multi-stage build process where some parts depend on others in their build process. I have used havily some pretty advanced qmake trickery for make all this mess to build on my Windows machine with both mingw and msvc compilers. It was not flawless but worked well enough.

The subprojects in order they are building:

- [**Lemon**](http://www.hwaci.com/sw/lemon/). It's a great LALR(1) parser written in C.
- **ThriftParser**. The meat. It uses LEMON to parse the Evernote Thrift files (it is NOT a general purpose Thrift parser) to gather info from the files (including comments) and then generates the bulk of the QEverCloud.
- **QEverCloud**. The end product.
- **TestEverCloud**.  Was used to test that QEverCloud works after build.
- **DoxyGen**. In release builds this subproject generates the documentation from QEverCloud subproject in html and qch formats. The latter you can include in Qt Creator and have context help on the Evernote API.
- **NotePoster**. Example.
- **CreateANote**. Another example.
- **CreateANoteAsync**. Yet another example.

### A few words about qmake trickery I used

`.qmake.cache` is the way I choosen to make my features visible to qmake. Some of them (not all) are used in .pro files. The features iself I devised for various qmake tasks are in `features` dir.

Unfortunaly, that's all I can help you with understanding the .pro files. qmake is not very well documented and never will be. It took me much efforts to gather the info to understand how it do things. I have neither time nor space here to explain everything I know and have used to make the features. If you can read Russian and are interested in qmake you can consult [the whole bunch of posts](http://blog.mgsxx.com/?page_id=1294) I wrote in my blog a couple of years ago.









