#include <gtest/gtest.h>
#include <arguments.h>
#include <sstream>
#include <string>
#include <type_traits>
#include <iostream>
#include <fstream>

auto& arguments = Arguments::getInstance();

TEST(ArgumentsParseTest, Null){
    EXPECT_FALSE(arguments.parseArguments(0, nullptr));
    EXPECT_EQ(arguments.getArgumentCount(),0);
}

TEST(ArgumentsParseTest, Empty){
    char* argv[] = {nullptr};
    EXPECT_FALSE(arguments.parseArguments(0, argv));
    EXPECT_EQ(arguments.getArgumentCount(),0);
}
TEST(ArgumentsParseTest, EmptyWithName){
    char name[] = {'n','a','m','e','\0'};
    char* argv[] = {name};
    EXPECT_FALSE(arguments.parseArguments(1, argv));
    EXPECT_EQ(arguments.getArgumentCount(),0);
}

TEST(ArgumentsParseTest, ParseOnlyDest){
    std::string name = "name";
    std::string destination = "destination";
    char* argv[] = {name.data(), destination.data()};
    EXPECT_TRUE(arguments.parseArguments(2, argv));
    EXPECT_EQ(arguments.getArgumentCount(),1);
    EXPECT_EQ("destination", arguments.getDestination());
}

TEST(ArgumentsParseTest, ParseHelp){
    std::string name = "name";
    std::string val = "--help";
    char* argv[] = {name.data(), val.data()};
    EXPECT_FALSE(arguments.parseArguments(2, argv));
    std::string help = "-H";
    char* argv2[] = {name.data(), help.data()};
    EXPECT_FALSE(arguments.parseArguments(2, argv2));
}

TEST(ArgumentsParseTest, ParseSourceDestination){
    std::string name = "name";
    std::string source = "source";
    std::string destination = "destination";
    char* argv[] = {name.data(), source.data(), destination.data()};
    EXPECT_TRUE(arguments.parseArguments(3, argv));
    EXPECT_EQ(arguments.getArgumentCount(),2);
    EXPECT_EQ("source", arguments.getSource());
    EXPECT_EQ("destination", arguments.getDestination());
}

TEST(ArgumentsParseTest, ParseSourceDestinationPattern){
    std::string name = "name";
    std::string source = "source";
    std::string destination = "destination";
    std::string pattern = "pattern";
    char* argv[] = {name.data(), source.data(), destination.data(), pattern.data()};
    EXPECT_TRUE(arguments.parseArguments(4, argv));
    EXPECT_EQ(arguments.getArgumentCount(),3);
    EXPECT_EQ("source", arguments.getSource());
    EXPECT_EQ("destination", arguments.getDestination());
    EXPECT_EQ("pattern", arguments.getPatternString());
}

TEST(ArgumentsParseTest, ParseSDPExcess){
    std::string name = "name";
    std::string source = "source";
    std::string destination = "destination";
    std::string pattern = "pattern";
    std::string extra = "extra";
    char* argv[] = {name.data(), source.data(), destination.data(), pattern.data(), extra.data()};
    EXPECT_FALSE(arguments.parseArguments(5, argv));
}

TEST(ArgumentsParseTest, ParseSDPWithTags){
    std::string name = "name";
    std::string source = "-s";
    std::string sourceVal = "source";
    std::string destination = "-d";
    std::string destinationVal = "destination";
    std::string pattern = "-p";
    std::string patternVal = "pattern";
    char* argv[] = {
        name.data(), 
        source.data(), 
        sourceVal.data(),
        destination.data(),
        destinationVal.data(),
        pattern.data(),
        patternVal.data()
    };
    EXPECT_TRUE(arguments.parseArguments(7, argv));
    EXPECT_EQ(arguments.getArgumentCount(),3)<<"Expected 3 arguments, got "<<arguments.getArgumentCount();
    EXPECT_EQ("source", arguments.getSource());
    EXPECT_EQ("destination", arguments.getDestination());
    EXPECT_EQ("pattern", arguments.getPatternString());
}

TEST(ArgumentsParseTest, ParseSDPWithTagsAndExcess){
    std::string name = "name";
    std::string source = "-s";
    std::string sourceVal = "source";
    std::string destination = "-d";
    std::string destinationVal = "destination";
    std::string pattern = "-p";
    std::string patternVal = "pattern";
    std::string extra = "extra";
    char* argv[] = {
        name.data(), 
        source.data(), 
        sourceVal.data(),
        destination.data(),
        destinationVal.data(),
        pattern.data(),
        patternVal.data(),
        extra.data()
    };
    EXPECT_FALSE(arguments.parseArguments(8, argv));
}

TEST(ArgumentsParseTest, ParseMultipleWithHelp){
    std::string name = "name";
    std::string source = "-s";
    std::string sourceVal = "source";
    std::string destination = "-d";
    std::string destinationVal = "destination";
    std::string pattern = "-p";
    std::string patternVal = "pattern";
    std::string help = "--help";
    std::string extra = "-cvh";
    char* argv[] = {
        name.data(), 
        source.data(), 
        sourceVal.data(),
        destination.data(),
        destinationVal.data(),
        pattern.data(),
        patternVal.data(),
        help.data(),
        extra.data()
    };
    EXPECT_FALSE(arguments.parseArguments(8, argv));
}

TEST(ArgumentsParseTest, ParseMultipleWithTags){
    std::string args[] = {"name","source","destination","pattern","-cvhr"};
    int n = sizeof(args)/sizeof(args[0]);
    char* argv[n];
    for(int i = 0;i<n;i++){
        argv[i] = args[i].data();
    }
    EXPECT_TRUE(arguments.parseArguments(n, argv));
    EXPECT_EQ(arguments.getArgumentCount(),7)<<"Expected 8 arguments, got "<<arguments.getArgumentCount();
    EXPECT_EQ("source", arguments.getSource());
    EXPECT_EQ("destination", arguments.getDestination());
    EXPECT_EQ("pattern", arguments.getPatternString());
    EXPECT_FALSE(arguments.isColored());
    EXPECT_TRUE(arguments.isVerbose());
    EXPECT_TRUE(arguments.isRecursive());
    EXPECT_TRUE(arguments.isIgnoreHidden());
}
TEST(ArgumentsParseTest, ParseMultipleWithTagsPre){
    std::string args[] = {"name","-cvhr","source","destination","pattern"};
    int n = sizeof(args)/sizeof(args[0]);
    char* argv[n];
    for(int i = 0;i<n;i++){
        argv[i] = args[i].data();
    }
    EXPECT_TRUE(arguments.parseArguments(n, argv));
    EXPECT_EQ(arguments.getArgumentCount(),7)<<"Expected 8 arguments, got "<<arguments.getArgumentCount();
    EXPECT_EQ("source", arguments.getSource());
    EXPECT_EQ("destination", arguments.getDestination());
    EXPECT_EQ("pattern", arguments.getPatternString());
}

TEST(ArgumentsParseTest, ParseMultipleWithLongTags){
    std::string args[] = {"name","--color-off","--source","source","--ignore-size","--destination","destination","--recursive","--verbose","--pattern","pattern","--ignore-hidden"};
    int n = sizeof(args)/sizeof(args[0]);
    char* argv[n];
    for(int i = 0;i<n;i++){
        argv[i] = args[i].data();
    }
    EXPECT_TRUE(arguments.parseArguments(n, argv));
    EXPECT_EQ(arguments.getArgumentCount(),8)<<"Expected "<<n-1<<" arguments, got "<<arguments.getArgumentCount();
    EXPECT_EQ("source", arguments.getSource());
    EXPECT_EQ("destination", arguments.getDestination());
    EXPECT_EQ("pattern", arguments.getPatternString());
    EXPECT_TRUE(arguments.isIgnoreSize());
}

TEST(ArgumentsParseTest,ParseMultipleWithLongAndShort){
    std::string args[] = {"name","--color-off","-s","source","--ignore-size","--destination","destination","-rv","-p","pattern","--ignore-hidden"};
    int n = sizeof(args)/sizeof(args[0]);
    char* argv[n];
    for(int i = 0;i<n;i++){
        argv[i] = args[i].data();
    }
    EXPECT_TRUE(arguments.parseArguments(n, argv));
    EXPECT_EQ(arguments.getArgumentCount(),8)<<"Expected "<<n<<" arguments, got "<<arguments.getArgumentCount();
    EXPECT_EQ("source", arguments.getSource());
    EXPECT_EQ("destination", arguments.getDestination());
    EXPECT_EQ("pattern", arguments.getPatternString());
}

TEST(ArgumentsParseTest, UndefinedOption){
    std::string args[] = {"name","--color-off","-s","source","--ignore-size","--destination","destination","-rv","-p","pattern","--ignore-hidden","-x"};
    int n = sizeof(args)/sizeof(args[0]);
    char* argv[n];
    for(int i = 0;i<n;i++){
        argv[i] = args[i].data();
    }
    EXPECT_FALSE(arguments.parseArguments(n, argv));
}

TEST(ArgumentsParseTest, MissingParameter){
    std::string args[] = {"name","--color-off","--source","--ignore-size","--destination","destination","-rv","--ignore-hidden", "-p"};
    int n = sizeof(args)/sizeof(args[0]);
    char* argv[n];
    for(int i = 0;i<n;i++){
        argv[i] = args[i].data();
    }
    EXPECT_FALSE(arguments.parseArguments(n, argv));
}

TEST(ArgumentsTest, DisplayHelp){
    auto* old = std::cout.rdbuf();
    std::stringbuf  buffer;
    std::cout.rdbuf(&buffer);
    displayHelp();
    std::cout.rdbuf(old);
    std::string result = 
    "Compare two directories and list files that are different.\n"
    "Usage: cmpdir [OPTION]... [SOURCE] DEST [PATTERN]\n"
    "Valid options:\n"
    "\t-r, --recursive: Recursively compare sub-directories\n"
    "\t-h, --ignore-hidden: Ignore hidden files and directories\n"
    "\t-S, --ignore-size: Ignore file sizes, only compare file names\n"
    "\t-d, --destination: Destination directory\n"
    "\t-s, --source: Source directory\n"
    "\t-H, --help: Display this help and exit\n"
    "\t-p, --pattern: Regex pattern to match file names\n"
    "\t-c, --color-off: Disable colored output\n"
    "\t-v, --verbose: Print verbose information.\n"
    "When SOURCE is not given, the current directory is used\n"
    "SOURCE and DEST can be given in order without option tags\n"
    "\tExample: compdir /home/user/source /home/user/destination\n"
    "\twhich is equivalent to:\n"
    "\tcompdir -s /home/user/source -d /home/user/destination\n";
    EXPECT_EQ(result, buffer.str());
}