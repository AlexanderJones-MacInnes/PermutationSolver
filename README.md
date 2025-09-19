This is a project I have been working on for my own personal learning. Hopefully other people might find it interesting. <br>

permutations.h is an importable header file for C++ containing a few functions that calculate permutations for a given set of N-strings. <br>
The main useful function that permutations.h provides is `SolvePermutations()` which returns a vector of strings containing all permutations of the input. <br><br>
`SolvePermutations()` can take a few types as input. Some examples of that are... <br><br>
`SolvePermutations(string) -> vector<string>` <br>
`SolvePermutations(list<string>) -> vector<string>` <br>
`SolvePermutations(vector<string>) -> vector<string>` <br><br>

This repo also includes an EXE wrapper for permutations.h in the releases section... <br>
I created this with the intention it be used as a sub-process by other programs but you can also use it as a command-line program. <br>
More information about this can be found on the release page or by entering `/help` when running permutations.exe on command-line.

