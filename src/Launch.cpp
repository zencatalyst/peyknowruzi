// PeykNowruzi, basic implementation ( cross platform )
// repo available at https://github.com/zencatalyst/magical-creations


#include "Scripts.h"


namespace pynz = peyknowruzi;


inline static void launch( )
{
	pynz::runScripts( );
}

int main( [[ maybe_unused ]] int argc, [[ maybe_unused ]] char* argv[] )
{
	launch( );

	return 0;
}
