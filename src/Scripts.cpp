
// PeykNowruzi - Basic ASCII-Art Generator
// Copyright (C) 2021-2022 Kasra Hashemi

/*

 This file is part of PeykNowruzi.

 PeykNowruzi is free software: you can redistribute it and/or modify it
 under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License,
 or (at your option) any later version.

 PeykNowruzi is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty
 of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 See the GNU General Public License for more details.

 You should have received a copy of the GNU General Public License along
 with PeykNowruzi. If not, see <https://www.gnu.org/licenses/>.

*/


#include "Scripts.hpp"
#include "CharMatrix.hpp"
#include "Log.hpp"
#include "Util.hpp"
#include "pch.hpp"


namespace peyknowruzi
{

void runScripts( )
{
	// runScript( );

    using CharMatrix_1001 = pmr::CharMatrix<1001, std::uint32_t, char>;

    static constexpr CharMatrix_1001::size_type Y_AxisLen { 36 };
    static constexpr CharMatrix_1001::size_type X_AxisLen { 168 };
    static constexpr CharMatrix_1001::value_type fillCharacter { ' ' };

    static_assert( Y_AxisLen >= CharMatrix_1001::min_allowed_y_axis_len &&
                   Y_AxisLen <= CharMatrix_1001::max_allowed_y_axis_len,
                   "Y_AxisLen can not be greater than max_allowed_y_axis_len or "
                   "less than min_allowed_y_axis_len" );

    static_assert( X_AxisLen >= CharMatrix_1001::min_allowed_x_axis_len &&
                   X_AxisLen <= CharMatrix_1001::max_allowed_x_axis_len,
                   "X_AxisLen can not be greater than max_allowed_x_axis_len or "
                   "less than min_allowed_x_axis_len" );

    constexpr size_t buffer_size { Y_AxisLen * X_AxisLen + 500 };
    static auto buffer { std::array< std::byte, buffer_size >{ } };
    const auto buffer_address { buffer.data( ) };
    static std::pmr::monotonic_buffer_resource rsrc { buffer_address, buffer_size };

    static auto matrix { CharMatrix_1001( Y_AxisLen, X_AxisLen , fillCharacter, &rsrc ) };

    matrix.getCoords( matrix.getNumOfInputLines( ) );
    matrix.print( );

    /*constexpr CharMatrix_1001::size_type Y_AxisLen { 36 };
    constexpr CharMatrix_1001::size_type X_AxisLen { 168 };
    constexpr CharMatrix_1001::value_type fillCharacter { ' ' };
    constexpr bool isFullInputModeEnabled { false };*/

    // CharMatrix_1001::runScriptForStackAllocated<Y_AxisLen, X_AxisLen, fillCharacter, isFullInputModeEnabled>( );
}

void exit_handler( )
{
#if PN_DEBUG == 1
	using std::string_literals::operator""s;

	log( "\nProgram execution ended in "s +
		 /*( std::stringstream { } << util::retrieve_current_local_time( ) ).str( ) +*/
		 "\n"s );
#endif
}

const int flag { std::atexit( exit_handler ) };

}
