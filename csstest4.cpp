#include "csstest4.h"
#define _GLIBCXX_USE_C99 1
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

using namespace std;
int CssTest4::BIT_FLIP = 0;

inline bool check_exist_fileS4 (const std::string& name) {
    ifstream f(name.c_str());
    return f.good();
}

struct EOF_ErrorS4
{
    int e;
    EOF_ErrorS4(int e2) { e = e2; }
};

class BitSeqS4  // sequence of bits from a raw binary file
{
    private:
    ifstream in;

    char byte;	// current byte read from stream
    int offset;  	// last bit 7..0 of byte used

    public:
  BitSeqS4(const char *fname) : in(fname) { offset=-1; }
    ~BitSeqS4() { in.close(); }
    int eof() { return (in.fail() && in.eof()); }

    char getbit()
    {
if(CssTest4::BIT_FLIP)
{
      if (offset==-1) { in.get(byte); byte = ~byte; offset=7; }
}
else
{
    if (offset==-1) { in.get(byte);  offset=7; }
}

    return byte & 1<<offset-- ? 1 : 0;
    }

//Nan's code start
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
    if (in.eof()) throw EOF_ErrorS4(1);

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
if(CssTest4::BIT_FLIP)
    byte = ~byte;

        if (in.eof()) throw EOF_ErrorS4(1);

            mpz_ui_pow_ui(tmp.get_mpz_t(),2, total-cnt);
        t += reverse((unsigned char) byte)*tmp;
        cnt -= 8;
    }
//Nan's code end
    // slow version (continue by bits)
    //
    while (cnt)
        {
            mpz_ui_pow_ui(tmp.get_mpz_t(),2, total-cnt);
            t+=getbit()*tmp;
            cnt--;
        }
    if (in.eof()) throw EOF_ErrorS4(2);
    return t;
    }
};

bool *ss_tableS4;

static BitSeqS4 *inbits;

static bool solovaytest(mpz_class &n, mpz_class &b)
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

static bool* cal_ss_tableS4(mpz_class &n)
{
    bool* ss_tableS4 = new bool[n.get_ui()-1];
    for(unsigned long i=0;i<n.get_ui()-1;i++)
     {
         mpz_class a(i+1);
         ss_tableS4[i]=solovaytest(n,a);
     }
     return ss_tableS4;
}

void CssTest4::cssTest4StartTest()
{

    res = "";

    if (!check_exist_fileS4(path.toStdString()))
      { res += "Input file " + path + " does not exist!\n"; return; }

    inbits = new BitSeqS4(path.toStdString().c_str());     // random bit source filename

    int c = cRandom; //store the value of c. c comes from c-random.

    mpz_class J; //store the Carmichael number
    long oddPlusone[] = {9, 15, 21, 25, 27, 33, 35, 39, 45, 49, 51, 55, 57, 63, 65,
                         69, 75, 77, 81, 85, 87, 91, 93, 95, 99, 561 };


//    ofstream resultfile;

    int testrounds = 5;
    int viol_array[100];
    int viol_array_idx = 0;
    int round_count[100];
    unsigned long long total_count = 0;

    for (auto& t : oddPlusone) // MS: read the file containing the Carmichael numbers line by line
    {
        unsigned long long count = 0;
    J = t;
    //cout<<"J = "<<J<<endl;
        if(J==0) return;
        ss_tableS4 = cal_ss_tableS4(J);//Build table for look up for all possible test witnesses w.r.t. J
        int j = mpz_sizeinbase(J.get_mpz_t(),2);// binary legnth of J
        mpz_class J_minus_1(J-1L);
        int bits_used = mpz_sizeinbase(J_minus_1.get_mpz_t(),2);// approximation of binary bits used for 1 bit of J-1 based number.

        c = j-1; //c = floor(log2(J)), since J is not power of 2, c=j-1
        int readLength = j*(j+2*c); // read length according to Chaitin Schwartz theorem


    unsigned long long offset_file = 0;
        while(readLength-offset_file)
      //while(offset_file<testrounds)
        {
        inbits->jumpbits(offset_file);
        //cout<<"starting round "<<(offset_file+1)<<" of "<<readLength<<endl;

            try
            {
                while (true)// loop to go through a random sample with a fixed test number
                {
                    bool flag = true;

                    mpz_class s(0);//Interpret string as an integer

                    s = inbits->getbits(readLength);

                    mpz_class d(0);//store base J-1 bit

                    //Calculate J-1 representation of s (d_kd_{k-1}...d_0)
                    //then do SS(J,1+d_0), SS(J, 1+d_1) ...  until one test says composite
                    while(s>=(J-1L))//Stop when i = k (do not calculate the left most d)
                    {
                        d = s%(J-1L);
                        s = s/(J-1L);

                        //composite = solovaytest(J, d);

                        if (ss_tableS4[d.get_ui()])//not add 1 to d, since the result is stored in index 0 when d=1
                        {
                            flag=false;
                            break;
                        }
                    }

                    if(flag) { count++; } //cout<<"violation, count ="<<count<<endl; }
                }

            }
            catch (EOF_ErrorS4 e){
                delete inbits;
                inbits = new BitSeqS4(path.toStdString().c_str());
            }
            // cout<<"Violations = "<<count<<endl;
            offset_file++;
        }

    // write output to file
//    resultfile.open ("results_SS_test4.txt", ios::out | ios::app);
if(CssTest4::BIT_FLIP)
    res += path + "[comp] ";
else
    res += path + " ";

    res += "J=" + QString::number(J.get_ui()) + " : " + QString::number(count) + " (" + QString::number(offset_file) + ")\n";


    emit verboseData(res);
    res = "";


    // write output to stderr
// #if BIT_FLIP
// 	cout << argc[1] << "[comp] ";
// #else
// 	cout << argc[1] << " ";
// #endif

// 	cout<<": J="<<J<<" : " << count << " (" << offset_file << ")" << endl;

    // record violation counts into array
    round_count[viol_array_idx] =  offset_file;
    viol_array[viol_array_idx] = count;
    viol_array_idx++;
    total_count = total_count + count;

    // initialize new lookup table
    delete ss_tableS4;
        bool *ss_tableS4;
    }

    // write output to file
//    resultfile.open ("results_SS_test4.txt", ios::out | ios::app);
if(CssTest4::BIT_FLIP)
    res += "** " +  path + "[comp] ";
else
    res += "** " + path + " ";

    for (int i=0; i<viol_array_idx; i++)
    {
    res  += QString::number(viol_array[i]) + " (" + QString::number(round_count[i]) + ") ";
    }

    emit verboseData(res);
    res = "";

    res += QString::number(total_count) + "\n";
//    resultfile.close();



    // write output to stderr
//#if BIT_FLIP
//    cout << argc[1] << "[comp] ";
//#else
//    cout << argc[1] << " ";
//#endif
//    for (int i=0; i<viol_array_idx; i++)
//      {
//    cout  << viol_array[i] << " (" << round_count[i] << ") ";
//      }
//    cout << total_count << endl;

}
//CssTest4::CssTest4()
//{

//}

void CssTest4::setPath(QString str)
{ path = str; }

void CssTest4::setCRandom(int cRandom)
{ this->cRandom = cRandom; }

void CssTest4::setBitFlip(int bitFlip)
{ BIT_FLIP = bitFlip; }

QString CssTest4::getResult() const
{ return res; }
