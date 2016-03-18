#include <algorithm>  
#include <cctype>     

#include "utility/string.hpp"

/**
 * @brief
 * Removes leading and following whitespace from an input string.
 *
 * @param[in] s A string which may have leading or trailing whitespaces.
 * @result A copy of @p s with any leading and trailing whitespace removed
 *
 * @details
 * The trim operation is completed without the producing intermediate (and 
 * redundant) copies seen in many implementations online. Iterators are
 * set the the first and last non-whitespace character positions in the input 
 * string and the return string is generated using the iterator range string 
 * constructor.
 */
std::string 
utility::string::trim(const std::string& s){
  auto wsfront = std::find_if_not( s.begin(),
				   s.end(),
				   [](int c){return std::isspace(c);});
  auto wsback = std::find_if_not( s.rbegin(),
				  s.rend(),
				  [](int c){return std::isspace(c);}).base(); 
  return ( wsback <= wsfront ? 
	   std::string() : 
	   std::string( wsfront, wsback )
	   );
}
