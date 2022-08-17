#include "nist_sp800_90btest.h"
#include <getopt.h>
#include <limits.h>

using namespace std;

void NIST_SP800_90BTest::noniidTest()
{
//    bool initial_entropy, all_bits;
//    int verbose = 1; // setting it to 1 to get all the result
//    char file_path[1024];
//    double H_original, H_bitstring, ret_min_entropy;
//    data_t data;
//    int opt;
//    double bin_t_tuple_res = -1.0, bin_lrs_res = -1.0;
//    double t_tuple_res = -1.0, lrs_res = -1.0;
//    unsigned long subsetIndex=ULONG_MAX;
//    unsigned long subsetSize=0;
//    unsigned long long inint;
//    char *nextOption;

//    data.word_size = 0;

//        initial_entropy = true;
//        all_bits = true;

////        while ((opt = getopt(argc, argv, "icatvl:")) != -1) {
////                switch(opt) {
////                        case 'i':
////                                initial_entropy = true;
////                                break;
////                        case 'c':
////                                initial_entropy = false;
////                                break;
////                        case 'a':
////                                all_bits = true;
////                                break;
////                        case 't':
////                                all_bits = false;
////                                break;
////                        case 'v':
////                                verbose++;
////                                break;
////            case 'l':
////                inint = strtoull(optarg, &nextOption, 0);
////                if((inint > ULONG_MAX) || (errno == EINVAL) || (nextOption == NULL) || (*nextOption != ',')) {
////                    print_usage();
////                }
////                subsetIndex = inint;

////                nextOption++;

////                inint = strtoull(nextOption, NULL, 0);
////                if((inint > ULONG_MAX) || (errno == EINVAL)) {
////                    print_usage();
////                }
////                subsetSize = inint;
////                break;
////                        default:
////                                print_usage();
////                }
////        }

////        argc -= optind;
////        argv += optind;

////    // Parse args
////    if((argc != 1) && (argc != 2)){
////        printf("Incorrect usage.\n");
////        print_usage();
////    }
//    // get filename
//    sprintf(file_path, "%s", path.toStdString().c_str());

////    if(argc == 2) {
////        // get bits per word
////        inint = atoi(argv[1]);
////        if(inint < 1 || inint > 8){
////            printf("Invalid bits per symbol.\n");
////            print_usage();
////        } else {
////            data.word_size = inint;
////        }
////    }

//    try{

//    if(verbose>0) emit verboseData("Opening file:" + QString(file_path) + "\n");

//    if(!read_file_subset(file_path, &data, subsetIndex, subsetSize)){
//        res += "Error reading file.\n";
//        emit finished(res);
//        return;
//    }
//    if(verbose > 0) emit verboseData("Loaded " + QString::number(data.len) + " samples of "+ QString::number(data.alph_size) + " distinct "+ QString::number(data.word_size) +"-bit-wide symbols\n");

//    if(data.alph_size <= 1){
//        emit verboseData("Symbol alphabet consists of 1 symbol. No entropy awarded...\n");
//        free_data(&data);
//        emit finished(res);
//        return;
//    }

//    if(!all_bits && (data.blen > MIN_SIZE)) data.blen = MIN_SIZE;

//    if((verbose>0) && ((data.alph_size > 2) || !initial_entropy)) res += "Number of Binary Symbols: " + QString::number(data.blen) + "\n";
//    if(data.len < MIN_SIZE) emit verboseData("\n*** Warning: data contains less than "+ QString::number(MIN_SIZE) +" samples ***\n\n");
//    if(verbose>0){
//        if(data.alph_size < (1 << data.word_size)) res += "\nSymbols have been translated.\n";
//    }

//    // The maximum min-entropy is -log2(1/2^word_size) = word_size
//    // The maximum bit string min-entropy is 1.0
//    H_original = data.word_size;
//    H_bitstring = 1.0;

//    if(verbose <= 1) {
//        emit verboseData("\nRunning non-IID tests...\n\n");
//        emit verboseData("Running Most Common Value Estimate...\n");
//    }

//    // Section 6.3.1 - Estimate entropy with Most Common Value
//    if(((data.alph_size > 2) || !initial_entropy)) {
//        ret_min_entropy = most_common(data.bsymbols, data.blen, 2, verbose, "Bitstring");
//        if(verbose == 1) emit verboseData("\tMost Common Value Estimate (bit string) = "+ QString::number(ret_min_entropy) +" / 1 bit(s)\n");
//        H_bitstring = min(ret_min_entropy, H_bitstring);
//    }

//    if(initial_entropy) {
//        ret_min_entropy = most_common(data.symbols, data.len, data.alph_size, verbose, "Literal");
//        if(verbose == 1) emit verboseData("\tMost Common Value Estimate = "+ QString::number(ret_min_entropy) +" / "+ QString::number(data.word_size) +" bit(s)\n");
//        H_original = min(ret_min_entropy, H_original);
//    }

//    if(verbose <= 1) emit verboseData("\nRunning Entropic Statistic Estimates (bit strings only)...\n");

//    // Section 6.3.2 - Estimate entropy with Collision Test (for bit strings only)
//    if(((data.alph_size > 2) || !initial_entropy)) {
//        ret_min_entropy = collision_test(data.bsymbols, data.blen, verbose, "Bitstring");
//        if(verbose == 1) emit verboseData("\tCollision Test Estimate (bit string) = "+ QString::number(ret_min_entropy) +" / 1 bit(s)\n");
//        H_bitstring = min(ret_min_entropy, H_bitstring);
//    }

//    if(initial_entropy && (data.alph_size == 2)) {
//        ret_min_entropy = collision_test(data.symbols, data.len, verbose, "Literal");
//        if(verbose == 1) emit verboseData("\tCollision Test Estimate = "+ QString::number(ret_min_entropy) +" / 1 bit(s)\n");
//        H_original = min(ret_min_entropy, H_original);
//    }

//    // Section 6.3.3 - Estimate entropy with Markov Test (for bit strings only)
//    if(((data.alph_size > 2) || !initial_entropy)) {
//        ret_min_entropy = markov_test(data.bsymbols, data.blen, verbose, "Bitstring");
//        if(verbose == 1) emit verboseData("\tMarkov Test Estimate (bit string) = "+ QString::number(ret_min_entropy) +" / 1 bit(s)\n");
//        H_bitstring = min(ret_min_entropy, H_bitstring);
//    }

//    if(initial_entropy && (data.alph_size == 2)) {
//        ret_min_entropy = markov_test(data.symbols, data.len, verbose, "Literal");
//        if(verbose == 1) emit verboseData("\tMarkov Test Estimate = "+ QString::number(ret_min_entropy) +" / 1 bit(s)\n");
//        H_original = min(ret_min_entropy, H_original);
//    }

//    // Section 6.3.4 - Estimate entropy with Compression Test (for bit strings only)
//    if(((data.alph_size > 2) || !initial_entropy)) {
//        ret_min_entropy = compression_test(data.bsymbols, data.blen, verbose, "Bitstring");
//        if(ret_min_entropy >= 0){
//            if(verbose == 1) emit verboseData("\tCompression Test Estimate (bit string) = "+ QString::number(ret_min_entropy) +" / 1 bit(s)\n");
//            H_bitstring = min(ret_min_entropy, H_bitstring);
//        }
//    }

//    if(initial_entropy && (data.alph_size == 2)) {
//        ret_min_entropy = compression_test(data.symbols, data.len, verbose, "Literal");
//        if(verbose == 1) emit verboseData("\ttCompression Test Estimate = "+ QString::number(ret_min_entropy) +" / 1 bit(s)\n");
//        H_original = min(ret_min_entropy, H_original);
//    }

//    if(verbose <= 1) emit verboseData("\nRunning Tuple Estimates...\n");

//    // Section 6.3.5 - Estimate entropy with t-Tuple Test

//    if(((data.alph_size > 2) || !initial_entropy)) {
//        SAalgs(data.bsymbols, data.blen, 2, bin_t_tuple_res, bin_lrs_res, verbose, "Bitstring");
//        if(bin_t_tuple_res >= 0.0) {
//            if(verbose == 1) emit verboseData("\tT-Tuple Test Estimate (bit string) = "+ QString::number(bin_t_tuple_res) +" / 1 bit(s)\n");
//            H_bitstring = min(bin_t_tuple_res, H_bitstring);
//        }
//    }

//    if(initial_entropy){
//        SAalgs(data.symbols, data.len, data.alph_size, t_tuple_res, lrs_res, verbose, "Literal");
//        if(t_tuple_res >= 0.0) {
//            if(verbose == 1) emit verboseData("\tT-Tuple Test Estimate = "+ QString::number(t_tuple_res) +" / "+QString::number(data.word_size) +" bit(s)\n");
//            H_original = min(t_tuple_res, H_original);
//            }
//    }

//    // Section 6.3.6 - Estimate entropy with LRS Test
//    if(((data.alph_size > 2) || !initial_entropy)) {
//        if(verbose == 1) emit verboseData("\tLRS Test Estimate (bit string) = "+ QString::number(bin_lrs_res) +" / 1 bit(s)\n");
//        H_bitstring = min(bin_lrs_res, H_bitstring);
//    }

//    if(initial_entropy) {
//        if(verbose == 1) emit verboseData("\tLRS Test Estimate = "+ QString::number(lrs_res) +" / "+QString::number(data.word_size) +" bit(s)\n");
//        H_original = min(lrs_res, H_original);
//    }

//    if(verbose <= 1) emit verboseData("\nRunning Predictor Estimates...\n");

//    if(((data.alph_size > 2) || !initial_entropy)) {
//        // Section 6.3.7 - Estimate entropy with Multi Most Common in Window Test
//        ret_min_entropy = multi_mcw_test(data.bsymbols, data.blen, 2, verbose, "Bitstring");
//        if(ret_min_entropy >= 0){
//            if(verbose == 1) emit verboseData("\tMulti Most Common in Window (MultiMCW) Prediction Test Estimate (bit string) = "+ QString::number(ret_min_entropy) +" / 1 bit(s)\n");
//            H_bitstring = min(ret_min_entropy, H_bitstring);
//        }
//    }

//    if(initial_entropy){
//        ret_min_entropy = multi_mcw_test(data.symbols, data.len, data.alph_size, verbose, "Literal");
//        if(ret_min_entropy >= 0){
//            if(verbose == 1) emit verboseData("\tMulti Most Common in Window (MultiMCW) Prediction Test Estimate = "+ QString::number(ret_min_entropy) +" / "+QString::number(data.word_size) + " bit(s)\n");
//            H_original = min(ret_min_entropy, H_original);
//        }
//    }

//    // Section 6.3.8 - Estimate entropy with Lag Prediction Test
//    if(((data.alph_size > 2) || !initial_entropy)) {
//        ret_min_entropy = lag_test(data.bsymbols, data.blen, 2, verbose, "Bitstring");
//        if(ret_min_entropy >= 0){
//            if(verbose == 1) emit verboseData("\tLag Prediction Test Estimate (bit string) = "+ QString::number(ret_min_entropy) +" / 1 bit(s)\n");
//            H_bitstring = min(ret_min_entropy, H_bitstring);
//        }
//    }

//    if(initial_entropy){
//        ret_min_entropy = lag_test(data.symbols, data.len, data.alph_size, verbose, "Literal");
//        if(ret_min_entropy >= 0){
//            if(verbose == 1) emit verboseData("\tLag Prediction Test Estimate = "+ QString::number(ret_min_entropy) +" / "+ QString::number(data.word_size) +" bit(s)\n");
//            H_original = min(ret_min_entropy, H_original);
//        }
//    }

//    // Section 6.3.9 - Estimate entropy with Multi Markov Model with Counting Test (MultiMMC)
//    if(((data.alph_size > 2) || !initial_entropy)) {
//        ret_min_entropy = multi_mmc_test(data.bsymbols, data.blen, 2, verbose, "Bitstring");
//        if(ret_min_entropy >= 0){
//            if(verbose == 1) emit verboseData("\tMulti Markov Model with Counting (MultiMMC) Prediction Test Estimate (bit string) = "+ QString::number(ret_min_entropy) +" / 1 bit(s)\n");
//            H_bitstring = min(ret_min_entropy, H_bitstring);
//        }
//    }
//    if(initial_entropy){
//        ret_min_entropy = multi_mmc_test(data.symbols, data.len, data.alph_size, verbose, "Literal");
//        if(ret_min_entropy >= 0){
//            if(verbose == 1) emit verboseData("\tMulti Markov Model with Counting (MultiMMC) Prediction Test Estimate = "+ QString::number(ret_min_entropy) +" / "+ QString::number(data.word_size) +" bit(s)\n");
//            H_original = min(ret_min_entropy, H_original);
//        }
//    }

//    // Section 6.3.10 - Estimate entropy with LZ78Y Test
//    if(((data.alph_size > 2) || !initial_entropy)) {
//        ret_min_entropy = LZ78Y_test(data.bsymbols, data.blen, 2, verbose, "Bitstring");
//        if(ret_min_entropy >= 0){
//            if(verbose == 1) emit verboseData("\tLZ78Y Prediction Test Estimate (bit string) = "+ QString::number(ret_min_entropy) +" / 1 bit(s)\n");
//            H_bitstring = min(ret_min_entropy, H_bitstring);
//        }
//    }

//    if(initial_entropy){
//        ret_min_entropy = LZ78Y_test(data.symbols, data.len, data.alph_size, verbose, "Literal");
//        if(ret_min_entropy >= 0){
//            if(verbose == 1) emit verboseData("\tLZ78Y Prediction Test Estimate = "+ QString::number(ret_min_entropy) +" / "+ QString::number(data.word_size) +" bit(s)\n");
//            H_original = min(ret_min_entropy, H_original);
//        }
//    }

//    if(verbose <= 1) {
//        emit verboseData("\n");
//        if(initial_entropy){
//           emit verboseData("H_original: "+ QString::number(H_original) +"\n");
//            if(data.alph_size > 2) {
//                res += "H_bitstring: "+ QString::number(H_bitstring) +"\n\n";
//                res += "min(H_original, "+ QString::number(data.word_size) +" X H_bitstring): "+ QString::number(min(H_original, data.word_size*H_bitstring)) +"\n\n";

//                emit verboseData(res);
//                res = "";
//            }
//        } else emit verboseData("h': "+ QString::number(H_bitstring) +"\n");
//    } else {
//        double h_assessed = data.word_size;

//        if((data.alph_size > 2) || !initial_entropy) {
//            h_assessed = min(h_assessed, H_bitstring * data.word_size);
//            emit verboseData("H_bitstring = "+ QString::number(H_bitstring) +"\n");
//        }

//        if(initial_entropy) {
//            h_assessed = min(h_assessed, H_original);
//            emit verboseData("H_original: "+ QString::number(H_original) +"\n");
//        }

//        emit verboseData("Assessed min entropy: "+ QString::number(h_assessed) +"\n");
//    }


//    free_data(&data);
    try{

        char result[1024];    *result = '\0';
        res = "";

        QString c = commandNONIID + path;

        FILE* cmd = popen(c.toStdString().c_str(), "r");
        if (cmd)
        {
            while (!feof(cmd))
                if (fgets(result, 1024, cmd) != NULL) emit verboseData(result);
            if(pclose(cmd) == -1) res = "Process Terminated!";
        }
    }catch(...)
    {
        printf("Somthing Went Wrong!\n");
    }

    emit finished(res);
}

void NIST_SP800_90BTest::iidTest()
{

//    bool initial_entropy, all_bits;
//    int verbose = 1; // setting it to 1 to get all the result
//    double rawmean, median;
//    char file_path[1024];
//    data_t data;
//    int opt;
//    unsigned long subsetIndex = ULONG_MAX;
//    unsigned long subsetSize = 0;
//    unsigned long long inint;
//    char *nextOption;

//    data.word_size = 0;
//    initial_entropy = true;
//    all_bits = true;




//    try{
//    // get filename
//    sprintf(file_path, "%s", path.toStdString().c_str());


//    if(verbose > 0){
//        emit verboseData("Opening file: "+ QString(file_path) + "\n");
//    }

//    if(!read_file_subset(file_path, &data, subsetIndex, subsetSize)){
//        res += "Error reading file.\n";
//        emit finished(res);
//        return;
//    }
//    if(verbose > 0) emit verboseData( "Loaded "+ QString::number(data.len) +" samples of "+ QString::number(data.alph_size) +" distinct "+ QString::number(data.word_size) +"-bit-wide symbols\n");

//    if(data.alph_size <= 1){
//        res += "Symbol alphabet consists of 1 symbol. No entropy awarded...\n";
//        free_data(&data);

//        emit finished(res);
//        return;
//    }

//    if(!all_bits && (data.blen > MIN_SIZE)) data.blen = MIN_SIZE;

//    if((verbose > 0) && ((data.alph_size > 2) || !initial_entropy)) emit verboseData("Number of Binary samples: "+ QString::number(data.blen)+"\n");
//    if(data.len < MIN_SIZE) emit verboseData("\n*** Warning: data contains less than "+ QString::number(MIN_SIZE) +" samples ***\n\n");
//    if(verbose > 0){
//        if(data.alph_size < (1 << data.word_size)) emit verboseData("\nSamples have been translated\n");
//    }

//    // Calculate baseline statistics
//    int alphabet_size = data.alph_size;
//    int sample_size = data.len;

//    emit verboseData("Calculating baseline statistics...\n");
//    calc_stats(&data, rawmean, median);

//    if(verbose > 0){
//        res += "\tRaw Mean: "+ QString::number(rawmean) +"\n";
//        res += "\tMedian: "+ QString::number(median) +"\n";
//        res += "\tBinary: " + QString(alphabet_size == 2 ? "true" : "false") + "\n\n";

//        emit verboseData(res);
//        res = "";
//    }

//    double H_original = data.word_size;
//    double H_bitstring = 1.0;

//    // Compute the min-entropy of the dataset
//    if(initial_entropy) {
//        H_original = most_common(data.symbols, sample_size, alphabet_size, verbose, "Literal");
//    }

//    if(((data.alph_size > 2) || !initial_entropy)) {
//        H_bitstring = most_common(data.bsymbols, data.blen, 2, verbose, "Bitstring");
//    }

//        if(verbose <= 1) {
//                if(initial_entropy){
//                        emit verboseData("H_original: "+ QString::number(H_original) + "\n");
//                        if(data.alph_size > 2) {
//                               emit verboseData("H_bitstring: "+ QString::number(H_bitstring) +"\n");
//                               emit verboseData("min(H_original, "+ QString::number(data.word_size) +" X H_bitstring): " + QString::number(min(H_original, data.word_size*H_bitstring)) +"\n");
//                        }
//                } else emit verboseData("h': "+ QString::number(H_bitstring) +"\n");
//        } else {
//                double h_assessed = data.word_size;

//                if((data.alph_size > 2) || !initial_entropy) {
//                        h_assessed = min(h_assessed, H_bitstring * data.word_size);
//                        emit verboseData("H_bitstring = "+ QString::number(H_bitstring) + "\n");
//                }

//                if(initial_entropy) {
//                        h_assessed = min(h_assessed, H_original);
//                        emit verboseData("H_original: "+ QString::number(H_original) +"\n");
//                }

//                emit verboseData("Assessed min entropy: "+ QString::number(h_assessed) +"\n");
//        }

//    emit verboseData("\n");

//    // Compute chi square stats
//    bool chi_square_test_pass = chi_square_tests(data.symbols, sample_size, alphabet_size, verbose);

//    if(chi_square_test_pass){
//        emit verboseData("** Passed chi square tests\n\n");
//    }else{
//        emit verboseData("** Failed chi square tests\n\n");
//    }

//    // Compute length of the longest repeated substring stats
//    bool len_LRS_test_pass = len_LRS_test(data.symbols, sample_size, alphabet_size, verbose, "Literal");

//    if(len_LRS_test_pass){
//        emit verboseData("** Passed length of longest repeated substring test\n\n");
//    }else{
//        emit verboseData("** Failed length of longest repeated substring test\n\n");
//    }

//    // Compute permutation stats
//    bool perm_test_pass = permutation_tests(&data, rawmean, median, verbose);

//    if(perm_test_pass){
//        emit verboseData("** Passed IID permutation tests\n\n");
//    }else{
//        emit verboseData("** Failed IID permutation tests\n\n");
//    }

//    free_data(&data);

    try{

        char result[1024];    *result = '\0';
        res = "";

        QString c = commandIID + path;

        FILE* cmd = popen(c.toStdString().c_str(), "r");
        if (cmd)
        {
            while (!feof(cmd))
                if (fgets(result, 1024, cmd) != NULL) emit verboseData(result);
            if(pclose(cmd) == -1) res = "Process Terminated!";
        }


    } catch(...)
    {
        emit verboseData("Somthing Went Wrong!\n");
    }

    emit finished(res);

}

void NIST_SP800_90BTest::startTest()
{
    if(testType == TestType::noniid)
        noniidTest();
    else
        iidTest();

    emit finished(res);
}
void NIST_SP800_90BTest::setTestType(TestType type)
{
    if(type > 1)
        return;
    testType = type;
}
QString NIST_SP800_90BTest::getResult() const
{ return res; }
void NIST_SP800_90BTest::setPath(QString path)
{ this->path =  path; }
