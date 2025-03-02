@echo off

REM

set new_date="Mon 4 Oct 2021 19:42:24 EDT"

set GIT_COMMITTER_DATE=%new_date%
set GIT_AUTHOR_DATE=%new_date%

git commit --amend --no-edit --date %new_date%
