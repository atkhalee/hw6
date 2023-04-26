#ifndef RECCHECK
#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <random>
#include <iomanip>
#include <fstream>
#include <exception>
#endif

#include "boggle.h"

std::vector<std::vector<char> > genBoard(unsigned int n, int seed)
{
	//random number generator
	std::mt19937 r(seed);

	//scrabble letter frequencies
	//A-9, B-2, C-2, D-4, E-12, F-2, G-3, H-2, I-9, J-1, K-1, L-4, M-2, 
	//N-6, O-8, P-2, Q-1, R-6, S-4, T-6, U-4, V-2, W-2, X-1, Y-2, Z-1
	int freq[26] = {9,2,2,4,12,2,3,2,9,1,1,4,2,6,8,2,1,6,4,6,4,2,2,1,2,1};
	std::vector<char> letters;
	for(char c='A'; c<='Z';c++)
	{
		for(int i=0;i<freq[c-'A'];i++)
		{
			letters.push_back(c);
		}
	}
	std::vector<std::vector<char> > board(n);
	for(unsigned int i=0;i<n;i++)
	{
		board[i].resize(n);
		for(unsigned  int j=0;j<n;j++)
		{
			board[i][j] = letters[(r() % letters.size())];
		}
	}
	return board;
}

void printBoard(const std::vector<std::vector<char> >& board)
{
	unsigned int n = board.size();
	for(unsigned int i=0;i<n;i++)
	{
		for(unsigned int j=0;j<n;j++)
		{
			std::cout << std::setw(2) << board[i][j];
		}
		std::cout << std::endl;
	}
}

std::pair<std::set<std::string>, std::set<std::string> > parseDict(std::string fname)
{
	std::ifstream dictfs(fname.c_str());
	if(dictfs.fail())
	{
		throw std::invalid_argument("unable to open dictionary file");
	} 
	std::set<std::string> dict;
	std::set<std::string> prefix;
	std::string word;
	while(dictfs >> word)
	{
		dict.insert(word);
		for(unsigned int i=word.size()-1;i>=1;i--)
		{
			prefix.insert(word.substr(0,i));
		}
	}
	prefix.insert("");
	return make_pair(dict, prefix);
}

std::set<std::string> boggle(const std::set<std::string>& dict, const std::set<std::string>& prefix, const std::vector<std::vector<char> >& board)
{
	std::set<std::string> result;
	for(unsigned int i=0;i<board.size();i++)
	{
		for(unsigned int j=0;j<board.size();j++)
		{
			boggleHelper(dict, prefix, board, "", result, i, j, 0, 1); //horizontally
			boggleHelper(dict, prefix, board, "", result, i, j, 1, 0); //vertically
			boggleHelper(dict, prefix, board, "", result, i, j, 1, 1); //diagonally
		}
	}
	
	return result;
}

bool boggleHelper(const std::set<std::string>& dict, const std::set<std::string>& prefix, const std::vector<std::vector<char> >& board, 
								   std::string word, std::set<std::string>& result, unsigned int r, unsigned int c, int dr, int dc)
{
//add your solution here!
//r and c are current positions on the board
//dr and dc set the sear direction --> they do not need to change
//use dr and dc to set r and c as you recurse to the next positions
//insert only the longest word into result
//don't worru about the future iterations
/*
check row and column
case:
r +1
c+1
(r and c) +1
//check if the letter is a prefix or not a
*/
//if r == board [i][j] --> the ith value

if(r == board.size() || c == board.size())
{
	//checking the word in dictionary
	if(dict.find(word) != dict.end())
	{
		std::cout<<word<<std::endl;
		result.insert(word);
		//if(prefix.find(word) ==prefix.end())
		
		
		return true;
	}

	return false;
}
if(dr ==0 && r < board[0].size())
{
	//need to check per row
	word += board[r][c];
	c+=dc;
	//return boggleHelper(dict, prefix, board, word, result, r, c, dr,dc);
}
//two cases: board.size() and 
if(dc == 0 && r < board[0].size())
{
	word += board[r][c];
	r+=dr;
	//return boggleHelper(dict, prefix, board, word, result, r, c, dr, dc);
}
if(dc ==1 && dr ==1)
{
	word += board[r][c];
	c+=dc;
	r+=dr;
	//return boggleHelper(dict, prefix, board, word, result, r+1, c, dr,dc);
}

// bool search = boggleHelper(dict, prefix, board, word, result, r, c, dr, dc);

// if(search == false)
// {
// 	if(prefix.find(word)!=prefix.end())
// 	{
// 	if(dict.find(word)!= dict.end())
// 		{
// 			result.insert(word);
// 			return true;
// 		}
// 	}
// 	return false;
// }
// else
// {
// 	//search results in true --> check in dictionary
// 	if(dict.find(word) != dict.end())
// 	{
// 		result.insert(word);
// 		return true;
// 	}
// 	return false;
// }




//check if still prefix
if(prefix.find(word) != prefix.end())
{
 	bool search = boggleHelper(dict, prefix, board, word, result, r, c, dr, dc);
	//if this return false
	//check if word is in dict

	if(search == false)
	{
		if(dict.find(word)!= dict.end())
		{
			result.insert(word);
			return true;
		}

	}
	
	return search;
}
else
{
	if(dict.find(word) != dict.end())
	{
		result.insert(word);
		return true;
	}
	return false;

	//return;
}
//if it iss recurse
//otherwise check if word is in dict and return;

//recurse

//----------

}
