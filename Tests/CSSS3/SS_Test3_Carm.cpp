// Solovay Strassen test with Chaitin Schwartz construction.
// g++ -O2 SS_Test3_Carm.cpp -o SS_Test3_Carm -lgmp -lgmpxx

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cassert>
#include <cstdlib>
#include <limits>
#include <cmath>
#include <sys/stat.h>

#include <gmpxx.h>

#define JUMP_BITS 1     // Setting to 1 means that instead of reading continuously through the data file, after each witness
			// string is read the program jumps back to the beginning of the data file, then skips a certain
			// number of bits (equal to tot_count), and then reads the next string. Why? Because usually only a fraction
                        // of the bits in the string is needed (this is the number used_bits*count) until compositeness is verified.
                        // This way, we can use the unused portion for the next CM number.

#define BIT_FLIP 0 // MS: if set to 1, flip every input bit (i.e., test the complemented sequence)
#define VERBOSE 0 // MS: set to 1 for expanded status output
#define ORIGINAL_READPROC 0 // MS: set to 1 to use readin procedure from original Abbott code (with reverse)

using namespace std;

inline bool check_exist_file (const std::string& name) {
    ifstream f(name.c_str());
    return f.good();
}

struct EOF_Error 
{ 
    int e;
    EOF_Error(int e2) { e = e2; }
};

#if ORIGINAL_READPROC
class BitSeq  // sequence of bits from a raw binary file
{
    private:
    ifstream in;
	
    char byte;	// current byte read from stream
    int offset;  	// last bit 7..0 of byte used

    public:
    static bool throwError;
    BitSeq(const char *fname) : in(fname) { offset=-1; }
    ~BitSeq() { in.close(); }
    int eof() { return (in.fail() && in.eof()); }

    char getbit()
    {
#ifdef BIT_FLIP
	if (offset==-1) { in.get(byte); byte = ~byte;  offset=7; }
#else
	if (offset==-1) { in.get(byte);  offset=7; }
#endif
	return byte & 1<<offset-- ? 1 : 0;
    }

    unsigned char reverse(unsigned char b)
    {
        b = (b & 0xF0) >> 4 | (b & 0x0F) << 4;
        b = (b & 0xCC) >> 2 | (b & 0x33) << 2;
        b = (b & 0xAA) >> 1 | (b & 0x55) << 1;
        return b;
    }

    void jumpbits(unsigned long long cnt)
    {
        offset=-1;
        in.seekg(cnt/8);
        getbits(cnt%8);
	if (in.eof()) throwError = true; 

    }

    mpz_class getbits(unsigned long long cnt)
    {
	mpz_class t(0);

        mpz_class tmp;

        unsigned long long total=cnt;

	if (offset < cnt)   // can we finish off current byte?
	{// note: if offset == -1 then t will still be 0			
	  char temp = byte & (1<<(offset+1))-1;
            t = reverse((unsigned char)temp)>>(7-offset);
	    cnt -= offset+1;
	    offset=-1; 
	}

	// fast version (by bytes)
	//
        if (cnt>=8) offset=-1;  // set once
	while (cnt>=8) 
	{
	    in.get(byte);
#ifdef BIT_FLIP
            byte = ~byte;
#endif
	    if (in.eof()) {throwError = true; break;}

            mpz_ui_pow_ui(tmp.get_mpz_t(),2, total-cnt);
	    t += reverse((unsigned char) byte)*tmp; 
	    cnt -= 8;
	}

	// slow version (continue by bits)
	//
	while (cnt)
        {
            mpz_ui_pow_ui(tmp.get_mpz_t(),2, total-cnt);
            t+=getbit()*tmp;
            cnt--;
        }
	if (in.eof()) throwError = true;
	return t; 
    }
};

#else

class BitSeq  // sequence of bits from a raw binary file
{
    private:
	ifstream in;
	
	char byte;	// current byte read from stream
	int offset;  	// last bit 7..0 of byte used

    public:
  static bool throwError;
	BitSeq(const char *fname) : in(fname) { offset=-1; }
	~BitSeq() { in.close(); }
	int eof() { return (in.fail() && in.eof()); }

	char getbit() 
	{
#if BIT_FLIP
	if (offset==-1) { in.get(byte); byte = ~byte;  offset=7; }
#else
	if (offset==-1) { in.get(byte);  offset=7; }
#endif
	return byte & 1<<offset-- ? 1 : 0;
	}

      void jumpbits(unsigned long long cnt)
    {
        offset=-1;
        in.seekg(cnt/8);
        getbits(cnt%8);
	if (in.eof()) throwError = true; 

    }

        mpz_class getbits(int cnt)
	{ 
	    mpz_class t(0);

	    if (offset < cnt)   // can we finish off current byte?
	    {// note: if offset == -1 then t will still be 0			
	      t = byte & (1<<(offset+1))-1;
		cnt -= offset+1;
		offset=-1; 
	    }
#if 1
	    // fast version (by bytes)
	    //
            if (cnt>=8) offset=-1;  // set once
	    while (cnt>=8) 
	    { 
		in.get(byte);
            #if BIT_FLIP
                byte = ~byte;
            #endif
		if (in.eof()) throwError = true;
		t = t*256+((unsigned char) byte); 
		cnt -= 8; 
	    }
#endif
	    // slow version (continue by bits)
	    //
	    while (cnt--) { t = t*2+getbit(); }
	    if (in.eof()) throwError = true;
	    return t; 
	}
};

#endif

bool BitSeq::throwError = false;
BitSeq *inbits;
  
bool solovaytest(mpz_class &n, mpz_class &b)
{
	mpz_class nm1(n), x(1L), y;
	nm1 = nm1 - 1L;
  
	int jacobi = mpz_jacobi(b.get_mpz_t(), n.get_mpz_t());
    
	if (jacobi==0) return true;

	mpz_class nm1d2(nm1);
	nm1d2 = nm1d2 / 2;
	// test a^(n-1/2) != jacobi (mod n)
	//
	mpz_powm(y.get_mpz_t(), b.get_mpz_t(), nm1d2.get_mpz_t(), n.get_mpz_t());

	if ((jacobi==-1 && y!=nm1) || (jacobi==1 && y!=1)) return true;
	return false;
}
    
int main(int argn, char *argc[])
{

  if (!check_exist_file(argc[1])) 
      { cout << "Input file "<<argc[1]<<" does not exist!" << endl; return -1; }
  if (!check_exist_file(argc[2])) 
      { cout << "CM number file not found!" << endl; return -1; }

    std::ifstream file(argc[2]);  // MS: file containing the Carmichael numbers
    std::string str;
    int cm_max_length = 20; // maximum number of digits of Carmichael numbers to be tested
      
  	assert(argn==2 || argn==3);
    
        int rounds=-1; // MS: this way it will test all Carmichael numbers in the file
        //if(argn==3) rounds=stoi(argc[2]); //How many Carmichael number will be tested (MS: do not give this parameter if we want to test all numbers)
        inbits = new BitSeq(argc[1]);
  	int c = 0; //store the value of c. c comes from c-random.

  	//mpz_class J; //store the Carmichael number
 
    	try
	{

		unsigned long long num_carmichael=0, tot_count = 0;
		

   while ( (std::getline(file, str)) && (str.length() <= cm_max_length) && !BitSeq::throwError) // MS: read the file containing the Carmichael numbers line by line 
    {

#if JUMP_BITS
                        //re-start with some bits jumped
                        inbits->jumpbits(tot_count);
                        if(BitSeq::throwError)
                          break;
			// MS: this means that instead of reading continuously through the data file, after each witness
			// string is read the program jumps back to the beginning of the data file, then skips a certain
			// number of bits (equal to tot count), and then reads the next string. Why? Because in this test
			// the witness strings get very long, so we???d reach the end of the data file very quickly if we didn???t
			// rewind and reposition after each witness. 

#endif
                        if(rounds==0) break;
			mpz_class J(str.c_str(), 10);  	          // CM number to be tested
                        // J = std::stol(str);  // MS: convert line to integer -- this will be the Carmichael number to be tested 
			num_carmichael++;

#if VERBOSE
			cout<<"Carmichael number " << J <<" (no. " << num_carmichael << "):";
			cout << "(skipped " << tot_count << " bits)" <<endl; // MS
#endif
			
			int j = mpz_sizeinbase(J.get_mpz_t(),2);// binary legnth of J
                        mpz_class J_minus_1(J-1L);
                        int bits_used = mpz_sizeinbase(J_minus_1.get_mpz_t(),2);// approximation of binary bits used for 1 bit of J-1 based number.

			c = j-1; //c = floor(log2(J)), since J is not power of 2 (Carmichael numbers are not even), c=j-1
			int readLength = j*(j+2*c); // read length according to Chaitin Schwartz theorem
                         
			mpz_class s(0); //Interpret string as an integer


			s = inbits->getbits(readLength); // MS: read string of length readLength from random data file
      if(BitSeq::throwError)
        break;
#if VERBOSE
			cout << "Reading string of length " << readLength << " from file:" << endl << s << endl;  // MS: show string
			std::cout << "In bits: " << s.get_str(2) << " (length="<< s.get_str(2).length() << ")\n"; // MS: display in binary (0/1) format
#endif

			mpz_class d(0); //store base J-1 bit

			bool composite=0;
			unsigned long count = 0;
                        
			//Calculate J-1 representation of s (d_kd_{k-1}...d_0)
			//then do SS(J,1+d_{k-1}), SS(J, 1+d_{k-2}) ...  until one test says composite
                        mpz_class end(J-1L);
                        while(!composite && !BitSeq::throwError)
                        {
                            mpz_class tmp(s);
			    while(tmp>end && !BitSeq::throwError)//Stop when i = k (do not calculate the right most d)
			    {
			        d = tmp%(J-1L);
				tmp = tmp/(J-1L);
                            }
                            d = d+1L;

			    composite = solovaytest(J, d);
                            end = end*(J-1L);
			    count++;
      
      			}
#if VERBOSE
                        cout<<"Trials (1-digit witnesses used) = "<<count<<"; binary bits used for these 1-digit witnesses in base J-1 = "<<bits_used*count<<endl<<endl;
#endif
                        tot_count += bits_used*count; // bits_used*count are the bits actually used until one W is true. The rest of the string is still unused.
			                              // tot_count accumulates this tally of actually used bits.
			                              // Hence, in the next round, we can start reading from tot_count and still get fresh bits. 
                        if(rounds>0)rounds--;

    		}

if(BitSeq::throwError)
{
	  cout << "Read past end of file!\n";
    cerr << "Read past End Of File\n";

}               // Output Total bits used: 
else
{
#if BIT_FLIP
   cout << argc[1] << "[comp] " << tot_count<<" "  << num_carmichael << endl;
#else
   cout << argc[1] << " " << tot_count<<  " " << num_carmichael << endl;
#endif
}

	}
  	catch (EOF_Error e){
	  cerr << "catch: Read past end of file!\n";
  } catch(...)
  {}
  	
  	
    cerr << "Done\n";
  	return 0;
}




