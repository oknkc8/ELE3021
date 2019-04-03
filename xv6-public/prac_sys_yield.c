#include "types.h"
#include "defs.h"
//#include "proc.h"
#include "mmu.h"
#include "param.h"

void
callyield(void){
	yield();
}

void
sys_callyield(void){
	return callyield();
}
