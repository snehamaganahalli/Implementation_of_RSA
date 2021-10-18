# Implementation_of_RSA
Implement RSA with and without using Chinese remainder Theorem (CRT). And calculate the efficiency for the same.


1) Run below command to sync the code to local
git clone

2) Install the GMP Library. The below command needs super user permission. Without this installation the program will not get compiled.
sudo apt-get install libgmp3-dev![image](https://user-images.githubusercontent.com/38486907/137661155-95d1b815-dec3-45f1-933c-9f603c167c0f.png)

3) compile
gcc rsa_crt.c -lgmp

4) Execute

./a.out

===========================================================================================================================================================
The program asks to enter the plain text. The maximun value for the plain text is [0, (n-1)]. (0 to n-1 including 0 and n-1).
The larger the value of the plain text (i.e when the plain text value is near to the value of n), we can see the efficiency of the Chinese remainder theorem (CRT).

For smaller plain text values, the normal RSA decryption is faster than decrypting using CRT.
