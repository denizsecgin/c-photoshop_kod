#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include<limits.h>

/* Kendi baslik dosyalarimizi include ediyoruz */
#include "pgm.h"
#include "effects.h"

/* PROGRAMIN ORNEK KULLANIMI:
 *
 *      $ ./pgm_efekt
 *      Usage: ./pgm_efekt <invert|binarize|noise|smooth> <PGM image 1> <PGM image 2> ... <PGM image N>
 *
 *      $ ./pgm_efekt invert effect_images/man_ascii.pgm
 *      (Invert efekti uygulanan resim effect_images/man_ascii.pgm.invert olarak kaydedilir)
 */

int main(int argc, char *argv[])
{
    /* TODO: Program efekt adi ve EN AZ 1 resim dosyasi olmak uzere EN AZ
     * 2 arguman istemektedir. Bu bilgiye gore asagidaki if()'in icerisini
     * doldurun.
     */
    if (argc<=2) {
        fprintf(stderr, "Usage: %s <invert|binarize|noise|smooth> <PGM image 1> <PGM image 2> ... <PGM image N>\n", argv[0]);
        return 1;
    }

    int i;
    /* Komut satirindan gelen efekt adi */
    char *effect_name = argv[1];

    /* TODO: Bazi efektlerin ihtiyac duyabilecegi rand() rassal
     * sayi uretecini seed edin. */

    srand(time(NULL));


    /* argv[0]:     Programin adi
     * argv[1]:     Efekt cesidi: invert, binarize, noise, smooth
     * argv[2] ...  argv[argc-1]: Dosya adi veya adlari
     */

    /* Butun argumanlari gez. Her biri bir resim dosyasi adi */
    for (i = 2; i < argc; ++i) {

        /* TODO: PGM dosyasini oku */


    	PGMInfo pgm_info;
	
    	pgm_info = pgm_read(argv[i]);//????

        /* Hata olduysa ekrana hata mesajini yazdir */
        if (pgm_info.error > 0) {
            pgm_print_error(pgm_info);
        }

        /* Hata yoksa resmin baslik bilgisini ekrana yazdir,
         * resme efekt uygula ve yeni dosyaya kaydet. */
        else {
            /* Yeni bir string olustur. Bu string efekt uygulanmis
             * dosyanin adini tutacaktir. */
            char new_filename[64];
            sprintf(new_filename, "%s_%s", argv[i], effect_name);

		

            /* PGM basligini ekrana yazdir. */
            pgm_print_header(pgm_info);

            /* Hangi efekt istendiyse ilgili fonksiyon cagiriliyor */
            if (strcmp(effect_name, "invert") == 0) {
                effect_invert(pgm_info.pixels, pgm_info.width, pgm_info.height);
            } else if (strcmp(effect_name, "binarize") == 0) {
                effect_threshold(pgm_info.pixels, pgm_info.width, pgm_info.height, 150);
            } else if (strcmp(effect_name, "noise") == 0) {
                effect_random_noise(pgm_info.pixels, pgm_info.width, pgm_info.height);
            } else if (strcmp(effect_name, "smooth") == 0) {
                effect_smooth(pgm_info.pixels, pgm_info.width, pgm_info.height);
            }

            /* TODO: Yeni PGM dosyasini olusturun. Eger basarisiz olursa
             * ekrana yazdirin. */
	
		pgm_write(new_filename,pgm_info);

            if (pgm_info.error > 0) {

            	pgm_print_error(pgm_info);

            }
 //selam

            /* TODO: pgm_info'daki pixels dizisini free() etmeliyiz. */

            free(pgm_info.pixels);

        }
    }
    return 0;
}
