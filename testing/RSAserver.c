#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

/* Refer to http://www.coders-hub.com/2013/04/c-code-to-encrypt-and-decrypt-message.html#.Vhs81MryNC1 */

unsigned int p,q,n,t,e,d;

int prime(unsigned int pr){
  int i;
  unsigned int j = sqrt(pr);
  for(i=2;i<=j;i++)
  {
      if(pr%i==0)
      return 0;
  }
  return 1;
}

// random prime in range 2**15 to 2**16
int rand_prime(){
	while(1){
		unsigned int r = srand(time(NULL)) + 32768;
		if (prime(r)){
			return r
		}
	}
}

void key_gen(){
	p = rand_prime();
	q = rand_prime();
	n = p*q; // 32 bit number;
	t = (p-1)*(q-1);
	public_key_gen();
	private_key_gen();
}

void public_key_gen(){
	e = 3;
	while(!prime(e) || t%e == 0 || e == p || e == q){
		e++;
	}
}

void private_key_gen(){
	x = 1;
	while(x%e != 0){
		x = x + t;
	}
	d = x/e;
}

unsigned int padd_message(unsigned int message){
	int mlen = 32;
	while(message >> (mlen - 1) % 2 == 0){
		mlen--;
	}
	if (mlen > 26){
		return 0;
	}
	return message + pow(2, 29) + //finish building padded message using mlen
}

unsigned int encrypt(unsigned int plaintext){
	int i;
	unsigned long int temp = 1;
	for(i = 0; i < e; i++){
		temp = temp * plaintext;
		temp = temp % n  // temp will be plaintext ^ (i + 1) mod n
	}
	return (unsigned int)temp
}

unsigned int decrypt(unsigned int ciphertext){
	int i;
	unsigned long int temp = 1;
	for(i = 0; i < d; i++){
		temp = temp * ciphertext;
		temp = temp % n  // temp will be ciphertext ^ (i + 1) mod n
	}
	return (unsigned int)temp
}

// same as pkcs but with pairs of bits (00, 01, 10, 11) instead of chars: 00||10||PS||00||m when PS is, for simplicity, all 1's (and at least 3 bits)
int check_simplified_pkcs_padding(unsigned int *unpadded, unsigned int plaintext){
	int PSlength = 0;
	int good = 1;
	int mlen;
	if (plaintext >> 28 != 2){
		good = 0;
	}
	else {
		while((plaintext >> (28 - 1 - PSlength)) % 2 == 1 && PSlength < 25){
			PSlength++;
		}
		mlen = 32 - 6 - PSlength;
		if (PSlength == 25 || (plaintext >> (28 - PSlength - 2)) % 4 != 0){
			good = 0;
		}
	}
	if (!good) {
		mlen = -1
		goto err;
	}
	*unpadded = plaintext % pow(2, mlen);
	err:
	if (mlen == -1){
		RSAerr("incorrect padding");
	}

	return mlen;
}

int main(){
	key_gen();
}

void decrypt()
{
  long int pt,ct,key=d[0],k;
  i=0;
  while(en[i]!=-1)
  {
      ct=temp[i];
      k=1;
      for(j=0;j<key;j++)
      {
          k=k*ct;
          k=k%n;
      }
      pt=k+96;
      m[i]=pt;
      i++;
  }
  m[i]=-1;
  printf("\nTHE DECRYPTED MESSAGE IS\n");
  for(i=0;m[i]!=-1;i++)
  printf("%c",m[i]);
  printf("\n");
}
