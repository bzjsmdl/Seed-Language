;-----------------------------------------------------------------------
;                            Target Macro 
;-----------------------------------------------------------------------
;  0  ...........................................  Optimization Seed Code           [State: Plan]
;  1  ...........................................  Optimization Seed IR           [State: Plan]
;  2  ...........................................  Assembly           
;  3  ...........................................  Machine Code(x86)           [State: Plan]
;  4  ...........................................  Object File(Windows 32, x86)           [State: Plan]
;  5  ...........................................  Executable File(Windows 32, x86)           [State: Plan]
;  6  ...........................................  Object File(Windows 64, x86)           [State: Plan]
;  7  ...........................................  Executable File(Windows 64, x86)           [State: Plan]
;  8  ...........................................  Object File(Linux 32, x86)           [State: Plan]
;  9  ...........................................  Executable File(Linux 32, x86)           [State: Plan]
;  A  ...........................................  Object File(Linux 64, x86)           [State: Plan]
;  B  ...........................................  Executable File(Linux 64, x86)           [State: Plan]
;
section .data
    ;Command Line
        ;Help
            global help, help_lengh, format, format_lengh, file, file_lengh, target, target_lengh, output, output_lengh
            help db "Type <seed -h> to get help", 13, 10, 0
            help_lengh equ $ - help - 1

            format db "Fromat: seed <Option> <Arguments> ...", 13, 10, "E.G.: seed -t win32",13, 10, 0
            format_lengh equ $ - format - 1
            file db "-f <filename>: Provide a file name to read", 13, 10, 0
            file_lengh equ $ - file - 1
            target db "-t <buildTarget>: Set the build target to <buildTarget>", 13, 10, 0
            target_lengh equ $ - target - 1
            output db "-o <filename>: Output file", 13, 10, 0
            output_lengh equ $ - output - 1
        ;Option
        global Option_help, CommandLineEnd
        Option_help db 2Dh, 00h, 68h, 00h, 00h, 00h
        CommandLineEnd dw 0
    
    global Output_File_Info, Input_File, NL
    Output_File_Info:
        ;File_name
        dd Output_Filename
        ;File_target
        dd 2


    Output_Filename db "a"
    Input_File dd 0

   
    NL db 13, 10
