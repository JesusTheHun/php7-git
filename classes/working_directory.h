#ifndef HAVE_GIT_CLASS_WORKING_DIRECTORY_H
#define HAVE_GIT_CLASS_WORKING_DIRECTORY_H

PHP_METHOD(WorkingDirectory, getBranch);

ZEND_BEGIN_ARG_INFO(WorkingDirectory_getBranch, 0)



extern zend_function_entry git_working_directory_methods[];

#else

#	ifndef HAVE_GIT_CLASS_WORKING_DIRECTORY
#	define HAVE_GIT_CLASS_WORKING_DIRECTORY

zend_function_entry git_working_directory_methods[] = {
    PHP_ME(WorkingDirectory, getBranch, WorkingDirectory_getBranch, ZEND_ACC_PUBLIC)
    {NULL, NULL, NULL}
};

/*****************/
/* CLASS METHODS */
/*****************/

/* Print git get branch */

PHP_METHOD(WorkingDirectory, getBranch)
{
    ZVAL_ARR(return_value, phpgit_working_directory_get_branch());
}

#	endif
#endif