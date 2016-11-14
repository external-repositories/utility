
#include <cstdio>
#include <ostream>

#include "catch.hpp"

#include "utility.hpp"

using namespace njoy::utility::stream;

SCENARIO( "Using the FILE_streambuf to write to a file", 
         "[FILE_streambuf]"){
  GIVEN( "A file pointer and an arbitrary string to write to a file" ){
    FILE* filePtr = fopen("foo.txt", "w");
    std::string arbText{"abcdefg\n123456"};

    THEN( "the FILE_streambuf can be created and text can be written to it" ){
      {
        FILE_streambuf<char> fsb(filePtr);
        std::ostream ostm(&fsb);
        ostm << arbText;
      }
      AND_THEN( "the contents of the file can be verified." ){
//      std::string fileString{njoy::utility::slurpFileToMemory("foo.txt")};

        REQUIRE( arbText == njoy::utility::slurpFileToMemory("foo.txt") );
      }
    }
  }   // GIVEN
}   // SCENARIO
