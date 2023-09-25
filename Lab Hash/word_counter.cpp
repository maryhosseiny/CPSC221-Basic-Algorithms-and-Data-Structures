/**
 * @file word_counter.cpp
 * Implementation of the WordFreq class.
 *
 * @author Chase Geigle
 * @date Spring 2011
 * @date Spring 2012
 */

using std::cout;
using std::endl;
using std::ifstream;
using std::istringstream;
using std::pair;
using std::string;
using std::vector;

template <template <class K, class V> class Dict>
WordFreq<Dict>::WordFreq(const string& filename) : dict(256) {
    /**
     * @todo Implement this function.
     * @see char_counter.cpp if you're having trouble.
     */
     TextFile infile(filename);
     while ((infile.good())) dict[infile.getNextWord()]++;
}

template <template <class K, class V> class Dict>
vector<pair<string, int>> WordFreq<Dict>::getWords(int threshold) {
    vector<pair<string, int>> ret;
    /**
     * @todo Implement this function.
     * @see char_counter.cpp if you're having trouble.
     */

    // (void)threshold;  // prevent warnings... When you implement this function, remove this line.
    for (auto& p : dict) {
        if (p.second >= threshold) ret.push_back(p);
    }
    return ret;
}
