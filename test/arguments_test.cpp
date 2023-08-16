#include <gtest/gtest.h>
#include <arguments.h>
#include <string>
#include <type_traits>

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