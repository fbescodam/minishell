MINISHELL (work in progress)

TODO LIST:
- if a path contains a / character, assume it's absolute or relative and try and access the file, DO NOT look in path and if it does not, then only check path
- print "No such file or directory" when running a local executable that does not exist, instead of "command not found"
- make "'"' work: should have an ' as one argument and then error out because of an unclosed ' parameter
- //// Ctrl + C should not clear the entire command, should only remove the ^C (should it really?)
- test with: "< /usr/share/dict/words cat | cat > out" (should not get stuck)
- check if we need to implement $PPID
- do we need to implement 2>&1 etc
- change envar export boolean into a string that contains the combined NAME=VALUE, or NULL if no need to export
- setting $_ envar (not required, is currently set to absolute path of minishell at setup):
	- for export, it is set to the last envar to set's name (not including the = and the value!)
	- for everything else, it is set to the last parameter of the command ran (if no parameters, that is the command ran) BEFORE RUNNING SAID COMMAND


cd: run in both child (print errors) and parent (change memory)
echo: run in child (print shit)
env: run in child (print shit)
exit: run in the child (print errors) and the parent (set exit code and exit program)
export: run in the child (print errors, but do not return errno on builtin error) and the parent (set memory)
pwd: run in the child (print shit)
unset: run in the child (print errors, but do not return errno on builtin error) and the parent (unset memory)


ORDER ON HOW TO DO THINGS:
- split on pipes
- check for and run heredoc
- set up the redirections (heredoc is part of that)
- set environment variables found in the command (VAR=VALUE cmd)
- expand environment variables
- parse the commands
- check if it is built-in, if not find the executable, if so, run built-in
- execute all commands at the same time (and if one doesn't expect input and the one that pipes into the non-expecting-input one tries to pipe into there, it should quit also (cat | ls))

-lsof -p to test fd leaks
- fix ^C ^D in read_input.c

-$FUCK="miao"
