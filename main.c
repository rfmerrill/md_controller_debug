// Built against SGDK 1.62
// public domain.


#include <genesis.h>

static u16 TH_CONTROL_PHASE(vu8 *pb)
{
    u16 val;

    *pb = 0x00; /* TH (select) low */
    asm volatile ("nop");
    asm volatile ("nop");
    val = *pb;

    *pb = 0x40; /* TH (select) high */
    val <<= 8;
    val |= *pb;

    return val;
}

int main()
{
    vu8 *pb;
    u16 v[4];

    char buf[20] = {0};
    u8 i = 0, j = 0;
    pb = (vu8 *)0xa10003;


    while(1)
    {
        JOY_init();

        pb = (vu8 *)0xa10003;
        SYS_disableInts();
        v[0] = TH_CONTROL_PHASE(pb);
        v[1] = TH_CONTROL_PHASE(pb);
        v[2] = TH_CONTROL_PHASE(pb);
        v[3] = TH_CONTROL_PHASE(pb);
        SYS_enableInts();

        VDP_drawText("P1", 6, 8);
        VDP_drawText("P2", 6, 14);

        for(i = 0; i < 4; i++)
        {
            for (j = 0; j < 8; j++)
            {
                if (v[i] & (1<<(15-j)))
                    buf[j] = '1';
                else
                    buf[j] = '0';
            }
            buf[8] = ' ';
            for (j = 8; j < 16; j++)
            {
                if (v[i] & (1<<(15-j)))
                    buf[j+1] = '1';
                else
                    buf[j+1] = '0';
            }
            VDP_drawText(buf, 10, 8+i);
        }


        pb = (vu8 *)0xa10005;
        SYS_disableInts();
        v[0] = TH_CONTROL_PHASE(pb);
        v[1] = TH_CONTROL_PHASE(pb);
        v[2] = TH_CONTROL_PHASE(pb);
        v[3] = TH_CONTROL_PHASE(pb);
        SYS_enableInts();

        for(i = 0; i < 4; i++)
        {
            for (j = 0; j < 8; j++)
            {
                if (v[i] & (1<<(15-j)))
                    buf[j] = '1';
                else
                    buf[j] = '0';
            }
            buf[8] = ' ';
            for (j = 8; j < 16; j++)
            {
                if (v[i] & (1<<(15-j)))
                    buf[j+1] = '1';
                else
                    buf[j+1] = '0';
            }
            VDP_drawText(buf, 10, 14+i);
        }


        SYS_doVBlankProcess();
    }
    return (0);
}
