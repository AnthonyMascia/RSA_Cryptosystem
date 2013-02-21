RSA_Cryptosystem
================

Programmer: Anthony Mascia

RSA Cryptosystem with Big Integer Library

The Purpose of this program is to demonstrate the use of the RSA
Cryptosystem by combining various methods and algorithms to obtain
the private and public key of a string message and then encrypting/decrypting
the message for the user to see.
<br /><br />

## Beginning of Program ##
This is what the beginning of the program looks like.<br />
<b>Displays:</b><br />
<ul>
<li>A welcome message.</li><br />
<li>Asks user if they want to use a predetermined list of 1,000 primes or their own</li><br />
</ul>
![Start of Program](http://i.imgur.com/PING7lI.png)
<br /><br />

## User Input ##
<ul>
<li>The program then picks two random prime numbers</li><br />
<li>These primes are then used to determine phi and n, which are the variables that will
obtain the private and public keys</li><br />
<li>To find the public key, the program finds the GCD of e and m</li><br />
<li>To find the private key, the program uses the Extended Euclidean Algorithm</li><br />
</ul>
![Private/Public Keys](http://i.imgur.com/YzMH4zw.png)
<br /><br />

## Encryption and Decryption ##
<b>Encrypting:</b><br />
<ul>
<li>The string message is put in to an array of characters, and then each character is encrypted using
the successive squaring algorithm, and then put sequentially in to an array of integers</li>
<li>Then the array of encrypted numbers is displayed to the user; this is the encrypted number</li>
</ul>
<br /><br />

<b>Decrypting:</b><br />
<ul>
<li>First, the program goes through array and decrypt ever encrypted number one by one
using the successive squaring algorithm again</li>
<li>Then static casts each int to a character</li>
<li>This character is then stored in to the array of characters until every number
is converted and we have a message</li>
</ul>
![Encrypting/Decrypting](http://i.imgur.com/rsCxOvn.png)
