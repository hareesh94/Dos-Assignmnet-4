#include <xinu.h>

typedef struct msg{
topic16 topic;
int *hand[256];
int subsc;
}msg1;

msg1 t[256];
pid32 p[256][2];
int *arr[256];

//Subscribe system call

syscall subscribe(
	  topic16 topic,		                 /* topic ID	*/
	  void (*handler)(topic16,uint32)		/* pointer to handler function	*/
	)
{
	intmask	mask;			
        int i=0;
        int j=0;
        int k=0;
        int gid=((topic)&(0xFF00));
       mask = disable();
	int tid=((topic)&(0x00FF));
        for(i=0;i<256;i++){	
 	if(t[i].topic==NULL || t[i].topic==topic){
        if(t[i].topic==NULL)
        t[i].topic=topic;
	for(k=0;k<256;k++)      
	if(t[i].hand[k]==NULL)  
	t[i].hand[k]=handler;
 	t[i].subsc++;
	}
	}	
	for(i=0;i<256;i++){
        if(p[i][0]==NULL)
        {
	p[i][0]=currpid;
	p[i][1]=topic;
	}
	}
	printf("process subscribed");
	restore(mask);		
	return OK;
}


//Publish sysytem call

syscall publish(topic16 topic, uint32 data)
{
intmask mask;
int i=0;
int j=0;
mask=disable();
for(i=0;i<256;i++){
if(t[i].topic==topic)
        for(j=0;j<256;j++){
if(t[j].hand[i]!=NULL){     
printf("broker called");
}
}
}

restore(mask);
return OK;
}

//Unsubscribe system call

syscall unsubscribe(topic16 topic)
{
int mask;
int i=0;
int j=0;
int tid=((topic)&(0x00FF));
mask=disable();
for(i=0;i<256;i++){
if(currpid==p[i][0])
{
p[i][0]=NULL;
p[i][1]=NULL;
}
}
printf("process unsubscribed");
restore(mask);
return OK;
}















