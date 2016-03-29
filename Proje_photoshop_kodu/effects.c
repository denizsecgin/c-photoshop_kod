#include "effects.h"

void effect_random_noise(unsigned char *pixels, int width, int height) {
    int nr_noisy_pixel = (width * height) / 5; // %5 oraninda noise ekle
    int i;

    for (i = 0; i < nr_noisy_pixel; ++i ) {
        int which_pixel = (rand() % (width * height));
        pixels[which_pixel] = (rand() % 256);
    }
}

void effect_smooth(unsigned char *pixels, int width, int height) {
    int i;
    for (i = 0; i < width * height -1; ++i) {
        pixels[i] = ((pixels[i] + pixels[i+1]) / 2) % 256;
    }
}

/* TODO: Invert efekti her pikselin degerinin tumleyenini o pikselin
 * yeni degeri olarak belirler.
 */
void effect_invert(unsigned char *pixels, int width, int height) {
int i;
for(i=0;i<width*height;i++){
pixels[i]=255-pixels[i];
}

}

/* TODO: Verilen bir esik degerin altinda kalan pikselleri siyah,
 * uzerinde kalanlari ise beyaz yaparak 2 renkli bir resim olusturur.
 */
void effect_threshold(unsigned char *pixels, int width, int height, int threshold) {
int i;
for(i=0;i<width*height;i++){
if(pixels[i]<threshold)
pixels[i]=0;
if(pixels[i]>threshold)
pixels[i]=255;
}
}

