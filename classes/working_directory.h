#ifndef HAVE_GIT_CLASS_WORKING_DIRECTORY_H
#define HAVE_GIT_CLASS_WORKING_DIRECTORY_H

PHP_METHOD(WorkingDirectory, getStatus);

ZEND_BEGIN_ARG_INFO(WorkingDirectory_getStatus, 0)
ZEND_BEGIN_ARG_INFO(WorkingDirectory_getBranch, 0)



extern zend_function_entry git_working_directory_methods[];

#else
#	ifndef HAVE_GIT_CLASS_WORKING_DIRECTORY
#	define HAVE_GIT_CLASS_WORKING_DIRECTORY

zend_function_entry git_working_directory_methods[] = {
    PHP_ME(WorkingDirectory, getBranch, Thread_start, ZEND_ACC_PUBLIC)
    PHP_ME(WorkingDirectory, getStatus, Thread_start, ZEND_ACC_PUBLIC)
    {NULL, NULL, NULL}
};

/*****************/
/* CLASS METHODS */
/*****************/

PHP_METHOD(WorkingDirectory, getBranch)
{
    ZVAL_STR(return_value, phpgit_working_directory_get_branch());
}

PHP_METHOD(WorkingDirectory, getStatus)
{
    ZVAL_ARR(return_value, phpgit_working_directory_get_status());
}

#	endif
#endif