# HELLSHELL (minishell)
[fbes](https://github.com/FreekBes)' & [jgalloni](https://github.com/jollajj98)'s work for the minishell subject in the [42](https://42.fr)/[Codam](https://www.codam.nl) core curriculum.


## Grade
[![Not graded yet](https://badge42.vercel.app/api/v2/cl1o16nym001109lewimxyxs8/project/2422501)](https://github.com/JaeSeoKim/badge42)


## Todo list

### CHECK IF THIS WORKS:
- if a path contains a / character, assume it's absolute or relative and try and access the file, DO NOT look in path and if it does not, then only check path
- test with: `< /usr/share/dict/words cat | cat > out` (should not get stuck)
- fix `echo ${${}}` (double check with `echo ${a}}`) (might not be required to work)
-lsof -p to test fd leaks

### TODO LIST:
- print `No such file or directory` when running a local executable that does not exist, instead of `command not found`
- make `"'"'` work: should have an `'` as one argument and then error out because of an unclosed `'` parameter
- do we need to implement `2>&1` etc
- fix `VARNAME="value and this is all in one value" cmd` including the double quotes at parsing the envar (`FUCKME="Makefile src/main.c" cat $FUCKME`)
- fix `^C` `^D` in read_input.c

### Builtin commands
cd: run in both child (print errors) and parent (change memory)
echo: run in child (print shit)
env: run in child (print shit)
exit: run in the child (print errors) and the parent (set exit code and exit program)
export: run in the child (print errors, but do not return errno on builtin error) and the parent (set memory)
pwd: run in the child (print shit)
unset: run in the child (print errors, but do not return errno on builtin error) and the parent (unset memory)

### ORDER ON HOW TO DO THINGS:
1. split on pipes
2. set environment variables found in the command (VAR=VALUE cmd)
3. set up the redirections (heredoc is part of that)
4. expand environment variables
5. parse the commands
6. check if it is built-in, if not find the executable, if so, run built-in
7. execute all commands at the same time (and if one doesn't expect input and the one that pipes into the non-expecting-input one tries to pipe into there, it should quit also (`cat | ls`))
