# A tool to compare two directories' files
![example](https://github.com/harveylo/cmpdir/blob/master/doc/example.png){width=50% height=50}

Usage: ``cmpdir [OPTION]... [SOURCE] DEST [PATTERN]``

## Valid Options:

    -r, --recursive: Recursively compare sub-directories
    -h, --ignore-hidden: Ignore hidden files and directories
    -S, --ignore-size: Ignore file sizes, only compare file names
    -d, --destination: Destination directory
    -s, --source: Source directory
    -H, --help: Display this help and exit
    -p, --pattern: Regex pattern to match file names
    -c, --color-off: Disable colored output
    -v, --verbose: Print verbose information
When `SOURCE` is not given, the current directory is used.

`SOURCE` `DEST` and `PATTERN` can be given in order without option tags.

    Example: 
    compdir /home/user/source /home/user/destination ".*\.txt$"
    which is equivalent to:
    compdir -s /home/user/source -d /home/user/destination -p ".*\.txt$"

ATTENTION: the `cmpdir DEST PATTERN` format is not supported.

If two arguments without option tags are given, they are regarded as `SOURCE` and `DEST` respctively.

## Result Format

`-` indicates that the file is only in the source directory

`+` indicates that the file is only in the destination directory

`~` indicates that the file is in both directories, but their sizes is different

Matched files are not printed, but the number of matched files is printed at the end of the result.
## Build Instructions
Make sure your compiler supports C++17 standard.

Please remember to use release configuration when using CMake to build the project.

`cmake -DCMAKE_BUILD_TYPE=Release ../`