#include <stdio.h>
#include <stdlib.h>




int main(int argc, char *argv[]) {
	
	unsigned char address [100], addressout [100];
	unsigned char data [76800];
	unsigned char vth, vtl, i;
	unsigned int x = 0, y = 0, sizeoffseting = 0, offsetbmp = 0, vector = 0, line = 0, Height, Width;
	
	int num;
	FILE *fptr;
	FILE *fptrout;
	
	//C:\PROTEUS\1.bmp	
	
	// Ask for file location
   	printf("Local do arquivo BitMap:  ");
   	scanf("%99s", address);
   	
   	
	// Open the file
   	fptr = fopen(address,"rb");
   	
   	if(fptr == NULL)
   	{
      	printf("Error! Aquivo não encontrado!");   
      	exit(1);             
   	}
   	
   	// Ask for location and name of the new file
   	printf("\nLocal do arquivo convertido:  ");
   	scanf("%99s", addressout);
   	
   	// Create the new file
	fptrout = fopen(addressout,"w");
   	
   	if(fptrout == NULL)
   	{
      	printf("Error! Aquivo não pode ser gerado!");   
      	exit(1);             
   	}
   	
   	
   	
   	fread(&data, sizeof(data), 1, fptr); 
   	
   	// Check if image is 8 bits format
   	if(data [0x1C] != 8) 
	   {
		printf("Formato de imagem incompativel com a saida");
		getchar();
		return 0;
	}
	
	Width = data [0x12]+(data [0x13] << 8);
	if(Width > 320) 
	{
		printf("Formato de imagem incompativel com a saida");
		getchar();
		return 0;
	}
	
	Height = data [0x16]+(data [0x17] << 8);
	if(Height > 240) 
	{
		printf("Formato de imagem incompativel com a saida");
		getchar();
		return 0;
	}
	
	fprintf(fptrout,"{\n%d,\n", Width);
	fprintf(fptrout,"%d,\n", Height);
	
	offsetbmp = data [0x0A]+(data [0x0B] << 8);
	//printf("%d,\n", offsetbmp);
	//getchar();
	
	sizeoffseting = (Width * Height) + offsetbmp;
   	
   	
	for (x = offsetbmp; x <= sizeoffseting; x ++)	
	{
		if(data[x] == data[x+1]) vector ++;	
		else
		{

			vector ++;
			vth = vector / 0xff;
			vtl = vector % 0xFF; 
			if(vth != 0) for(i = 0; i < vth; i++) fprintf(fptrout,"255, %d, ", data[x]);	
			if(vtl != 0) fprintf(fptrout,"%d, %d, ",vtl, data[x]);
			line++;
			vector = 0;

		}
		if(line == 20)
		{
			line =0;
			fprintf(fptrout,"\n");
		}					
	}
	
	fprintf(fptrout,"00\n};");
	fclose(fptrout);
	fclose(fptr); 
	return 0;
}
