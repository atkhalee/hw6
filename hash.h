#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>
#include<cctype>

typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }
    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const
    {
        // Add your code here
				//string new_string = '/0';
				int digit =0;
				char last;
				std::vector<unsigned long long> temp_vals(5,0);
				for(unsigned long int i=0; i <k.length()/6+1;i++)
				{
					std::vector<HASH_INDEX_T>integralVals (6,0);
					for(int j =0; j<6 && digit !=(int) k.size(); j++, digit++)
					{
						last = k[k.size()-(1+digit)];
						integralVals[5-j] = (last<='9' && last >='0') ? (last-22) : (tolower(last)-'a');	
					}
					temp_vals[4-i] = ((((((integralVals[0]*36)+integralVals[1])* 36 + integralVals[2]) * 36 + integralVals[3]) * 36 + integralVals[4])*36 + integralVals[5]);
				}
				return rValues[0] * temp_vals[0] + rValues[1]* temp_vals[1]+ rValues[2]*temp_vals[2] + rValues[3]*temp_vals[3] + rValues[4]* temp_vals[4];

    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    // HASH_INDEX_T letterDigitToNumber(char letter) const
    // {
    //     // Add code here or delete this helper function if you do not want it
		// 		char ch = tolower(letter);
		// 		int digit;
		// 		for(int i =0; i <=35; i++)
		// 		{
		// 			if ch 
		// 		}
		// 		//then use a loop to run 
    // }

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif
