#include "boreltest.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <cassert>
#include <cmath>
#include <sys/stat.h>
#include <QDebug>

#define ALLOFFSETS 0
//#define ALLOFFSETS 1

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

class BitSeq  // sequence of bits from a raw binary file
{
    private:
    ifstream in;

    char byte;	// current byte read from stream
    int offset;  	// last bit 7..0 of byte used

    public:
    BitSeq(const char *fname) : in(fname) { offset=-1; }
    ~BitSeq() { in.close(); }
    int eof() { return (in.fail() && in.eof()); }

    char getbit()
    {
          if (offset==-1) { in.get(byte); offset=7; }
      return byte & 1<<offset-- ? 1 : 0;
    }

        unsigned int getbits(int cnt)
    {
        unsigned int t = 0;

        if (offset < cnt)   // can we finish off current byte?
        {// note: if offset == -1 then t will still be 0
          t = byte & (1<<(offset+1))-1;
        cnt -= offset+1;
        offset=-1;
        }

        // fast version (by bytes)
        //
            if (cnt>=8) offset=-1;  // set once
        while (cnt>=8)
        {
        in.get(byte);
        if (in.eof()) throw EOF_Error(1);
//		assert( !in.eof() );	// more bits in stream?
        t = t*256+((unsigned char) byte);
        cnt -= 8;
        }

        // slow version (continue by bits)
        //
        while (cnt--) { t = t*2+getbit(); }
        if (in.eof()) throw EOF_Error(2);
        return t;
    }
};
void BorelTest::setPath(QString path)
{
    this->path = path;
}

void BorelTest::StartTest()
{
    //assert(argn==3);  // input bit filename and bit length to inspect.

    QString result = "";
    if (!check_exist_file(path.toStdString()))
    { result += "Input file " + path + " does not exist!"; return; }

    unsigned long long int seq_length = 0;

    double output[5];

    for (int n = 1; n <= 4; n++)
      {

        //cout << "Counting all length n = " << n << " bit strings in file "
        //	 << argc[1] << endl;

    unsigned int strs = 1 << n; // number of bit strings to find


    vector<unsigned int> cnts(strs,0);

      BitSeq inbits(path.toStdString().c_str());
      unsigned int cnt = 0;	// counter for number of strings read
      try{
        while (true){
      unsigned int b = inbits.getbits(n); cnt++;
      cnts[b] = cnts[b]+1;
        }
      }
      catch (EOF_Error e){
        //cerr << "read " << e.e << '/'<<  cnt << " substrings\n";
      }

      //cout << "Occurence: ";
      //for (unsigned int i=0; i < strs; i++)
      //cout<<cnts[i]<<' ';
    //cout << endl;

      if (n==1) { seq_length = cnt; }

    //cout << "seq length over alphabet = " << cnt << endl;
    unsigned long int minval =  *min_element(cnts.begin(), cnts.end());
    unsigned long int maxval =  *max_element(cnts.begin(), cnts.end());

    double diff_minval = fabs(double(minval)/double(cnt)-double(pow(2,-n)));
    double diff_maxval = fabs(double(maxval)/double(cnt)-double(pow(2,-n)));

  if(VERBOSE)
  {
    result += "min: "  +  QString::number(minval) + "\n"; // minimum of the count
    result += "max: " + QString::number(maxval) + "\n"; // maximum of the count
    result +=  QString::number(cnt) + "\n";
    result +=  QString::number(double(minval)/double(cnt)) + "\n";
    result +=  QString::number(double(maxval)/double(cnt)) + "\n";
    result += QString::number(double(pow(2,-n))) + "\n";
    result += "(" + QString::number(diff_minval) + ", " + QString::number(diff_maxval) + ") of " + QString::number(cnt) + "\n";
  }


    if (diff_minval >= diff_maxval) { output[n]=diff_minval; }
    else { output[n]=diff_maxval;}

      }

    double maxresult = 0.0;

    double norm = double( sqrt( double(seq_length)/ log2(double(seq_length)) )); // correct version
    //double norm = log2(double(seq_length)); // abbott version

    for (int n = 1; n <= 4; n++)
      {
        if (output[n] > maxresult) { maxresult = output[n]; }
      }

    result += path + " " + QString::number(maxresult*norm) + "\n";

    emit finished(result);

}

void BorelTest::setVerbose(int verbose)
{
    this->VERBOSE = verbose;
}

