PHP_ARG_WITH(git, for git support,
[  --with-git             Include git support])

if test "$PHP_GIT" != "no"; then
    PHP_NEW_EXTENSION(git, git.c src/working_directory.c classes/working_directory.c, $ext_shared,, -DZEND_ENABLE_STATIC_TSRMLS_CACHE=1)
    PHP_ADD_BUILD_DIR($ext_builddir/src, 1)
    PHP_ADD_INCLUDE($ext_builddir)
fi
