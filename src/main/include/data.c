char* AM = {"Seed-Language Compiler: Sorry... I throw an error of alloc memory. It's not your fault.\n\
        I have an advice --\n\
        you can try again or delete me...\0"};
char* CNOF = {"Seed-Language Compiler: Ah! I can't open the file.\nNote:\n\
	1. If you didn't created the file or its path, please create it;\n\
	2. The file may be occupied by another program, system, or network, or the file is currently running;\n\
	3. More and More...\0"};
char* CLAM = {"Seed-Language Compiler: Emm... May I say that I can't pick the command line arguments? I have some tips:\n\
	1.If the command line used placeholders(- / 0), you need to write another path:\n\
	\tseed -f - => seed -f d:/-.seed\n\
	2.If arguments of the command line not finished, you should finisn it now:\n\
	\tseed -f => seed -f d:/a.seed\n\
	3.Use another tools to convert it to my command-line format\0"};
char* DSNE = {"Seed-Language Compiler: Your section name doesn't meet the standard. I think that a dot is added before the name, right? So, please delate the dot~\0"};
char* UI = {"Seed-Language Compiler: Why did you add a dot before a name(identifer)? I can't understand. So, please delate the dot~"}; 
char* chelp = {"Seed-Language Compiler: If you want to use me to compile some seed-file, you must know my command-line format. Give you a my-command-line-format table:\n\
	-h / --help: To get help;\n\
	-f / --file <ReadFromat> <FilePath>: Read the <FilePath>\n\
		<ReadFromat>: There're some options of the readfromat, like seed, ir...\n\
	-o / --output <Fromat> <FilePath>: Output the <FilePath>\n\
		<FilePath>: If no finished, default path is \"a.asm\";\n\
		<Fromat>: There're some options of the fromat, like pe, elf, asm...\0"};
char* CTCBSS = {"Seed-Language Compiler: I'm sorry to break your compilation...\n\
But you can take a look at my implemention:\n\
	(https://github.com/bzjsmdl/Seed-Language/tree/main/src/main/lexer/state32.asm or https://github.com/bzjsmdl/Seed-Language/tree/main/src/main/lexer/state64.asm)\n\
Now, my memory in BSS Segment is used up. So, do you want to alloc some more(alloc 64MB)?(y/n)\0"};