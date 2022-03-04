- replace  write / printf errors with our custom fd_putstring function
- if a path contains a / character, assume it's absolute or relative and try and access the file, DO NOT look in path and if it does not, then only check path
- make "'"' work: should have an ' as one argument and then error out because of an unclosed ' parameter
- //// Ctrl + C should not clear the entire command, should only remove the ^C (should it really?)
- test with: "< /usr/share/dict/words cat | cat > out" (should not get stuck)
- ioctl to check pipe byte limit
- check if we need to implement $PPID
- do we need to implement 2>&1 etc
- CD : child checks access to directory, if not prints error (this way stderr redirections are set correctly), then error code is passed to parent
- when a program segfaults bash prints segfault. Ours does not. I'd love to know why?





VOLGORDE ORDER SEQUENCE WHATEVER HELL
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
