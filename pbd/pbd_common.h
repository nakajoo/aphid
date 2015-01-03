#ifndef PBD_COMMON_H
#define PBD_COMMON_H
#include <AllMath.h>
namespace pbd {
struct Spring {
		unsigned p1, p2;
		float rest_length;
		float Ks, Kd;
		int type;
	};
}
#endif        //  #ifndef PBD_COMMON_H

