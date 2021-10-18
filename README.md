# Implementation_of_RSA
Implement RSA with and without using Chinese remainder Theorem (CRT). And calculate the efficiency for the same.


1) Run below command to sync the code to local

**git clone https://github.com/snehamaganahalli/Implementation_of_RSA.git**

2) Install the GMP Library. The below command needs super user permission. Without this installation the program will not get compiled.

**sudo apt-get install libgmp3-dev**

3) compile

**gcc rsa_crt.c -lgmp**

4) Execute

**./a.out**

**Example runs:**

1) enter the number to encrypt:

1234567890  (10 digits)

2) 222222222233333333334444444477777777777777777777 (50 digits)

3) 22222222223333333333444444447777777777777777777774444444444444666666666666555555555555888888867546 (100 digits)

4) 22222222223333333333444444447777777777777777777774444444444444666666666666555555555555888888867546553485769364658694635277777777777777766666666666333  (150 digits)

5) 3910906112460495082455641524758395842223773706163927429683247121237778918244282038204906465819743338991230270916132368306659185881981950472589745902333400941355080285481175433769979494301109199  

(195 digits. This is the max value which can be encrypted.)
=======================================================================

The program asks to enter the plain text. The maximun value for the plain text is [0, (n-1)]. (0 to n-1 including 0 and n-1).

**We will see that decryption using Chinese remainder theorem is two to three times mode efficient than the normal decryption.**
