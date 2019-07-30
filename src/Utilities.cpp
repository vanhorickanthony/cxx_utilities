//============================================================================
// @name        : utils.cc
// @author      : Anthony Van Horick
// @date        : 2019-07-30
// @description :
//============================================================================

#include <iostream>

#include <string>

#include <vector>
#include <map>

#include <iostream>
#include <type_traits>
#include <cstdint>


#include "./utils.hh"


int main()
{

	std::vector< int > vec_1 = {0, 1};
	std::vector< int > vec_2 = {0, 1};
	std::vector< int > vec_3 = {1, 2, 3};
	std::map< std::vector<int>, std::map<int, char> > map_1
	=
	{
			{ {1, 2, 3}, { {1, 'a' } , { 2, 'b' }, { 3, 'c' } } },
			{ {1, 2, 3}, { {1, 'a' } , { 2, 'b' }, { 3, 'c' } } }
	};
	std::map< std::vector<int>, std::map<int, char> > map_2
	=
	{
			{ {1, 2, 3}, { {1, 'a' } , { 2, 'b' }, { 3, 'c' } } },
			{ {1, 2, 3}, { {1, 'a' } , { 2, 'b' }, { 3, 'c' } } }
	};
	std::cout << _compare(vec_1, vec_2) << std::endl;
	std::cout << _compare(vec_1, vec_3) << std::endl;
	std::cout << _compare('a', 'b') << std::endl;
	std::cout << _compare(map_1, map_2) << std::endl;
	return 0;

}
