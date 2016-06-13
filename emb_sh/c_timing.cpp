
#include "c_timing.h"

namespace Emb {

	CStopwatch::CStopwatch( void ) { };

	void CStopwatch::Start( void ) {
		QueryPerformanceFrequency( &_freq );
		QueryPerformanceCounter( &_start );
	}

	void CStopwatch::Stop( void ) {
		QueryPerformanceCounter( &_stop );
		_recorded = ( _stop.QuadPart - _start.QuadPart ) * 1000.0 / _freq.QuadPart;
	}

	t_real CStopwatch::Read( void ) {
		return _recorded;
	}

	void CStopwatch::Reset( void ) {
		_start.QuadPart = 0;
	}

	CStopwatch::~CStopwatch( void ) { };

}