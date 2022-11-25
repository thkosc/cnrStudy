Program to probe more efficient coherent noise removal (CNR) algorithms in comparison to the ones already in place in LArSoft.

Get the code :
git clone https://github.com/thkosc/cnrStudy

Compile the code :
make

How to use the code :

./cnrStudy -c configFile.txt -f larsoft-art-root-file.root
[OPTIONS] : 
	'-n 10' --> will only study event 10 (first event = 0) in the file
	'-h' --> print help guide
