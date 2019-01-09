/******************************************************************************
*                                                                             *
* randwrite.cc                                                                *  
* Xingyu He                                                                   *
* Project 5  randwrite                                                             *
* Apr 15 2018                                                                 *
*                                                                             *
* This program constructs sentence from a piece of text by randomly selecting *
* a groupd of continuous letters in the piece of text(seed) of length k  and  *
* randomly attach letters that occur after the seed in the piece of text      *
* the seed is then updated to the last k letters. The process is repeated     *
* until the desired length is reached                                         *
******************************************************************************/
#include "list.h"
#include <iostream>
#include <fstream>
#include <cstdlib> 
#include <cassert>
#include <ctime>

using namespace std;

// initialize seed randomly
string seed_init(size_t k, list<char> & text) {

    // create variables for later use
    size_t text_size = text.size();
    string seed;

    // randomly initialize a number smaller than the size of the text
    size_t random_index = rand() % text_size;

    // get the consecutive texts after the randomly selected index that
    // is the length of k
    for (size_t i = 0; i < k; i++) 
        seed += text.get(random_index + i);

    return seed;
}


// all occurences of the seed and find the letters after all the occurences
// and return the randomly chosen letter
char find_all(list<char> & text, string seed)
{
    // possible_follow is a list all the letters followed after the 
    // occurrences of seed
    list<char> possible_follow;
    // starting_index is the index at which the first for loop starts looking
    // for letters in seed
    int starting_index;
    int k = seed.length();
    int text_length = text.size();

    // this for loop iterates through all the letters in text
    for (int i = 0; i < text_length; i++) {
        starting_index = i; 
        
        // this for loop checks whether the letter 
        // in text corresponds to the letters in seed orderly
        for (;text.get(i) == seed[i - starting_index]; i++) {

            // if the for loop reaches the end of the seed, the next letter
            // after the seed is attached to possible_follow list. Break out 
            // of this current loop if one possible letter is found
            if (size_t(i - starting_index + 1) == k) {
                possible_follow.add(text.get(i + 1), possible_follow.size());
                break;
            }
        }
        // repeat this process until the text is exhausted
    }

    // if no characters can be found after seed, return null
    if (possible_follow.size() == 0)
        return NULL;

    // otherwise return a randomly chosen 
    return possible_follow.get(rand() % possible_follow.size());

}


// this function is main function that handles all the helper functions 
// to do k analysis
string k_analysis(size_t k, list<char> & text, size_t length) {

    // randomly initialize seed
    string seed = seed_init(k, text);   
    // result would be the first seed and all the consecutive letters after
    // it from find_all function
    string result = seed;
    // randomly chosen character all the letters that follow seed
    char choosen_char;

    // this for loop will iterate until the length of the word desired is 
    // reached
    for (size_t i = 0; i < length; i++) {
        // randomly chosen character all the letters that follow seed
        choosen_char = find_all(text, seed);
        // if not a character is found, call this function again so with less 
        // length and add what this current function has obtained 
        if (!choosen_char)
            return result + k_analysis(k, text, length - result.length());

        // change the seed to the orignal seed without the first letter and 
        // add the newly selected character
        seed = seed.substr(1,k - 1) + choosen_char;
        // attach the newly chosen cahracter to the result
        result += choosen_char;
    }
    return result;
}


int main(int argc, char ** argv) {
    
    assert(argc == 5);
    
    // make sure randomization is different at runtime
    srand(time(NULL));

    // get input variables from terminal
    size_t k = atoi(argv[1]);
    size_t length = atoi(argv[2]);

    ifstream source;
    source.open(argv[3]);

    // read file
    int c = 0;
    list<char> text;


    while (c != EOF) {
    c = source.get();
    // convert line breakers into spaces
    if (c == 10)
        text.add(' ',text.size());
    else
        text.add((char)c, text.size());
    }
    source.close();

    // get the result from k_analysis
    string brut_force_shakspare = k_analysis(k, text, length);
    cout<< "The result of the random writer is:" << brut_force_shakspare <<endl;

    // write result into result file
    ofstream result;
    result.open(argv[4]);
    result << brut_force_shakspare;
    result.close();
}
