#include "csstest12.h"
#include <QDebug>
#include <exception>

using namespace std;

int CssTest12::BIT_FLIP = 1;

long bits_usedS = 0;

inline bool check_exist_fileS (const std::string& name) {
    ifstream f(name.c_str());
    return f.good();
}

struct EOF_ErrorS
{
    int e;
    EOF_ErrorS(int e2) { e = e2; }
};

unsigned long long total_readS=0;

class BitSeqS  // sequence of bits from a raw binary file
{
    private:
    ifstream in;

    char byte;	// current byte read from stream
    int offset;  	// last bit 7..0 of byte used
    long bitcnt;
    long total_bits_read;

    public:
  BitSeqS(const char *fname) : in(fname) { offset=-1; bitcnt=0; total_bits_read=0; }
    ~BitSeqS() { in.close(); }
    int eof() { return (in.fail() && in.eof()); }

    char getbit()
    {
      bitcnt++;   // MS: I believe this statement should be omitted, as the getbits function, from which it is
                  //     called, already increases the bitcnt variable by cnt. Still, we quote the resulting value for comparison.
if(CssTest12::BIT_FLIP)
{
          if (offset==-1) { in.get(byte); byte = ~byte; offset=7; }
}
else
{
          if (offset==-1) { in.get(byte); offset=7; }
}
      return byte & 1<<offset-- ? 1 : 0;
    }

        mpz_class getbits(int cnt)
    {
      bitcnt += cnt;
      total_bits_read += cnt;
        mpz_class t(0);

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
                //cerr << "read byte:" << std::hex << (unsigned int) byte << endl;
if(CssTest12::BIT_FLIP)
        byte= ~byte;
                //cerr << "comp byte:" << std::hex << (unsigned int) byte << endl;
        if (in.eof()) throw EOF_ErrorS(1);
        t = t*256+((unsigned char) byte);
        cnt -= 8;
        }

        // slow version (continue by bits)
        //
        while (cnt--) { t = t*2+getbit(); }
        if (in.eof()) throw EOF_ErrorS(2);
        return t;
    }

    long count() const { return bitcnt; }
    long count_all() const { return total_bits_read; }
        void ignorebits(int cnt) { bitcnt -= cnt; }
};



static BitSeqS *inbits;

bool CssTest12::solovaytest(mpz_class &n)
{

    try
    {
  mpz_class nm1(n), x(1L), y;
  nm1 = nm1 - 1L;

  mpz_class a(0);

  int cnt = mpz_sizeinbase(n.get_mpz_t(),2);
if(VERBOSES)
{
  res += "length of test string=" + QString::number(cnt) + "\n";
  //******************************* Emit Signal Verbose
      emit verboseData(res);
      res = "";
}


static unsigned long loopcount = 0; // *************************************

  do {
      a = inbits->getbits(cnt);
       total_readS += cnt;
       if (a==0 || a>= n)
     {
if(VERBOSES)
{
           res += "\nReject witness: " + QString::number(a.get_ui()) + "\n";
           res += "As bit string: " + QString::fromStdString(a.get_str(2)) + "\n"; // MS: display the witness integer in binary (0/1) format
           //******************************* Emit Signal Verbose
           emit verboseData(res);
           res = "";
}

       inbits->ignorebits(cnt);

     }
       else break;
  } while (true);


    bits_usedS += cnt;

if(VERBOSES)
{
  res += "\nUse witness=" + QString::number(a.get_ui()) + "\n";
  res += "Witness as bit string: " + QString::fromStdString(a.get_str(2)) + "\n"; // MS: display the witness integer in binary (0/1) format
  //******************************* Emit Signal Verbose
  emit verboseData(res);
  res = "";
}


  int jacobi = mpz_jacobi(a.get_mpz_t(), n.get_mpz_t());

  if (jacobi==0) return true;

  mpz_class nm1d2(nm1);
  nm1d2 = nm1d2 / 2;

  mpz_powm(y.get_mpz_t(), a.get_mpz_t(), nm1d2.get_mpz_t(), n.get_mpz_t());

  if ((jacobi==-1 && y==nm1) || (jacobi==1 && y==1))
    {
      // cout << "Test failed" << endl;
      return false;
    }

    }catch(...)
    {
    }
  return true;
}

void CssTest12::StartTest()
{
    res = "";
    if (!check_exist_fileS(path.toStdString()))
        { res += "Input file " + path + " does not exist!\n"; return; }
    if (!check_exist_fileS(carmichaelPath.toStdString()))
        { res += "CM number file not found!\n"; return; }


    unsigned long global_offset = gOffset;
    unsigned long long carm_count = 0;

    int cm_max_length = 20; // maximum number of digits of Carmichael numbers to be tested

      std::ifstream file(carmichaelPath.toStdString());  // MS: file containing the Carmichael numbers
      std::string str;

      if(!file){
           res +="Error: Carmichael file not found.\n";
       return;
       }


      // Arguments: input bit filename plus an optional read offset from bit file
      inbits = new BitSeqS(path.toStdString().c_str()); // random bit source filename
      int maxk=0;  		  // max number of tests needed per composite.

      if (global_offset > 0)
      {
//        global_offset = atoi(argc[2]);
        inbits->getbits(global_offset); // skip some bits
        //total_readS += global_offset;
      }

      //mpz_class n; 	          // input composite product

  try
  {
    while ( (std::getline(file, str)) && (str.length() <= cm_max_length)) // MS: read the file containing the Carmichael numbers line by line
      {
        carm_count++;
        mpz_class n(str.c_str(), 10);  	          // CM number to be tested

  if(VERBOSES)
   {
        res +=  "\n*****************************\n";
        res += "n=" + QString::number(n.get_ui()) + "\n";
        res += "*****************************\n\n";
  }


         int i; for (i=1; true; i++)
         {
           if (solovaytest(n)) break;
         }
         if (i>maxk) maxk=i;
         //bits_usedS += i*mpz_sizeinbase(n.get_mpz_t(),2);

  if(VERBOSES)
  {
         res += "tests needed " + QString::number(i) + " (max " + QString::number(maxk) + ")\n";
//         qDebug() << "tests needed " + QString::number(i) + " (max " + QString::number(maxk) + ")\n";
         //******************************* Emit Signal Verbose
             emit verboseData(res);
             res = "";
  }
      }

  }
  catch (EOF_ErrorS e)
  {
      res += "Read past end of file!\n";
  } catch(...)
 {
 }

  if(VERBOSES)
   {
   res += "\nTotal bits used (Abbott original code -- disregard): " + QString::number(inbits->count());
   res += "\nTotal bits used (MS modified code): " + QString::number(bits_usedS);
   res += "\nTotal bits read: " + QString::number(inbits->count_all()) + "\n";
   emit verboseData(res);
   res = "";
   }

  //******************************* Emit Signal Verbose


   // output: file name | offset | max_k | bits used (MS) | bits used (Abbott) | total bits read | CM numbers tested"
  if(CssTest12::BIT_FLIP)
   res += path + "[comp] " + QString::number(global_offset) + " " + QString::number(maxk) + " " + QString::number(bits_usedS) + " " + QString::number(inbits->count()) + " " + QString::number(total_readS) + " " + QString::number(carm_count) + "\n";
  else
   res += path + " " + QString::number(global_offset) + " " + QString::number(maxk) + " " + QString::number(bits_usedS) + " " + QString::number(inbits->count()) + " " + QString::number(total_readS) + " " + QString::number(carm_count) + "\n";


   emit finished(res);
}


void CssTest12::setPath(QString str)
{ path = str; }
void CssTest12::setCarmichaelPath(QString str)
{ carmichaelPath = str; }
void CssTest12::setGlobalOffset(unsigned long long offset)
{ gOffset = offset; }

void CssTest12::setBitFlip(int bitFlip)
{ BIT_FLIP = bitFlip; }

void CssTest12::setVerbose(int verbose)
{ VERBOSES = verbose; }



QString CssTest12::getResult() const
{ return res; }
