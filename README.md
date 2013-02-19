RSA_Cryptosystem
================

Programmer: Anthony Mascia

RSA Cryptosystem with Big Integer Library

The Purpose of this program is to demonstrate the use of the RSA
Cryptosystem by combining various methods and algorithms to obtain
the private and public key of a string message and then encrypting/decrypting
the message for the user to see.


This is what the beginning of the program looks like.
Displays:
A welcome message.
Asks user if they want to use a predetermined list of 1,000 primes or their own
![Start of Program](http://i.imgur.com/PING7lI.png)


The program then picks two random prime numbers
These primes are then used to determine phi and n, which are the variables that will obtain the private and public keys
To find the public key, the program finds the GCD of e and m
To find the private key, the program uses the Extended Euclidean Algorithm
![Private/Public Keys](http://i.imgur.com/YzMH4zw.png)


Now it is time for the encrpyting and decrypting process
Encrypting:
The string message is put in to an array of characters, and then each character is encrypted using
the successive squaring algorithm, and then put sequentially in to an array of integers
Then the array of encrypted numbers is displayed to the user; this is the encrypted number

Decrypting:
First, the program goes through array and decrypt ever encrypted number one by one
using the successive squaring algorithm again
We then convert static cast the int to a character
This character is then stored in to the array of characters until every number is converted and we have a message
![Encrypting/Decrypting](http://i.imgur.com/rsCxOvn.png)
