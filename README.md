# Cache Attacks Library

## What is this?
This library is a simple yet powerful tool that helps you perform cache side-channel attacks. The basic attackers implemented here are target-based, receiving a specific target and identifying accesses.
While the implemented attackers here are very straightforward, the user is free to expand and build his/her own attacker types based on the base classes provided here and using the wrappers and tools we've built.
The code is written to work in a Linux environment, and is free to use by anyone everywhere.

## Main features:
1. Easy API for basic cache side-channel attacks.
2. Wrappers for loading and searching for target in victim files.
3. Flexible base classes and tools to build further attacks with ease.

## How to use
### Given attackers
There are 2 attackers implemented here: FRAttacker and PPAttacker. While FRAttacker uses flush-reload methods and PPAttacker uses prime & probe methods, the 2 basic implementations here are used in the same way. Both receive a target pointer to a read-only victim (the target should be shared between the victim and the attacker). The target can be found by the constructor if given a path to the victim and the data to search in the victim file. If the user would like to provide the target pointer himself/herself, he/she can do so by using the provided setter function.
Once constructed and given a target, the Configure() function should be called to configure the attacker. After Configure is called, the user should make sure that the interval and maxIteration parameters were set in the constructor, and if not - set them manually using their setters.
Then the Attack() function should be called to start the attack. This function will run maxIteration iterations, each iteration removing the target from the cache (using the respected methods), waiting interval microseconds and measuring access times (in cycles). After the function has ended, the measurements field of the attacker will be updated with the results. Use the getter function to get the measurements and analyze the data gathered by the attacker.

### The Measurements class
Measurements are given using the Measurements class. This class contains a vector of accesses which can be accessed using a getter. Each entry in the vector is a struct containing the cycles measured, the time of measurement and a speculation whether the target was in L3 cache or in the main memory.

### Building your own attackers
To build your own attacker, simply write a son to the Attacker base class. The Attacker base class contains all the basic structure of an attacker, and implements a time measurement function for easy and accurate measurements of access times to pointers.
The class you write (that inherits from Attacker) should implement the Configure() and the Attack() functions. It's up to you to decide what to do with them. Note that by default Configure isn't required to be called before Attack, so if you want to you should enforce that yourself. The rest is built for you and ready to go.

### Read the documentation!
The .h files are heavily documented with far more detail, and each of them starts with a paragraph explaining how to use that class. Read them before doing anything else :)

### Examples
Examples of using FRAttacker and PPAttacker can be found in main1 and main2 which are in AttackerTest1 and AttackerTest2 respectively.
For example on how to write your own attackers, refer to FRAttacker and read the Configure and Attack functions.
Everything is documented for your convenience.

## Who are we?
We are CS/Math students at TAU. This library was written by us as a project in a first degree course in CS. Feel free to contact us anytime:
omriyeshaya@mail.tau.ac.il


Enjoy!