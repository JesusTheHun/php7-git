dnl $Id$
dnl config.m4 for extension git

dnl Comments in this file start with the string 'dnl'.
dnl Remove where necessary. This file will not work
dnl without editing.

dnl If your extension references something external, use with:

dnl PHP_ARG_WITH(git, for git support,
dnl Make sure that the comment is aligned:
dnl [  --with-git             Include git support])

dnl Otherwise use enable:

dnl PHP_ARG_ENABLE(git, whether to enable git support,
dnl Make sure that the comment is aligned:
dnl [  --enable-git           Enable git support])

if test "$PHP_GIT" != "no"; then
  dnl Write more examples of tests here...

  dnl # --with-git -> check with-path
  dnl SEARCH_PATH="/usr/local /usr"     # you might want to change this
  dnl SEARCH_FOR="/include/git.h"  # you most likely want to change this
  dnl if test -r $PHP_GIT/$SEARCH_FOR; then # path given as parameter
  dnl   GIT_DIR=$PHP_GIT
  dnl else # search default path list
  dnl   AC_MSG_CHECKING([for git files in default path])
  dnl   for i in $SEARCH_PATH ; do
  dnl     if test -r $i/$SEARCH_FOR; then
  dnl       GIT_DIR=$i
  dnl       AC_MSG_RESULT(found in $i)
  dnl     fi
  dnl   done
  dnl fi
  dnl
  dnl if test -z "$GIT_DIR"; then
  dnl   AC_MSG_RESULT([not found])
  dnl   AC_MSG_ERROR([Please reinstall the git distribution])
  dnl fi

  dnl # --with-git -> add include path
  dnl PHP_ADD_INCLUDE($GIT_DIR/include)

  dnl # --with-git -> check for lib and symbol presence
  dnl LIBNAME=git # you may want to change this
  dnl LIBSYMBOL=git # you most likely want to change this 

  dnl PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
  dnl [
  dnl   PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $GIT_DIR/$PHP_LIBDIR, GIT_SHARED_LIBADD)
  dnl   AC_DEFINE(HAVE_GITLIB,1,[ ])
  dnl ],[
  dnl   AC_MSG_ERROR([wrong git lib version or lib not found])
  dnl ],[
  dnl   -L$GIT_DIR/$PHP_LIBDIR -lm
  dnl ])
  dnl
  dnl PHP_SUBST(GIT_SHARED_LIBADD)

  PHP_NEW_EXTENSION(git, git.c, $ext_shared,, -DZEND_ENABLE_STATIC_TSRMLS_CACHE=1)
fi
