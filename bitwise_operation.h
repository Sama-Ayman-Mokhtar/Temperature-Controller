#define Set_bit(Reg,bit) {Reg|=(1<<bit);}
#define Clear_bit(Reg,bit) {Reg &= ~(1<<bit);}
#define Get_Bit(Reg,bit) ((Reg >> bit) & 1)
#define Toggle_Bit(Reg,bit) {Reg^= (1<<bit);}