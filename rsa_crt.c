#include<stdio.h>
#include<gmp.h>
#include <assert.h>
#include <time.h>

mpz_t x, p, q, n, e, d, dp, dq, y, p_minus_1, q_minus_1;
clock_t start_t, end_t;
double total_with_crt, total_t;

void rsa_encrypt()
{
  mpz_init(y);
  mpz_set_ui(y, 0);

  /* Calculate y = x^e mod n */
  mpz_powm(y, x, e, n);
  printf ("\nEncrypted message is ");
  mpz_out_str(stdout, 10, y);
  printf ("\n");
}


void rsa_decrypt()
{
  mpz_t decrypt_val;
  mpz_init(decrypt_val);
  mpz_set_ui(decrypt_val, 0);

  /* x = y^d mod n */
  start_t = clock();
  mpz_powm(decrypt_val, y, d, n);
  end_t = clock();

  total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
  printf ("\nDecryption WITHOUT using Chinese remainder theorem (CRT) is ");
  mpz_out_str(stdout, 10, decrypt_val);

}

/* RSA decrypt using chinese remainder theorem */
void rsa_decrypt_using_crt()
{
  mpz_t xp, xq, inv_p, inv_q, crt_decrypt_val, tmp, tmp1;

  mpz_init(xp);
  mpz_set_ui(xp, 0);

  mpz_init(xq);
  mpz_set_ui(xq, 0);

  mpz_init(inv_p);
  mpz_set_ui(inv_p, 0);

  mpz_init(inv_q);
  mpz_set_ui(inv_q, 0);

  mpz_init(tmp);
  mpz_set_ui(tmp, 0);

  mpz_init(tmp1);
  mpz_set_ui(tmp1, 0);

  mpz_init(crt_decrypt_val);
  mpz_set_ui(crt_decrypt_val, 0);

  /* Calculate xp = y^dp mod p */
  mpz_powm(xp, y, dp, p);

  /* Calculate xq = y^dq mod q */
  mpz_powm(xq, y, dq, q);

  mpz_invert(inv_p, q, p);
  mpz_invert(inv_q, p, q);

  /* tmp = xp * q * inv_p */
  mpz_mul(tmp, xp, q);
  mpz_mul(tmp, tmp, inv_p);

  /* tmp1 = xp * q * inv_p */
  mpz_mul(tmp1, xq, p);
  mpz_mul(tmp1, tmp1, inv_q);

  start_t = clock();
  mpz_add(crt_decrypt_val, tmp, tmp1);
  mpz_mod(crt_decrypt_val, crt_decrypt_val, n);
  end_t = clock();
  total_with_crt = (double)(end_t - start_t) / CLOCKS_PER_SEC;

  printf ("\nDecryption WITH chinese remainder theorem (CRT) is ");
  mpz_out_str(stdout, 10, crt_decrypt_val);
}

void clear_all()
{
  mpz_clear(x);
  mpz_clear(p);
  mpz_clear(q);
  mpz_clear(n);
  mpz_clear(e);
  mpz_clear(d);
  mpz_clear(dp);
  mpz_clear(dq);
  mpz_clear(y);
  mpz_clear(p_minus_1);
  mpz_clear(q_minus_1);

}

void init_all()
{
  mpz_init(x);
  mpz_init(p);
  mpz_init(q);
  mpz_init(n);
  mpz_init(e);
  mpz_init(d);
  mpz_init(dp);
  mpz_init(dq);
  mpz_init(y);
  mpz_init(p_minus_1);
  mpz_init(q_minus_1);
}

int main()
{

  char inputStr[1024];

  int flag;

  init_all();

  mpz_set_ui(x, 0);

  /*Choose p, q such that they are relatively prime to each other*/
  mpz_set_ui(p, 15635861);

  mpz_set_ui(q, 14899679);

  /* n = p*q */
  mpz_set_ui(n, 232969309788619);

  /* Select a public key */
  mpz_set_ui(e, 3);

  /* Select a private key. It is inverse of e mod phi. phi = (p-1) * (q-1)  */
  mpz_set_ui(d, 155312852835387);

  /* Calculate dp; dp = d mod (p-1) */
  mpz_sub_ui(p_minus_1, p, 1);
  mpz_mod(dp, d, p_minus_1);

  /* Calculate dq; dq = d mod (q-1) */
  mpz_sub_ui(q_minus_1, q, 1);
  mpz_mod(dq, d, q_minus_1);

  printf ("\nEnter the number to encrypt. The number should be less than n: ");
  mpz_out_str(stdout, 10, n);
  printf ("\n");
  scanf("%1023s" , inputStr);

  /* Parse the input string as a base 10 number. If flag is not 0 then the operation failed */
  flag = mpz_set_str(x, inputStr, 10);
  assert ("Invalid input string. please enter a valid input string" && flag == 0);

  /* If the number is greater than n (the message space) prit error. */
  flag = mpz_cmpabs (n, x);
  assert ("Invalid input string. please enter a valid input string lesser than n" && (flag >= 0));

  /* Print n */
  printf ("\nPlain text is ");
  mpz_out_str(stdout, 10, x);
  printf ("\n");

  rsa_encrypt();

  rsa_decrypt_using_crt();
  rsa_decrypt();

  printf ("\n");
  printf ("\n===========================================================================\n");
  printf("Total time taken by CPU using CRT : %f", total_with_crt);
  printf("\nTotal time taken by CPU without using CRT: %f\n", total_t);
  printf ("===========================================================================\n");

  clear_all();
  return 0;
}
