include(LibFindMacros)

libfind_pkg_check_modules(libgd_PKGCONF gd)

find_path(libgd_INCLUDE_DIR
  NAMES libgd.h
  PATHS ${libgd_PKGCONF_INCLUDE_DIRS}
)

find_library(libgd_LIBRARY
  NAMES gd
  PATHS ${libgd_PKGCONF_LIBRARY_DIRS}
)

set(libgd_PROCESS_INCLUDES LIBGD_INCLUDE_DIR)
set(libgd_PROCESS_LIBS LIBGD_LIBRARY)
libfind_process(libgd)
