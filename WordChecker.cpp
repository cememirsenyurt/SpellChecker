#include "WordChecker.hpp"
#include <algorithm> // For std::sort and std::unique

WordChecker::WordChecker(const Set<std::string>& words)
    : words(words)
{
}

bool WordChecker::wordExists(const std::string& word) const
{
    return words.contains(word);
}

std::vector<std::string> WordChecker::findSuggestions(const std::string& word) const
{
    std::vector<std::string> suggestions;

    // Swapping adjacent characters
    for (size_t i = 0; i < word.length() - 1; ++i) {
        std::string swapped = word;
        std::swap(swapped[i], swapped[i + 1]);
        if (wordExists(swapped)) {
            suggestions.push_back(swapped);
        }
    }

    // Replacing characters with alphabet letters and inserting a character
    std::string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    for (size_t i = 0; i <= word.length(); ++i) { // Note the <= to handle insertions at the end
        for (char ch : alphabet) {
            // Inserting a character from the alphabet
            std::string inserted = word.substr(0, i) + ch + word.substr(i);
            if (wordExists(inserted)) {
                suggestions.push_back(inserted);
            }
            // Replacing a character only if i < word.length() to avoid out-of-bounds
            if (i < word.length()) {
                std::string replaced = word;
                replaced[i] = ch;
                if (wordExists(replaced)) {
                    suggestions.push_back(replaced);
                }
            }
        }
    }

    // Removing each character
    for (size_t i = 0; i < word.length(); ++i) {
        std::string removed = word.substr(0, i) + word.substr(i + 1);
        if (wordExists(removed)) {
            suggestions.push_back(removed);
        }
    }

    // Remove duplicate suggestions
    std::sort(suggestions.begin(), suggestions.end());
    auto last = std::unique(suggestions.begin(), suggestions.end());
    suggestions.erase(last, suggestions.end());

    return suggestions;
}
