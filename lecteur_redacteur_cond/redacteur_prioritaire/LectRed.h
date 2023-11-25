//
//  LectRed.h
//  LectRed
//
//  Created by Vania Marangozova-Martin on 14/11/2017.
//  Copyright © 2017 Vania Marangozova-Martin. All rights reserved.
//

#ifndef LectRed_h
#define LectRed_h
#include <pthread.h>
typedef struct LR_s {
    pthread_cond_t lecteur;
    pthread_cond_t ecriteur;
    pthread_mutex_t mutex;
    int cnt_lect;
    int cnt_ecri;
    int cnt_lect_wait;
    int cnt_ecri_wait;

}LR_t ;

void initialiser_lecteur_redacteur( LR_t * );
void detruire_lecteur_redacteur( LR_t * );
void debut_lecture( LR_t * );
void fin_lecture( LR_t * );
void debut_redaction( LR_t * );
void fin_redaction( LR_t * );
#endif /* LectRed_h */
