Rem Create a list with all .c files in this folder and all subfolders
Rem Very useful if a new autosar module shall be added to the project. All .o files must be listed then in the makefile.

dir /b /s *.c > list1.txt

for /f "tokens=*" %%A in (list1.txt) do echo %%~nxA >> files.txt

del list1.txt
