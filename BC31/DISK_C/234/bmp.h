#ifndef bmp_h
#define bmp_h

void selectpage(register char page);
unsigned char set_SVGA_mode(int vmode);
unsigned int get_SVGA_mode(void);
void set_SVGA_palette(unsigned char r[],unsigned char g[], unsigned char b[]);
void readbmp(char *p);
 
#endif