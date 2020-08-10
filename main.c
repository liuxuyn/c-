#include "allhead.h"

int main()
{
    int page=0;
    int gd=VGA,gm=VGAHI;
    initgraph(&gd,&gm,"C:\\borlandc\\bgi");
    mouseinit();

    while(1)
    {
        switch(page)
        {
            case 0:
                page=fbegin();
                break;

            case 1:
                page=edit();
                break;

            default:
                {
                    delay(50);
                    exit(0);
                }
                break;
        }
    }
}
