
#include "cfg.h"

namespace cio{

void* capture(int r, int c, int h, int w);
void restore(int r, int c, int h, int w, CDirection d, void* b);
void release(void**);

}// end of namespace cio