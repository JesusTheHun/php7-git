#ifndef HAVE_GIT_CLASS_WORKING_DIRECTORY
#define HAVE_GIT_CLASS_WORKING_DIRECTORY

#define PHP_GIT_WORKING_DIRECTORY_FETCH_FROM(o)     ((php_working_directory_t*) (((char*)o) - XtOffsetOf(php_working_directory_t, std)))
#define PHP_GIT_WORKING_DIRECTORY_FETCH(z)          PHP_GIT_WORKING_DIRECTORY_FETCH_FROM(Z_OBJ_P(z)) /* }}} */

/* arginfos */

ZEND_BEGIN_ARG_INFO_EX(WorkingDirectory_construct_arginfo, 0, 0, 1)
	ZEND_ARG_TYPE_INFO(0, repoPath, IS_STRING, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(WorkingDirectory_getBranch_arginfo, 0)
ZEND_END_ARG_INFO()

/*****************/
/* CLASS METHODS */
/*****************/

PHP_METHOD(WorkingDirectory, __construct)
{
    const char *repoPath;
    git_repository *repo;
    php_working_directory_t *wd;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "s", &repoPath) != SUCCESS) {
        return;
    }

    phpgit_throw_exception_on_libgit_error(
        git_repository_open(&repo, repoPath)
    );

    wd = PHP_GIT_WORKING_DIRECTORY_FETCH_FROM(Z_OBJ_P(getThis()));
    wd->repo = repo;
}

/* Print git get branch */

PHP_METHOD(WorkingDirectory, getBranch)
{
    php_working_directory_t *wd;
    git_repository *repo;
    const char *branch;
    zend_string *zbranch;

    wd = PHP_GIT_WORKING_DIRECTORY_FETCH_FROM(Z_OBJ_P(getThis()));
    repo = wd->repo;

    branch = (const char *) phpgit_working_directory_get_branch(repo, FORMAT_SHORT);

    if (branch != NULL) {
        zbranch = zend_string_init(branch, strlen(branch), 0);
        RETURN_STR(zbranch);
    } else {
        RETURN_FALSE;
    }
}

zend_function_entry git_working_directory_methods[] = {
    PHP_ME(WorkingDirectory, __construct, WorkingDirectory_construct_arginfo, ZEND_ACC_PUBLIC)
    PHP_ME(WorkingDirectory, getBranch, WorkingDirectory_getBranch_arginfo, ZEND_ACC_PUBLIC)
    {NULL, NULL, NULL}
};

#endif