#include "php_git.h"

const char * phpgit_working_directory_get_branch(git_repository *repo, int format) {
    int error = 0;
    const char *branch = NULL;
    git_reference *head = NULL;

    error = git_repository_head(&head, repo);

    if (error == GIT_EUNBORNBRANCH || error == GIT_ENOTFOUND) {
        zend_throw_exception("Exception", "Branch not found", 404);
    } else if (!error) {
        branch = git_reference_shorthand(head);
    } else {
        zend_throw_exception("Exception", "Failed to get current branch", 500);
    }

    if (!branch) {
        if (format == FORMAT_LONG) {
            zend_throw_exception("Exception", "Not currently on any branch", 0);
        } else {
            zend_throw_exception("Exception", "HEAD (no branch)", 1);
        }
    }

    return branch;
}