
# Force qmake to launch on every build
QMAKE_EXTRA_TARGETS += after_build firsthook
firsthook.target = first
firsthook.depends = after_build
after_build.depends = all
after_build.CONFIG = phony
after_build.commands = $(DEL_FILE) $(MAKEFILE)

# qDebug is noop in release mode
CONFIG(release, debug|release) {
  DEFINES += QT_NO_DEBUG_OUTPUT
}
