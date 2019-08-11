#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>

/* Refer to http://www.coders-hub.com/2013/04/c-code-to-encrypt-and-decrypt-message.html#.Vhs81MryNC1 */
unsigned long long int n, t;
unsigned long long int p,q,flag,e,d,temp[100],j,m[100],en[100],i;
char msg[100];
int prime(long int);
void ce();
long int cd(long int);
void encrypt();
void decrypt();

void RSAerr(char *error){
  printf("%s\n", error);
}

void print_bits(unsigned int num){
  int i;
  int bits[32];
  for(i = 0; i < 32; i++){
    bits[i] = num % 2;
    num /= 2;
  }
  for(i = 31; i >= 0; i--){
    printf("%d", bits[i]);
  }
  printf("\n");
}

// same as pkcs but with pairs of bits (00, 01, 10, 11) instead of chars: 000||10||PS||00||m when PS is, for simplicity, all 1's (and at least 3 bits)
int check_simplified_pkcs_padding(unsigned int *unpadded, unsigned int plaintext){
  int PSlength = 0;
  int good = 1;
  int mlen;
  if (plaintext >> 27 != 2){
    printf("1");
    good = 0;
  }
  else {
    while((plaintext >> (27 - 1 - PSlength)) % 2 == 1 && PSlength < 25){
      PSlength++;
    }
    mlen = 32 - 7 - PSlength;
    if (PSlength == 25 || (plaintext >> (27 - PSlength - 2)) % 4 != 0){
      printf("2");
      good = 0;
    }
  }
  if (good == 0) {
    mlen = -1;
    goto err;
  }

  *unpadded = plaintext % (int)pow(2, mlen);

  err:
  if (mlen == -1){
    RSAerr("incorrect padding");
  }

  return mlen;
}

long int padd_message(long int message){
  int mlen = 32;
  while((message >> (mlen - 1)) % 2 == 0){
    mlen--;
  }
  if (mlen > 25){
    return 0;
  }
  return message + pow(2, 28) + pow(2, 27) - pow(2, mlen + 2); //finish building padded message using mlen
}

// random prime in range 2**14 to 2**15
int rand_prime(){
  long int r;
  while(1){
    r = (rand() % 16384) + 16384;//16384;32768
    if (prime(r) == 1){
      return r;
    }
  }
}

void key_gen(){
  srand(time(NULL));
  p = rand_prime();
  q = rand_prime();
  n=p*q;
  t=(p-1)*(q-1);
  ce();
}


int prime(long int pr)
{
  int i;
  j=sqrt(pr);
  for(i=2;i<=j;i++)
  {
      if(pr%i==0)
      return 0;
  }
  return 1;
}

void ce()
{
  for(i=2;i<t;i++)
  {
      if(t%i==0)
      continue;
      flag=prime(i);
      if(flag==1&&i!=p&&i!=q)
      {
          e=i;
          flag=cd(e);
          if(flag>0)
          {
              d=flag;
              break;
          }
      }
  }
}

long int cd(long int x)
{
  long long int k=1;
  while(1)
  {
      k=k+t;
      if(k%x==0)
      return(k/x);
  }
}

void encrypt()
{
  long int pt,ct,key=e,len;
  unsigned long long int k;
  i=0;
  len=strlen(msg);
  while(i!=len)
  {
      pt=m[i];
      k=1;
      for(j=0;j<key;j++)
      {
          k=k*pt;
          k=k%(unsigned long long)n;
          
      }
      temp[i]=k;
      ct=k;
      en[i]=ct;
      i++;
  }
  en[i]=-1;
}

void decrypt()
{
  unsigned long long int pt,ct,key=d;
  unsigned long long int k;
  i=0;
  while(en[i]!=-1)
  {
      ct=temp[i];
      k=1;
      for(j=0;j<key;j++)
      {
          k=k*ct;
          k=k%(unsigned long long)n;
      }
      pt=k;
      m[i]=pt;
      i++;
  }
  m[i]=-1;
}



void main()
{
  unsigned int temp;

  key_gen();
  printf("n - %llu, p - %llu, q - %llu, t - %llu\n", n, p, q, t);
  msg[0] = 'a';
  m[0] = padd_message(100);
  printf("%llu\n",m[0]);
  print_bits(m[0]);
  encrypt();
  decrypt();
  printf("\nTHE ENCRYPTED MESSAGE IS\n");
  for(i=0;en[i]!=-1;i++)
  printf("%llu",en[i]);
  printf("\nTHE DECRYPTED MESSAGE IS\n");
  printf("%llu\n",m[0]);
  print_bits(m[0]);
}
