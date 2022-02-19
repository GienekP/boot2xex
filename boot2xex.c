/*--------------------------------------------------------------------*/
/* ATARI boot file to XEX - GienekP                                   */
/*--------------------------------------------------------------------*/
#include <stdio.h>
/*--------------------------------------------------------------------*/
void boot2xex(const char *fni, const char *fno)
{
	unsigned int i,fsize;
	unsigned int start, end;
	FILE *fi,*fo;
	fi=fopen(fni,"rb");
	if (fi)
    {
		printf("Open \"%s\"\n",fni);
		fseek(fi,0,SEEK_END);
		fsize=ftell(fi);
		fseek(fi,0,0);
		printf("File size: %i bytes\n",fsize);
		fo=fopen(fno,"wb");
		if (fo)
		{
			printf("Save \"%s\"\n",fno);
			fgetc(fi);
			fgetc(fi);
			start=(fgetc(fi)&0xFF);
			start|=((fgetc(fi)&0xFF)<<8);
			start+=6;
			printf("Load adress = $%04X\n",start);
			fgetc(fi);
			fgetc(fi);		
			fsize-=6;
			end=start+fsize-1;
			printf("End adress = $%04X\n",end);		
			fputc(0xFF,fo);
			fputc(0xFF,fo);
			fputc(0xE0,fo);
			fputc(0x02,fo);
			fputc(0xE1,fo);
			fputc(0x02,fo);		
			fputc((start&0xFF),fo);
			fputc(((start>>8)&0xFF),fo);
			printf("Run adress = $%04X\n",start);
			fputc((start&0xFF),fo);
			fputc(((start>>8)&0xFF),fo);
			fputc((end&0xFF),fo);
			fputc(((end>>8)&0xFF),fo);		
			for (i=0; i<fsize; i++) {fputc(fgetc(fi),fo);};	
			fclose(fo);
		}
		else
		{
			printf("Save Error \"%s\"\n",fno);
		};
		fclose(fi);
	}
	else
	{
		printf("Open Error \"%s\"\n",fni);
	};
}
/*--------------------------------------------------------------------*/
int main(int argc, char *argv[])
{
	printf("boot2xex - GienekP\n");
	switch (argc)
	{
		case 3:
		{
			boot2xex(argv[1],argv[2]);
		} break;
		default:
		{
			printf("use:\n");
			printf("   bootxex file.atariboot file.xex\n");	
		} break;
	};
	return 0;
}
/*--------------------------------------------------------------------*/