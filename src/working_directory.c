#ifndef HAVE_WORKING_DIRECTORY
#define HAVE_WORKING_DIRECTORY

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"

char * void phpgit_working_directory_get_branch(git_repository *repo, int format) {
    int error = 0;
    const char *branch = NULL;
    git_reference *head = NULL;

    error = git_repository_head(&head, repo);

    if (error == GIT_EUNBORNBRANCH || error == GIT_ENOTFOUND)
        zend_throw_exception("Exception", "Branch not found", 404);
    else if (!error) {
        branch = git_reference_shorthand(head);
    } else


    if (format == FORMAT_LONG)
        printf("# On branch %s\n", branch ? branch : "Not currently on any branch.");
        zend_throw_exception("Exception", "Not currently on any branch", 0);
    else
        if (branch) {
             RETURN_NEW_STR(branch);
        } else {
            zend_throw_exception("Exception", "HEAD (no branch)", 1);
        }

    git_reference_free(head);
}


void php_indexed_init(void) {
    zend_class_entry ce;
    zend_object_handlers *zh;

    INIT_CLASS_ENTRY(ce, "WorkingDirectory", git_working_directory_methods);
    WorkingDirectory_ce = zend_register_internal_class(&ce);

    zh = zend_get_std_object_handlers();

    memcpy(&php_gitwd_handlers, zh, sizeof(zend_object_handlers));
}