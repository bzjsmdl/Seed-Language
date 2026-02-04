section .data
    ;Command Line
        ;Help
            global help, help_lengh, format, format_lengh
            help db "-h: To get help", 13, 10, 0
            help_lengh equ $ - help - 1

            format db "Fromat: seed <Target> <Input File> <Output File> <Option>", 13, 10, "E.G.: seed win32 a.seed a.asm -h",13, 10, 0
            format_lengh equ $ - format - 1
            
    global NL
    NL db 13, 10

    global CompilerTable
    CompilerTable:
        dd 0    ;Input_File
        dd 0    ;Output_File
        db 0    ;Target