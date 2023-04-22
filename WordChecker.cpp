// WordChecker.cpp
//
// ICS 46 Winter 2022
// Project #4: Set the Controls for the Heart of the Sun
//
// Replace and/or augment the implementations below as needed to meet
// the requirements.

#include "WordChecker.hpp"

WordChecker::WordChecker(const Set<std::string>& words)
    : words{words}
{
}


bool WordChecker::wordExists(const std::string& word) const
{
    return words.contains(word);
}


std::vector<std::string> WordChecker::findSuggestions(const std::string& word) const
{
    // Nonsensical code because the compiler requires the member variables
    // 'words' to be used somewhere, or else it becomes a warning (which
    // turns into an error).
    
    std::vector<std::string> suggestion;
    bool x;

    if(word.length() >= 2)
    {
        for(unsigned int i = 0; i < word.length(); ++i)
        {
            std::string newString = word;
            newString[i] = word[i+1];
            newString[i+1] = word[i];
            
            if (std::find(suggestion.begin(), suggestion.end(), newString) != suggestion.end())
            {
                x = false;
            }
            else
            {
                x = true;
            }

            if(wordExists(newString) && x)
            {
                suggestion.push_back(newString);
            }
            else
            {

            }
        }
    }

    std::string abc = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    for(unsigned int i = 0; i < abc.length(); ++i)
    {
        for(unsigned int j = 0; j < word.length(); ++j)
        {
            std::string newString = word;
            newString.erase(j, 1);
            newString.insert(j, sizeof(char), abc[i]);
           
            if (std::find(suggestion.begin(), suggestion.end(), newString) != suggestion.end())
                {
                        x = false;
                            }
                                else
                                    {
                                            x = true;
                                                }


            if(wordExists(newString) && x)
            {
                suggestion.push_back(newString);
            }
            else
            {

            }
        }
    }

    for(unsigned int i = 0; i < word.length(); ++i)
    {
        std::string newString;
        newString = word;

        newString.erase(i, 1);
        
        if (std::find(suggestion.begin(), suggestion.end(), newString) != suggestion.end())
            {
                    x = false;
                        }
                            else
                                {
                                        x = true;
                                            }


        if(wordExists(newString) && x)
        {
            suggestion.push_back(newString);
        }
        else
        {

        }
    }

    for(unsigned int i = 0; i < abc.length(); ++i)
    {
        for(unsigned int j = 0; j < word.length(); ++j)
        {
            std::string newString;
            newString = word;

            if(newString[j] != abc[i])
            {
                newString[j] = abc[i];
            }
            
            if (std::find(suggestion.begin(), suggestion.end(), newString) != suggestion.end())
                {
                        x = false;
                            }
                                else
                                    {
                                            x = true;
                                                }


            if(wordExists(newString) && x)
            {
                suggestion.push_back(newString);
            }
            else
            {

            }
        }
    }
    
    for(unsigned int i = 0; i < word.length(); ++i)
    {
        std::string newString;
        std::string splited1;
        std::string splited2;

        newString = word;
        splited1 = word.substr(0, i);
        splited2 = word.substr(i, newString.length());
        
        if (std::find(suggestion.begin(), suggestion.end(), newString) != suggestion.end())
            {
                    x = false;
                        }
                            else
                                {
                                        x = true;
                                            }


        if(wordExists(splited1) && wordExists(splited2) && x)
        {
            std::string newVersion;
            newVersion = splited1 + " " + splited2;
            suggestion.push_back(newVersion);
        }
    }

    return suggestion;
}

