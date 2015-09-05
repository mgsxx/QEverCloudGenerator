# helpers functions that do not depend on mgsProject design


# Prepares string value to be used as a macro value by substituting spaces in the string
# to \040 escape sequences, commas to \054, and parenthesis to \050 and \051, and " to \042 and ' to \047
# $$1 - string
# $$2 - optional string that will be appended to the end of the result
#       (it's for \0 which is needed sometimes)
# Example:
#    $$mgsTextDefineValue(some text with spaces,\\0)
# will yield
#    some\x20text\x20with\x20spaces\0

defineReplace(mgsTextDefineValue) {
  v = $$1
  v2 = $$2
  v3 = $$3
  v = $$join(v,\\040,,)
  !isEmpty(v2) {
    v += $$v2
    v = $$join(v,,,)
  }

  SYMB =,
  v = $$replace(v,$$SYMB,\\054)
  SYMB =(
  v = $$replace(v,$$SYMB,\\050)
  SYMB =)
  v = $$replace(v,$$SYMB,\\051)
  SYMB =\"
  v = $$replace(v,$$SYMB,\\042)
  SYMB =\'
  v = $$replace(v,$$SYMB,\\047)

  return($$v)
}

# Constructs full text macro declaration.
# $$1 - macro name
# $$2 - macro value
# $$3 - options. Supported options:
#   zero - adds \\0 to the end of the value
#   noquote - do not add quotes (\\") around the value
# Intended usage:
#   DEFINES += $$mgsTextDefine(TEXT_MACRO_NAME,some text value with spaces)
# Example:
#   $$mgsTextDefine(MACRO_NAME,some text with spaces,zero noquote)

defineReplace(mgsTextDefine) {
  options = $$3
  append =
  contains(options, zero) {
    append +=\\0
  }
  mode =
  contains(options, fixcommas) {
    mode = fixcommas
  } else: contains(options, keepcommas) {
    mode = keepcommas
  } else: contains(options, noquote) {
    mode = fixcommas
  } else {
    mode = keepcommas
  }
  v = $$mgsTextDefineValue($$2,$$append,$$mode)

  term =
  !contains(options, noquote) {
    term = \\\"
  }
  v = $${1}=$${term}$$join(v,,,)$$term
  return($$v)
}

defineReplace(mgsCmdParam) {
  v = $$1
  SYMB =\"
  return($$replace(v,$$SYMB,\\042))
}

# addSubdirs(subdirs,deps)
defineReplace(addSubdirs) {
  for(subdirs, 1) {
    entries = $$files($$subdirs)
    for(entry, entries) {
      name = $$replace(entry, [/\\\\], _)
      SUBDIRS += $$name
      eval ($${name}.subdir = $$entry)
      for(dep, 2):eval ($${name}.depends += $$replace(dep, [/\\\\], _))
      export ($${name}.subdir)
      export ($${name}.depends)
    }
  }
  export(SUBDIRS)
  return(1)
}
