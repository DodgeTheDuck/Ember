#pragma once

#include "c_common.h"

namespace EmbCL {

	class CStopwatch {

		public:
		CStopwatch( void );
		~CStopwatch( void );

		void Start( void );
		void Stop( void );
		t_real Read( void );
		void Reset( void );

		private:
		t_int64 _freq;
		t_int64 _start;
		t_real _recorded;
		t_int64 _stop;

	};

}