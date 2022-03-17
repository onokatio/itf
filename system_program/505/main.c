#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/time.h>
#include <time.h>

volatile sig_atomic_t is_siged = 0;

void myfunc(){
	struct itimerval itimer;
	itimer.it_value.tv_sec = 0;
	itimer.it_value.tv_usec = 0;
	itimer.it_interval.tv_sec = 0;
	itimer.it_interval.tv_usec = 0;

	if(setitimer(ITIMER_REAL,&itimer,NULL) < 0){
		perror("setittimer");
		exit(1);
	}

	return;
}

void myfunc2(){

	is_siged = 1;

	return;
}

int mygetchar(time_t second){
	struct sigaction sa_sig;
	memset(&sa_sig, 0, sizeof(sa_sig));
	sa_sig.sa_handler = myfunc2;
	sa_sig.sa_flags = 0;

	if (sigaction(SIGINT, &sa_sig, NULL) < 0) {
		perror("sigaction");
		exit(1);
	}

	struct sigaction sa_alarm;
	memset(&sa_alarm, 0, sizeof(sa_alarm));
	sa_alarm.sa_handler = myfunc;
	sa_alarm.sa_flags = 0;

	if (sigaction(SIGALRM, &sa_alarm, NULL) < 0) {
		perror("sigaction");
		exit(1);
	}

	struct itimerval itimer;
	itimer.it_value.tv_sec = second;
	itimer.it_value.tv_usec = 0;
	itimer.it_interval.tv_sec = 0;
	itimer.it_interval.tv_usec = 0;

	if(setitimer(ITIMER_REAL,&itimer,NULL) < 0){
		perror("setittimer");
		exit(1);
	}

	int a;
	a = getchar();
	if(is_siged){
		a = -3;
	}else if(feof(stdin)){
		a = -1;
	}else if(ferror(stdin)){
		a = -2;
	}

	return a;

}

int main(){
	time_t now;

	now = time(NULL);
	printf("%s",ctime(&now));
	int a;
	a = mygetchar(2);
	printf("str = '%c', int = %d\n",a,a);

	now = time(NULL);
	printf("%s",ctime(&now));
	return 0;
}
