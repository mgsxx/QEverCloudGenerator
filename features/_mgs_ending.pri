CONFIG -= mgs_check_proper_ending

for(folder, FOLDERS) {
  !exists($${_PRO_FILE_PWD_}/$${folder}) {
     system(mkdir $$system_path($${_PRO_FILE_PWD_}/$${folder}))
  }
  !exists($${_PRO_FILE_PWD_}/$${folder}/$${folder}.pri) {
     system(@echo $$LITERAL_HASH $$folder > $$system_path($${_PRO_FILE_PWD_}/$${folder}/$${folder}.pri))
  }
  include($${_PRO_FILE_PWD_}/$${folder}/$${folder}.pri)
}
unset(folder)

mgstest {
  TEMPLATE = app
  CONFIG -= staticlib dll shared sylib static plugin
}