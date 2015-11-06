#ifndef HAVE_GIT_CLASS_WORKING_DIRECTORY_H
#define HAVE_GIT_CLASS_WORKING_DIRECTORY_H

enum {
  FORMAT_DEFAULT   = 0,
  FORMAT_LONG      = 1,
  FORMAT_SHORT     = 2,
  FORMAT_PORCELAIN = 3,
};

/* WorkingDirectory internal structure */

typedef struct _php_working_directory_t {
    zval        *data;
    git_repository *repo;
    zend_object  std;
} php_working_directory_t;


#define PHP_GIT_WORKING_DIRECTORY_FETCH_FROM(o)     ((php_working_directory_t*) (((char*)o) - XtOffsetOf(php_working_directory_t, std)))
#define PHP_GIT_WORKING_DIRECTORY_FETCH(z)          PHP_GIT_WORKING_DIRECTORY_FETCH_FROM(Z_OBJ_P(z)) /* }}} */


/* Let the world know what is a WorkingDirectory_ce */
zend_class_entry *WorkingDirectory_ce;


/* proto */
const char * phpgit_working_directory_get_branch(git_repository *repo, int format);
PHP_METHOD(WorkingDirectory, __construct);
PHP_METHOD(WorkingDirectory, getBranch);


/* arginfos */

ZEND_BEGIN_ARG_INFO_EX(WorkingDirectory_construct_arginfo, 0, 0, 1)
	ZEND_ARG_TYPE_INFO(0, repoPath, IS_STRING, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(WorkingDirectory_getBranch_arginfo, 0)
ZEND_END_ARG_INFO()


#else
# ifndef HAVE_GIT_CLASS_WORKING_DIRECTORY
# define HAVE_GIT_CLASS_WORKING_DIRECTORY

zend_function_entry git_working_directory_methods[] = {
    PHP_ME(WorkingDirectory, __construct, WorkingDirectory_construct_arginfo, ZEND_ACC_PUBLIC)
    PHP_ME(WorkingDirectory, getBranch, WorkingDirectory_getBranch_arginfo, ZEND_ACC_PUBLIC)
    {NULL, NULL, NULL}
};

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
# endif
#endif