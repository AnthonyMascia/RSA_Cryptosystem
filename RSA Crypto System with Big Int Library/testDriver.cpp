// Programmer: Anthony Mascia
// RSA Cryptosystem with Big Integer Library
//
// Purpose:
//	The Purpose of this program is to demonstrate the use of the RSA
//	Cryptosystem by combining various methods and algorithms to obtain
//	the private and public key of a string message and then encrypting/decrypting
//	the message for the user to see.



/** Preprocessor Directives **/
#include <iostream>
#include <iomanip>
#include <ctime>
#include <fstream>
#include "BigIntegerLibrary.h"  // 
using namespace std;

/** Function Prototypes **/
void welcomeMessage();								  // Welcome message
BigInteger GCD(BigInteger, BigInteger);				  // Greatest Common Divisor
BigInteger extendedEuclid(BigInteger, BigInteger);	  // Extended Euclidean Algorithm
BigInteger successiveSquare(BigInteger,
							BigInteger, BigInteger);  // Successing Squaring Algorithm

int main(){
  
	welcomeMessage();			    // Display welcome message

	int select;
	ifstream file;
	BigInteger p, q;			    // Prime numbers to be inputted for key generation
	BigInteger n, m;			    // n = p * q; m = phi = (p-1) * (q-1)
	BigInteger privKey;
	BigInteger e = 2;
	string message;
	char charMessage[100];          // Will convert message into array of characters
	BigInteger intMessage[100];     // Will convert characters in to an array of their ASCII value
	BigInteger encryptedNum;
	BigInteger decryptedMessage;    // Numbers we get after encrypting/decrypting
	bool findE = true;		        // Used for while loop until e is found


	string primeListString[1000];   // Will store the actual string data from the .txt file
	BigInteger primeListInt[1000];  // Array of converted prime strings to integers



	/***** CREATE LIST OF PRIME NUMBERS *****/

	cout << "1) Enter '1' if you would like to use a preset list of primes.\n"
		 << "2) Enter any other number to specify your own file path.\n"
		 << "----> ";
	cin >> select;
		
	// Condition where user wants to use text file already in the program
	if(select == 1)
	{
		file.open("primes.txt");             // Open text file in program
		if(file.is_open())
		{
			for(int i = 0; i < 1000; i++)
				file >> primeListString[i];  // Create array of primes
		}
	}

	// Condition where user wants to use their own text file
	else
	{
		while(!file.is_open())                    // Ensure user inputs correct file path
		{
			char fName[80];
			cout << endl << "Enter file path: "; 
			cin >> fName;
			file.open(fName);
			if(file.is_open())
			{
				cout << "File found!";
				for(int i = 0; i < 1000; i++)
					file >> primeListString[i];   // Create array of primes
			}
			else
				cout << endl << "File not found. Please try again." << endl;
		}  // end while
	}  // end else

	/***** END CREATE LIST OF PRIME NUMBERS *****/



	// First convert every string in array to a BigInteger
	// Then add that BigInteger to the BigInteger array of primes
	// until we have a list of BigInteger primes we can work with
	for(int i = 0; i < 1000; i++)
	{
		string temp = primeListString[i];
		primeListInt[i] = stringToBigInteger(temp);
	}


	cout << endl << endl;


    srand( (unsigned)time( NULL ) );  // Set initial seed


	// Select 2 random primes from list
	p = primeListInt[rand() % 1000];
	q = primeListInt[rand() % 1000];

	cout << "Your first prime number will be: " << p << endl;
	cout << "Your second prime number will be: " << q << endl;

	n = p * q;         // Initialize n
	m = (p-1) * (q-1); // Initialize phi


	/***** OBTAINING PUBLIC KEY *****/

	while(findE)			// While loop to obtain 'e'
	{           
		if(GCD(e, m) == 1)  // Want the GCD to be 1
			findE = false;
		else
		{
			GCD(e, m);
			e++;            // Keep incrementing e until 1 is reached
		}
	}					    // end while

	cout << "Your public key is: ( " << e << ", " << n << " )" << endl;

	/***** END OBTAINING PUBLIC KEY *****/



	/***** OBTAINING PRIVATE KEY *****/

	privKey = extendedEuclid(e, m);

	if(privKey <= 0){        // Testing if negative
		while(privKey <= 0)  // If so, keep adding m until privKey is positive
			privKey += m;
	}

	cout << "Your private key is: ( " << privKey << ", " << n << " )" << endl;

	/***** END OBTAINING PRIVATE KEY *****/



	cout << endl << endl;




	cout << "Enter a message to encrypt: ";
	cin.ignore();
	getline(cin, message);

	// First convert string message to an array of characters
	// Then convert the array of chracters to an array of integers
	for(int i = 0; i < message.length(); i++)
	{
		charMessage[i] = message[i];
		intMessage[i] = charMessage[(int)i];
	}		



	cout << endl << endl;



	/***** BEGIN ENCRYPTING *****/

	// Encrypt every number in array and replace previous
	// number with encrypted number until we have an array
	// full of encrypted numbers
	for(int i = 0; i < message.length(); i++)
	{
		encryptedNum = successiveSquare(intMessage[i], e, n);
		intMessage[i] = encryptedNum;
	}
	
	cout << "ENCRYPTED NUMBER\n"
		 << "----------------\n\n";
	for(int i = 0; i < message.length(); i++)
		cout << intMessage[i];

	/***** END ENCRYPTING *****/



	cout << endl << endl << endl;



	/***** BEGIN DECRYPTING *****/

	// First go through array and decrypt ever encrypted number one by one
    // Then convert each BigInteger to a regular int
	// This then allows us to static cast the int to a character
	// This character is then stored in to the array of characters
	// until every number is converted and we have a message
	for(int i = 0; i < message.length(); i++)
	{
		decryptedMessage = successiveSquare(intMessage[i], privKey, n);
		int decryptedNumber = decryptedMessage.toInt();
		char decryptedChar = static_cast<char>(decryptedNumber);
		charMessage[i] = decryptedChar;
	}

	cout << "DECRYPTED MESSAGE\n"
		 << "-----------------\n\n";
	for(int i = 0; i < message.length(); i++)
		cout << charMessage[i];

	/***** END DECRYPTING *****/



	cout << endl << endl << endl;



	system("pause");
	return 0;
}


//**************************************************************
// Function used for finding e which is the public key number. *
// 'e' is the coprime of m(n). It is the number that when it's *
// GCD'd with m, will be 1. So this is a simple GCD finding    *
// function and it dealt with in a while loop in main().       *
//**************************************************************
BigInteger GCD(BigInteger a, BigInteger b)
{    
	while( 1 )
    {
        a = a % b;
		if( a == 0 )
			return b;
		b = b % a;

        if( b == 0 )
			return a;
    }
} // end GCD



//**************************************************************
// Function used for finding d which is the private key number.*
// 'd' is the multiplicative inverse of 'e'%(m*n). The Extended*
// Euclidean Algorithm is the best method in finding this,     *
// especially with very large prime numbers                    *
//**************************************************************
BigInteger extendedEuclid(BigInteger num1, BigInteger num2){
	BigInteger num1Orig = num1, num2Orig = num2; // Save original numbers inputted
	BigInteger x = 1, y = 0;
	BigInteger k = 0, l = 1; // Will become the numbers to multiply a and b by 
	BigInteger quo /*Quotient*/, rem /*Remainder*/, m, n;
	while(num1 != 0){ // While there is still a remainder
		quo = num2 / num1;
        rem = num2 % num1;
        m = k - quo * x;
        n = l - quo * y;
        k = x, l = y; // Keep track of original x and y values for next iteration
        x = m; 
		y = n;
        num2 = num1; // b will eventually become the modulo of a and b
		num1 = rem; // Invoking Euclids Algo for next iteration
	} // End while

	return k;

} // End function extendedEuclid()



//**************************************************************
// Function used for getting the encrypted/decrypted numbers of*
// the number the user wishes to encrypt.					   *
// For ENCRYPTION:											   *
//		- The number we wish to encrypt becomes the base	   *
//		- e becomes the exponent							   *
//      - The mod becomes n (This never changes)			   *
// For DECRYPTION:                                             *
//		- The encrypted number we obtain becomes the base	   *
//		- d becomes the exponent							   *
//      - The mod remains n									   *
//**************************************************************
BigInteger successiveSquare(BigInteger base, BigInteger exp, BigInteger m){
	// Base case: when exponent is = 0
	if(exp == 0)
		return 1; // Any number to the 0 power is 1
	// Base case: when exponent is = 1
	else if(exp == 1)
		return base % m; // Any number to the 1 power is itself
						 // mod it to m in case base is bigger than m
	// Case 1: when exponent is even
	else if(exp % 2 == 0)
		return successiveSquare((base * base) %m, exp / 2, m);
	// Case 2: when exponent is odd
	else
		return (successiveSquare((base * base) % m, exp / 2, m) * base) % m;
} // End function successiveSquare()



//**************************************************************
// Function that simply displays a welcome message to the user *
//**************************************************************
void welcomeMessage(){
	cout << setw(65) <<
		"#################################################\n" << setw(65) <<
		"#                                               #\n" << setw(65) <<
		"#             Hello and welcome to...           #\n" << setw(65) <<
		"#         Anthony's RSA Encrypto Machine!       #\n" << setw(65) <<
		"#                                               #\n" << setw(65) <<
		"#   Have you ever wanted to send your friend    #\n" << setw(65) <<
		"# a super secret message, but couldn't because  #\n" << setw(65) <<
		"#  if fallen into the wrong hands, could just   #\n" << setw(65) <<
		"#   absolutely ruin your life for some reason?  #\n" << setw(65) <<
		"#                                               #\n" << setw(65) <<
		"#                WELL FEAR NOT!!                #\n" << setw(65) <<
		"# With my machine you can input any message you #\n" << setw(65) <<
		"#  wish, and it will generate both private and  #\n" << setw(65) <<
		"# public keys for you and your friend. Then it  #\n" << setw(65) <<
		"#  will encrypt your message, and then decrypt  #\n" << setw(65) <<
		"#   it to prove that this is the real deal and  #\n" << setw(65) <<
		"#                not just a scam!               #\n" << setw(65) <<
		"#                                               #\n" << setw(65) <<
		"#                                               #\n" << setw(65) <<
		"#          Let's get started shall we?          #\n" << setw(65) <<
		"#                                               #\n" << setw(66) <<
		"#################################################\n\n";
} // End welcomeMessage()
