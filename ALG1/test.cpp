#include <iostream>
#include <vector>

std::vector<std::string> unique_names(const std::vector<std::string>& names1, const std::vector<std::string>& names2)
{
    std::vector<std::string> result;
    for ( int i = 0; i < 3; i++ ) {
        for ( int j = 0; j < 4; j++ ) {
            if ( names1[i] != result[j] || names2[i] != result[j] )
            result[j] = names1[i];
        }
    }

    return result;
}

int main()
{
    std::vector<std::string> names1 = {"Ava", "Emma", "Olivia"};
    std::vector<std::string> names2 = {"Olivia", "Sophia", "Emma"};
    
    std::vector<std::string> result = unique_names(names1, names2);
    for(auto element : result)
    {
        std::cout << element << ' '; // should print Ava Emma Olivia Sophia
    }
}