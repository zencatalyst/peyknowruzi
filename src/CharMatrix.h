
#pragma once

#include "Util.h"
#include <iostream>
#include <vector>
#include <memory>
#include <unordered_set>


class CharMatrix
{
public:
	inline CharMatrix( );
	inline CharMatrix( const int& Y_DIM, const int& X_DIM, const char FILL_CHARACTER = ' ' );
	inline ~CharMatrix( ) = default;
	inline CharMatrix( const CharMatrix& ) = delete;
	inline CharMatrix& operator=( const CharMatrix& ) = delete;
	inline CharMatrix( CharMatrix&& rhs ) noexcept;
	inline CharMatrix& operator=( CharMatrix&& rhs ) noexcept;

	inline const int& getY_DIM( ) const;
	inline const int& getX_DIM( ) const;
	inline std::vector< std::vector<char> >& getCharacterMatrix( );
	inline void setCharacterMatrix( const std::vector<int>& coordsOfChar );
	inline bool validateUserEnteredCoords( const char (&str_userEnteredCoords)[169],
											std::vector<int>& int_userEnteredCoords );

	inline int getNumOfInputLines( );
	inline void getCoords( );
	inline void writeToOutput( );

	inline static char findCharType( const std::vector<int>& coordsOfChar );
	inline static auto initialize( );
	static void launch( );

private:
	int _Y_DIM;
	int _X_DIM;
	std::vector< std::vector<char> > _characterMatrix;
	inline static const std::unordered_set<char> CHAR_SET { '/', '\\', '|', '-' };
};
