#include	"./thread.h"

void
thread_make(ReqHandler rh)
{
  void	*thread_main(void *);

  Pthread_create(&tptr[rh.index], NULL, &thread_main, (void *) (rh.handler));
  return;		/* main thread returns */
}

void *
thread_main(void *arg)
{
  Handler handler = (Handler)arg;
  int         connfd;

  socklen_t		clilen;
  struct sockaddr	*cliaddr;

  cliaddr = Malloc(addrlen);

  for ( ; ; ) {
    clilen = addrlen;
      Pthread_mutex_lock(&mlock);
    connfd = Accept(listenfd, cliaddr, &clilen);
    Pthread_mutex_unlock(&mlock);

    handler(connfd);		/* process request */
    Close(connfd);
  }
}