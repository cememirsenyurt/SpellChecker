# SpellChecker
This is a project to build a spell checker, similar to those found in word processors, text editors, or email clients.

The program will check spelling in the input text and report on misspellings, along with suggestions about potentially correct spellings. The project aims to implement efficient search structures critical to the spell checker's performance, capable of searching for words in a potentially large word set and providing suggestions for each misspelling.

Implementation
The project provides a spell checker that can be configured via standard input (i.e., std::cin) and writes its output to standard output (i.e., std::cout). The program is capable of doing two different things:

Given a file containing a word set and another file containing input text, it can check spelling in the input text and report on misspellings, along with suggestions about potentially correct spellings.
Given a file containing a word set and another file containing input text, it can do the work of a spell checker without displaying a result, instead displaying the CPU time required to perform the task.
The program includes a class called WordChecker that checks the spelling of words and makes appropriate suggestions when they're misspelled. The project also requires implementing three class templates that derive from an existing class template Set<ElementType>, which implements the concept of a set (i.e., a collection of search keys).

The three class templates that can be implemented are:

AVLSet<ElementType>, which is an AVL tree (or can be configured to skip the balancing and act as a binary search tree).
SkipListSet<ElementType>, which is a skip list.
HashSet<ElementType>, which is a hash table with separate chaining, implemented as a dynamically-allocated array of linked lists.
