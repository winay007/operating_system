#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>



pthread_mutex_t mutext,writer;
int rc=0;
int shared_resource=0;

void *readerfn(void *arg){

	int id=*((int *)arg);
	//printf("\n Reader trying to read  %d",id);
	
	pthread_mutex_lock(&mutext);
	
	rc++;
	if(rc==1)
		pthread_mutex_lock(&writer);
	
	pthread_mutex_unlock(&mutext);

	printf("\n Reader %d  trying to read %d",id,shared_resource);
	usleep(1000000);
	pthread_mutex_lock(&mutext);
	rc--;
	
	if(rc==0)
		pthread_mutex_unlock(&writer);
	
	pthread_mutex_unlock(&mutext);
	
	pthread_exit(NULL);

}

void *writerfn(void *arg){

	int id=*((int *)arg);
	
	pthread_mutex_lock(&writer);
	shared_resource=rand()%100;
	printf("\n Writer id %d trying to writer:%d",id,shared_resource);
	pthread_mutex_unlock(&writer);
	usleep(1000000);
	pthread_exit(NULL);
}

int main(){
	int wc=5;
	int rc=10;
	// init mutext
	
	pthread_mutex_init(&writer,NULL);
	pthread_mutex_init(&mutext,NULL);
	
	pthread_t readerThread[rc];
	pthread_t writerThread[wc];	
	
	int writerId[wc];
	int readerId[rc];
	
	for(int i=0;i<wc;i++){
		writerId[i]=i+1;
		pthread_create(&writerThread[i],NULL,writerfn,&writerId[i]);
		
	}
	
	for(int i=0;i<rc;i++){
		readerId[i]=i+1;
		pthread_create(&readerThread[i],NULL,readerfn,&readerId[i]);
	}


	for(int i=0;i<wc;i++)
		pthread_join(writerThread[i],NULL);

	for(int i=0;i<rc;i++)
		pthread_join(readerThread[i],NULL);
		
	//pthread_mutex_destroy(&mutext);
	//pthread_mutex_destroy(&writer);
	
	return 0;
	
}
