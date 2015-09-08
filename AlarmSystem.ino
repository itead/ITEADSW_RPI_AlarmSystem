#include <SIM900.h>
#include <sms.h>
#include <call.h>
#include<sys/types.h>
#include<sys/wait.h> 
#include <signal.h>
#include<unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>





#define GSM_POWER_PIN 11
#define STATUS_ALARM GPIO4

SIMCOM900 gsm(GSM_POWER_PIN,Serial0);
SMSGSM sms(gsm);
CallGSM call(gsm);

boolean started=false;

byte ret;
char DTMF_char='_';
pid_t fd;
pid_t md;
pid_t ppid;
int cfd;
int recbyte;
int sin_size;
char buffer[1024] = {0};
struct sockaddr_in s_add, c_add;
unsigned short portnum = 0x8888;





void setup(void)
{
     //Serial connection.
     pinMode(STATUS_ALARM,INPUT);
     printf("GSM Shield Call Test\n");
     printf("Start...\n");
     if (gsm.begin(9600)) 
     {
          printf("\nstatus=READY\n");
          started=true;
     } 
     else
     { 
        printf("\nstatus=IDLE\n");
     }
     if(!started) 
     {
        printf("setup error,Halt now...");
        while(1)delay(10000);
     }
     
     cfd = socket(AF_INET, SOCK_STREAM, 0);
     if(-1 == cfd)
     {
             printf("socket fail ! \r\n");
             //return -1;
     }
 
     printf("socket ok !\r\n");
 
     bzero(&s_add,sizeof(struct sockaddr_in));
     s_add.sin_family=AF_INET;
     s_add.sin_addr.s_addr= inet_addr("172.16.5.154");
     s_add.sin_port=htons(portnum);
     printf("s_addr = %#x ,port : %#x\r\n",s_add.sin_addr.s_addr,s_add.sin_port);
 
     if(-1 == connect(cfd,(struct sockaddr *)(&s_add), sizeof(struct sockaddr)))
     {
             printf("connect fail !\r\n");
             //return -1;
     }
 
     printf("connect ok !\r\n");
	
    
};

void loop(void)

{   
    int times = 0;
    int val = 1;
    int timer = 40;
    int log = 0; 
    int press = 0; 
    int fork_log = 1;
    printf("Please press emergency call button\n");
    if (0 == digitalRead(STATUS_ALARM))
    {
        delay(5);  
        if (0 == digitalRead(STATUS_ALARM))
        {
            call.Call("13169939943");
            call.SetDTMF(1);
            ret = call.CallStatus();
            while (timer > 0)
            {
                ret = call.CallStatus();
                printf("%d\n",ret);
                timer--;
                delay(1000);
                
                if( ret = call.CallStatus() == 10 && fork_log == 1 )
                {	
                    fork_log = 0;
                    timer = 0;
                    fd = fork();
                    if (fd == 0)
                    {
                        while(1)
                        {
                            printf("\nSound an alarm\n\n\n");
                            execlp("mplayer", "ao","/home/pi/Segnix/AlarmSystem/24.mp3", NULL);
                        }   
                    }
                    else
                    {
                        ppid = fork();
                        if(ppid == 0)
                        {   
                            while (1)
                            {
                                DTMF_char = call.DetDTMF();
                                ret = call.CallStatus();
                                printf("%d\n",ret);
                                if (DTMF_char == '1')
                                {
                                    int kill_ret = kill(fd ,SIGKILL);
                                    if (!kill_ret)
                                    {                        
                                        printf("\nYou press 1 xxxxxx\n");
                                        md = fork();
                                        if (md == 0)
                                        {
                                            while(1)
                                           {
                                                if (ret = call.CallStatus() == 0)
                                                {
                                                    system("killall -9 mplayer");
                                                    exit(12);
                                                }
                                            }  
                                        }
                                        else
                                        {
                                            execlp("mplayer", "ao","/home/pi/Segnix/AlarmSystem/25.mp3", NULL);
                                        }
                                    }
                                }
                                else if (DTMF_char == '2')
                                {
                                    int kill_ret = kill(fd ,SIGKILL);
                                    if (!kill_ret)
                                    {                        
                                        printf("\nYou press 2 xxxxxx\n");
                                        md = fork();
                                        if (md == 0)
                                        {
                                            while(1)
                                           {
                                                if (ret = call.CallStatus() == 0)
                                                {
                                                    system("killall -9 mplayer");
                                                    exit(12);
                                                }
                                            }  
                                        }
                                        else
                                        {
                                            execlp("mplayer", "ao","/home/pi/Segnix/AlarmSystem/26.mp3", NULL);
                                        }
                                    }
                                }  
                                else if (ret = call.CallStatus() == 0)
                                {
                                    
                                    kill(fd ,SIGKILL);
                                    kill(getpid() ,SIGKILL); 
                                    call.HangUp();
                                }
                                else 
                                {
                                    delay(10);
                                    times=times+1;
                                    printf("%d\n",times);
                                    if (times > 10)
                                    {
                                        printf("\n Will be automatically suspended \n");
                                        kill(fd ,SIGKILL);
                                        kill(getpid() ,SIGKILL);
                                        call.HangUp();
                                    }
                                }
                            }
                        }
                    }
                   
                    waitpid(ppid, NULL,0);
                    call.HangUp();
                }
                else if (ret = call.CallStatus() == 0)
                {
                    timer = 0;
                }
            }
            if(ret = call.CallStatus() == 0 && fork_log == 1)
            {
                ret = sms.SendSMS("13169939943","Your house is on fire!");
                if ( ret == 1) 
                {
                    printf("Send OK\n");
                    delay(5000);
                } else 
                {
                    printf("Send ERR. ret = %d\n",ret);
                    delay(3000);
                }   
            }
            memset(buffer, 0, 100);
    	    sprintf(buffer, "Your house is on fire! \r\n");
            send(cfd, buffer, strlen(buffer), 0);
        }
    }
   delay(100);
}

