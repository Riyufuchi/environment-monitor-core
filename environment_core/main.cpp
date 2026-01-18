extern "C"
{
#include "src/sos/sos.h"
}

#include "src/output_modules/traffic_light.h"

int main()
{
  sos_init();
  while (1)
    sos_task();
  return 0;
}
