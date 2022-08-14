# RegistrationSystem-with-Encrypting-and-FileSystem


Title			: Registration System with SHA-256 Encrypting and FileSystem
Language		: C++
Author			: Wojciech Jastrzebowski
Date Created	: 13-08-2022


The program is used to imitate the login/password registration system. 
For this purpose, I used the file system and SHA-256 password encryption. 

As far as the file system is concerned, the program creates a users.txt file, 
where user names and encrypted passwords are stored. 

The encryption of passwords uses the SHA-256 standard https://create.stephan-brumme.com/hash-library/ 
- other encryption would also be good, but for the example use in the sample program I decided to use this one.
