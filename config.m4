PHP_ARG_WITH(pthreads-sanitize, wether to enable AddressSanitizer for pthreads,
[  --with-git Enable GIT support], no, no)

if test "$PHP_GIT" != "no"; then

	PHP_NEW_EXTENSION(git, git.c src/working_directory.c, $ext_shared,, -DZEND_ENABLE_STATIC_TSRMLS_CACHE=1)
	PHP_ADD_BUILD_DIR($ext_builddir/src, 1)
fi