namespace string {

/* regular expression constants */
const std::regex 
integerPattern_
( "\\s*(\\+|-)?[[:d:]]+\\s*", std::regex::optimize | std::regex::nosubs );

const std::regex 
infinityPattern_
( "\\s*(\\+|-)inf((inity)?)\\s*",
  std::regex::optimize | std::regex::nosubs | std::regex::icase );

const std::regex 
decimalFormPattern_
( "\\s*(\\+|-)?(([[:d:]]+(\\.([[:d:]]*))?)|(\\.([[:d:]]+)))\\s*",
  std::regex::optimize | std::regex::nosubs );

const std::regex 
realNumberPattern_ /* https://xkcd.com/1171/ */
( "\\s*(\\+|-)?(([[:d:]]+((\\.([[:d:]]*))?((([ed](\\+|-)?)"
  "|(\\+|-))[[:d:]]+)?)?)|(\\.([[:d:]]+)(((([ed](\\+|-)?)|"
  "(\\+|-))[[:d:]]+)?)))\\s*", 
  std::regex::optimize | std::regex::nosubs | std::regex::icase );

/* Forward Declaration of function signatures */
std::vector< std::string > split( const std::string& s );

std::vector< std::string >
split( const std::string& s, const std::string& delimiter );

double 
toDouble( const std::string& s );

std::string 
trim( const std::string& s );

/* Inline functions */
/** 
 * @brief 
 * Confirms a string corresponds to an integer 
 *
 * @param[in] s A string which may or may not be parsable as an integer value.
 * @result Boolean value specifying whether @p s may be parsed as an integer 
 *
 * @details
 * C++ inherits some of the strangeness of C input/output. An example of this
 * undesirable behaviour is how numeric values are read. When told to read an
 * integer from a stream containing something along the lines of *1234abc*, C++
 * will read until the next whitespace character and parse everything up to the
 * first nonconforming character (*a*), returning *1234* and ignoring *abc*. 
 *
 * In NJOY21, functions which call to legacy implementations verify the validity 
 * of input decks before passing them to the Fortran executable (which would 
 * issue a runtime error in this case and crash). To avoid ungraceful failure,
 * values are instead read in as strings and verified using functions like this 
 * one.
 */
inline bool 
isInteger( const std::string& s ){
  return std::regex_match( s, integerPattern_ );
}

/** 
 * @brief 
 * Confirms that all the strings between iterators correspond to an integer
 *
 * @details
 * This uses the isInteger function to confirm the validity of each string
 * individually.
 */
template< typename Iterator >
bool
isInteger( Iterator beginIt, Iterator endIt){
  return std::all_of( beginIt, endIt, 
                      []( const std::string& s ){ return isInteger(s); } );
}

/** 
 * @brief 
 * Confirms that all the strings in a Container correspond to an integer
 *
 * @details
 * This is just syntax sugar when verifying everything in a container.
 */
template< typename Container >
bool
isInteger( const Container& cont ){
  return isInteger( cont.begin(), cont.end() );
}

/**
 * @brief 
 * Confirms a string corresponds to a real number in a Fortran-compatible format 
 *
 * @param[in] s A string which may or may not be parsable as an integer value.
 * @result Boolean value specifying whether @p s may be parsed as double using 
 *         the utility::string::toDouble function.
 *
 * @details 
 * C++ inherits some of the strangeness of C input/output. An example of this
 * undesirable behaviour is how numeric values are read. When told to read an
 * integer from a stream containing something along the lines of *1234abc*, C++
 * will read until the next whitespace character and parse everything up to the
 * first nonconforming character (*a*), returning *1234* and ignoring *abc*. 
 *
 * In NJOY21, functions which call to legacy implementations verify the validity 
 * of input decks before passing them to the Fortran executable (which would 
 * issue a runtime error in this case and crash). To avoid ungraceful failure,
 * values are instead read in as strings and verified using functions like this 
 * one. 
 *
 * In addition, Fortran accepts a wider variety of real number formats than the 
 * std::stod function in the string header of the standard library. This 
 * function recognizes all Fortran-camptable real number formats.
 */
inline bool 
isRealNumber( const std::string& s ){
  return ( std::regex_match( s, realNumberPattern_ ) ||
           std::regex_match( s, infinityPattern_ ) );
}

/**
 * @brief 
 * Confirms that all the strings between iterators correspond to a real
 * number in a Fortran-compatible format.
 *
 * @details
 * This uses the isRealNumber function to confirm the validity of each string
 * individually.
 */
template< typename Iterator >
bool
isRealNumber( Iterator beginIt, Iterator endIt){
  return std::all_of( beginIt, endIt,
                      [](const std::string& s){ return isRealNumber(s); } );
}

/** 
 * @brief 
 * Confirms that all strings in a container are valid real numbers in a
 * Fortran-compatible format.
 *
 * @details
 * This is just syntax sugar if you want to confirm all the values in a
 * container.
 */
template< typename Container >
bool
isRealNumber( const Container& cont ){
  return isRealNumber( cont.begin(), cont.end() );
}

#include "utility/string/unzip.hpp"

} // namespace string

