
# doxygen have to be in the path

TEMPLATE = aux

CONFIG -= debug_and_release debug_and_release_target

DOXYGEN.PROJECT_NAME = QEverCloud
DOXYGEN.PROJECT_BRIEF = Unofficial Evernote Cloud API for Qt
DOXYGEN.QHP_NAMESPACE = com.mgsxx.qevercloud
DOXYGEN.QHP_VIRTUAL_FOLDER = mgsxx
DOXYGEN.QHP_CUST_FILTER_NAME = QEverCloud
DOXYGEN.QHP_CUST_FILTER_ATTRS = QEverCloud mgsxx
DOXYGEN.QHP_SECT_FILTER_ATTRS = QEverCloud mgsxx
DOXYGEN.INPUT = $$clean_path($$PWD/../$$DOXYGEN.PROJECT_NAME)
#DOXYGEN.HTML_HEADER = $$PWD/header.html
#DOXYGEN.HTML_FOOTER = $$PWD/footer.html
#DOXYGEN.HTML_STYLESHEET = $$PWD/qt.css
#DOXYGEN.LAYOUT_FILE = $$PWD/qtlayout.xml

CONFIG(release, debug|release) {

DOXYGEN.QCH_FILE = $$OUT_PWD/$${DOXYGEN.PROJECT_NAME}.qch
DOXYGEN.OUTPUT_DIRECTORY = $$OUT_PWD
DOXYGEN.PROJECT_BRIEF = $$join(DOXYGEN.PROJECT_BRIEF,' ', \", \")
DOXYGEN.QHG_LOCATION = $$[QT_INSTALL_BINS]/qhelpgenerator
#DOXYGEN.HTML_EXTRA_STYLESHEET = $$PWD/mgs.css


_VARS = $$enumerate_vars()
DOXYGEN_VARS = $$find(_VARS, DOXYGEN.)
doxy_command =
for(var, DOXYGEN_VARS) {
  eval(varvalue = \$\${$$var})
  var = $$split(var, '.')
  var = $$last(var)
  doxy_command += & echo $$var = $$varvalue
}

doxy_command = (type $$shell_path($$PWD/Doxyfile) $$doxy_command) | doxygen -
doxy_command = $$join(doxy_command,' ')
message($$doxy_command)

QMAKE_EXTRA_TARGETS += doxygen firsthook
doxygen.target = $$DOXYGEN.QCH_FILE
doxygen.commands = $$doxy_command

doxygen.depends = $$files($$DOXYGEN.INPUT/*.*, true) $$PWD/Doxyfile $$_PRO_FILE_ # $$PWD/mgs.css

firsthook.depends = $${doxygen.target}
firsthook.target = first


}
