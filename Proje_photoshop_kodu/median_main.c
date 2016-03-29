#include <stdio.h>
#include <stdlib.h>
#include<limits.h>
#include "pgm.h"

#define N_IMAGES 9


/* TODO: Istediginiz bir siralama algoritmasiyla pixels dizisini
 * siralayin ve ortanca elemanin degerini geri dondurun. */
 
/************************ Insertion Sort****************************/

void insertion_sort(unsigned char *array, int size) {

  int i;
  for (i = 1; i < size; ++i) {
    int pivot = array[i];
    int j;
    for (j = i; j > 0; --j) {
      if (pivot < array[j - 1]) {
        array[j] = array[j - 1];
      } else break;
    }
    array[j] = pivot;
  }
}
unsigned char sort_and_get_median(unsigned char *pixels, int size) {
	int i,j;

	insertion_sort(pixels,size);
	
		return pixels[(size-1)/2];

}

int main(int argc, const char *argv[])
{
    int i;
    
    /* 9 adet resim var */
    PGMInfo images[N_IMAGES];
    
    /* Temizlenmis resim icin baslik kismini hazirlayalim */
    PGMInfo filtered = { "P5", "# \n", 495, 557, 255, NULL, 0};
    
    /* Temizlenmis resmin pikselleri icin yer ayiralim */
    filtered.pixels = malloc(filtered.width * filtered.height);
  
    /* Resimleri sirayla images[]'in ilgili elemanina okuyun.
     * Resimler median_images/ dizini altinda 1'den 9'a kadar adlandirilmis
     * olup uzantilari pgm'dir. Ornek: 1.pgm, 2.pgm, .. */
    for (i = 0; i < N_IMAGES; ++i) {
        char image_file[64];
        
        /* TODO: image_file'in icerisine okunacak dosya adini yazin (ipucu: sprintf()) */
        sprintf(image_file,"./median_images/%d.pgm",i+1); 
        
        /* TODO: Resim dosyasini pgm_read() ile images[i] icerisine okuyun. */
        images[i] = pgm_read(image_file);

        /* Hata olusursa programi sonlandir */
        if (images[i].error > 0) {
            pgm_print_error(images[i]);
            exit(1);
        }

        /* Bilgileri ekrana yazdir */
        pgm_print_header(images[i]);
    }

    /* TODO: Median filtreleme */
    int j;
    int k;
    unsigned char gecici[9]; //pikseller unsigned char türünden oldugundan dolayı böyle bi dizi oluşacak
    for(j=0;j<images[0].width*images[0].height;j++){
    for (k=0;k<N_IMAGES;k++) {
              gecici[k] = images[k].pixels[j]; // her resmin aynı pikselindeki degeri kaydettik
    }
    
    filtered.pixels[j] = sort_and_get_median(gecici,N_IMAGES); // o degerleri sıralayıp ortancasını filteredi'in j. pikseline yazdık
    }
   
    /* Temizlenmis resmi kaydedin. */
    pgm_write("median_images/filtered.pgm", filtered);
    
    /* TODO: Temizlenmis resmin piksel alanini free() edin */
    free(filtered.pixels);

    /* TODO: Tum fotograflarin piksel alanlarini free() edin */
    for(i=0;i<9;i++)
    free(images[i].pixels);


    return 0;
}
