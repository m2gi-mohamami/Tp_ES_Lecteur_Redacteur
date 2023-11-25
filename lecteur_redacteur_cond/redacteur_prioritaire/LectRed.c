#include "LectRed.h"

void initialiser_lecteur_redacteur( LR_t * lecteur_redacteur){
    lecteur_redacteur->cnt_ecri=0;
    lecteur_redacteur->cnt_lect=0;
    lecteur_redacteur->cnt_ecri_wait=0;
    lecteur_redacteur->cnt_lect_wait=0;
    pthread_mutex_init(&lecteur_redacteur->mutex,NULL);
    pthread_cond_init(&lecteur_redacteur->ecriteur,NULL);
    pthread_cond_init(&lecteur_redacteur->lecteur,NULL);

}

void detruire_lecteur_redacteur( LR_t * lecteur_redacteur){
   pthread_mutex_destroy(&lecteur_redacteur->mutex);
}
void debut_lecture( LR_t * lecteur_redacteur){
   pthread_mutex_lock(&lecteur_redacteur->mutex);
   lecteur_redacteur->cnt_lect_wait++;
   while (lecteur_redacteur->cnt_ecri!=0 || lecteur_redacteur->cnt_ecri_wait!=0)
   {
    pthread_cond_wait(&lecteur_redacteur->lecteur,&lecteur_redacteur->mutex);
   }
   lecteur_redacteur->cnt_lect_wait--;
   lecteur_redacteur->cnt_lect+=1;
   pthread_mutex_unlock(&lecteur_redacteur->mutex);

}

void fin_lecture( LR_t * lecteur_redacteur ){
   pthread_mutex_lock(&lecteur_redacteur->mutex);
   lecteur_redacteur->cnt_lect-=1;
   if(lecteur_redacteur->cnt_lect==0 && lecteur_redacteur->cnt_ecri_wait!=0)
      {
         lecteur_redacteur->cnt_ecri_wait--;
         lecteur_redacteur->cnt_ecri++;
         pthread_cond_signal(&lecteur_redacteur->ecriteur);
      }
   pthread_mutex_unlock(&lecteur_redacteur->mutex);
}

void debut_redaction( LR_t * lecteur_redacteur){
   pthread_mutex_lock(&lecteur_redacteur->mutex);

  if(lecteur_redacteur->cnt_lect!=0 ||lecteur_redacteur->cnt_ecri!=0)
   { 
    lecteur_redacteur->cnt_ecri_wait++;
    pthread_cond_wait(&lecteur_redacteur->ecriteur,&lecteur_redacteur->mutex);
   }else{
    lecteur_redacteur->cnt_ecri+=1;
   }
  
   pthread_mutex_unlock(&lecteur_redacteur->mutex);
}
void fin_redaction( LR_t * lecteur_redacteur){ 
   pthread_mutex_lock(&lecteur_redacteur->mutex);
   lecteur_redacteur->cnt_ecri-=1;
   if(lecteur_redacteur->cnt_ecri_wait!=0){
         lecteur_redacteur->cnt_ecri_wait--;
         lecteur_redacteur->cnt_ecri++;
         pthread_cond_signal(&lecteur_redacteur->ecriteur);

   }else{
      pthread_cond_broadcast(&lecteur_redacteur->lecteur);
   }
   pthread_mutex_unlock(&lecteur_redacteur->mutex);
  }