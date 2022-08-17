.pragma library

var font_title;
var font_normal;
var font_eng;
var view;
var pathText;



var EntTestResult = "";
const EntText = "ENT";

var BorelTestResult = "";
const BorelText = "Borel Normality";

var SSTest3Result = "";
var SSTest3FilePath = "";
const SSTest3Text = "CSSS 3";


var SSTest4Result = "";
var SSTest4FilePath = "";
const SSTest4Text = "CSSS 4";

var SSTest12Result = "";
var SSTest12FilePath = "";
const SSTest12Text = "CSSS 1&2";

var NIST_SP800_90BResult = "";
var NIST_SP800_90BText = "‫‫‪NIST ‪‫‪SP800-90B‬‬";

var dieharderTestResult = "";
var dieharderText = "DIEHARDER";

var NIST_SP800_22Result = "";
var NIST_SP800_22Text = "‫‪NIST‬‬ ‫‪SP800-22‬‬";

var outputPath = "";
var outputText = "Output";

const helpText = "DIEHARDER\n----------------\nDIEHARDER is the most famous test suite for testing RNGs. It consists of 31 statistical tests.\n
\n\nNIST SP800-22\n----------------\nNIST SP800-22 is another famous statistical test suite which consists of 15 statistical tests. Each test in this suite evaluates a p-value that should be larger than the significance level.\n
\n\nNIST SP800-90B\n----------------\n
NIST SP800-90B is an Entropy assessment package that provides a standardized means of estimating the quality of a source of entropy. This test assures that a random sequence is independent and identically distributed (IID) and also estimates the min-entropy for the provided data.\n
\n\nENT\n----------------\n
ENT is a series of basic statistical tests that evaluate the random sequence in some elementary features such as Entropy, Chi-square Test, Arithmetic Mean, Monte Carlo Value for Pi, and Serial Correlation Coefficient.\n\n\n
Borel Normality\n----------------\nBorel normality is a necessary condition for algorithmic randomness and incomputability. A random string is considered Borel normal if its metric value is less than 1.\n
\n\nCSSS\n----------------\nThe CSSS tests use random sequences as witnesses to test whether or not a given integer n is composite or prime. They are based on Solovay-Strassen test of primality and Chaitin-Schwartz theorem.\n";

const aboutText = "Pi Randomness Assessment Test (PiRATe)\n-Version 1.1-\n\n
Developed at the Quantum Communication Group\nIranian Center for Quantum Technologies, Tehran - 2022.\n
Authors:\nSoheil Hajibaba\nAmirhosein Dadahkhani\nSeyed Ahmad Madani (amadani@icqts.ir)\n";

//const backgorundColor = "#000005";
//const textColor = "#bbffcb";
const backgorundColor = "#d2e2dc";
const textColor = "#121410";


const testStartMessage = "Starting The Test It Might Take a while...";


function delay(time, root)
{

  var timer = Qt.createQmlObject("import QtQuick 2.13; Timer{ interval: "+ time +"; repeat: false;\
     onTriggered: {}}", root);
  timer.start();
}


