#pragma once

#include "c_defs.h"

namespace Emb {

	class EMB_SH_API CStopwatch {

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