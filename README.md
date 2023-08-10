# A tool to compare two directories' files
Usage: ``cmpdir [OPTION]... [SOURCE] DEST [PATTERN]``

Valid options:

    -r, --recursive: Recursively compare sub-directories
    -h, --ignore-hidden: Ignore hidden files and directories
    -S, --ignore-size: Ignore file sizes, only compare file names
    -d, --destination: Destination directory
    -s, --source: Source directory
    -H, --help: Display this help and exit
    -p, --pattern: Regex pattern to match file names
When SOURCE is not given, the current directory is used.

SOURCE and DEST can be given in order without option tags.

    Example: 
    compdir /home/user/source /home/user/destination
    which is equivalent to:
    compdir -s /home/user/source -d /home/user/destination