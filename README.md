# cli_shell

cli

type help for list of commands

how to use:
requires a base directory, create one with cli.InsertDir("Example_BaseDir_Name", "__BASE_MENU");

you can create a new command within this directory with: 
cli.Insert("Example_Parent_Dir", { FCMDS::Example_Function, Example_MaxArg_Int, "Example Help Text" } );

you can also create directories within directories with:
cli.InsertDir("Example_Dir_Name", "Example_ParentDir_Name");

currently supports:

input handling (call function based on item)

directories, subdirectories

items

colored output (atleast in vs console, i dont remember shit about how that color output works :) )

