#ifndef WATCHY_circle_H
#define WATCHY_circle_H

#ifdef WATCHY_SIM
    #include "..\..\Watchy.h"
#else // WATCHY_SIM
    #include <Watchy.h>
#endif // WATCHY_SIM

#include "icons.h"
#include "FreeSansBold9pt7b.h"

class Watchycircle : public Watchy{
    using Watchy::Watchy;
    public:
        void drawWatchFace();
        
 };

#endif