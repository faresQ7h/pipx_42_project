pipex

Tiny re-implementation of:
< infile cmd1 | cmd2 > outfile


Runs two commands connected by a pipe. infile -> cmd1 stdin; cmd2 stdout -> outfile (created/truncated).

Build
make        # builds ./pipex
make fclean # clean all

*******Usage*******
./pipex infile "cmd1 args..." "cmd2 args..." outfile

Examples

./pipex input "grep Hello" "wc -l" output
./pipex input "awk '{count++} END {print count}'" "cat" output
./pipex input "cat" "./script\\\"quote.sh" output
./pipex input "cat" "./script\\ space.sh" output

******Features (short)******

1- PATH resolution for commands.

2- Quote-aware parser:

'...' literal; "..." supports \" and \\.

Outside quotes: \X -> X.

3- Detects unclosed quotes (prints syntax error: unclosed quote).

4- ENOEXEC fallback: if a script has no shebang, run it as /bin/sh script ….

5- Exit codes: 127 (not found), 126 (permission/exec format/dir), otherwise 1.
Returns the second command’s status when both run.

********Notes******

-outfile opened O_CREAT|O_TRUNC (0644): -rw-r--r-
-Errors mimic shell messages (e.g., command not found: …, Permission denied, etc.).

***********************

That’s it! pipex should behave like a shell for the common two-command pipeline with basic quoting and escaping.
