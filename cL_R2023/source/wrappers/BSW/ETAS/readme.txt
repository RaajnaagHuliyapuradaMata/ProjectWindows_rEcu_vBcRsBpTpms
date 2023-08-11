RST 10/2019

New generated code must be merged into BSW/ETAS/Gendata folder. Especially the "integration" folders contain generated files, that have manual changes.
Most integration files only have 1 line changed: the #warning directive is put in comment.

How to do this best:
1 Before generating new code, make a copy of the Gen folder in the Etas configuration.
2 Now generate code.
3 Compare the old and the new gen folder with beyond compare (compare file contents!).

Now it's clear, which files have "real" changes.
Copy the list of these files (screenshot).

4 Compare the Gendata folder in 03_Source with the new Gen folder (again compare contents).

Now a lot of files are different.

5 Manually open and merge the files from the above list.

Hints:
Beyond compare will highlight some files in the Gen folder that are missing in the Source (Dem project specific .c files). They are not necessary and even contain a comment to delete them if the contained features are not configured. So don't add them to the project.
