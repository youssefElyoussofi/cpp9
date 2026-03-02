#include "PmergeMe.hpp"

void parsing(int ac, char **argv, std::vector<int> &nums)
{
    if (ac <= 2)
        throw std::logic_error("enter at least two argements without using quotes");
    nums.reserve(ac - 1);
    for (int i = 1; i < ac; i++)
    {
        char *rest;
        long nb = strtol(argv[i], &rest, 10);
        if (rest == argv[i] || *rest != '\0')
            throw std::logic_error("input not valid");
        if (nb > INT_MAX || nb < INT_MIN)
            throw std::logic_error("invalid number out of rand INT_MAX INT_MIN");
        if (nums.size() > 0 && find(nums.begin(), nums.end(), nb) != nums.end())
            throw std::logic_error("invalid input do not enter Duplicate Number");
        nums.push_back(nb);
    }
}

int main(int ac, char **av)
{
    std::vector<int> nums;
    double time1, time2;
    try
    {
        parsing(ac, av, nums);
        PmergeMe merge(nums);
        time1 = merge.algorithm(VECTOR);
        time2 = merge.algorithm(LIST);
        std::cout << "Before: ";
        merge.print_unsorted_numbers();
        std::cout << "After: ";
        merge.print_sorted_numbers(VECTOR);
        std::cout << "Time to process a range of " << nums.size() << " elements with std::vector : " << time1 << " us\n";
        std::cout << "Time to process a range of " << nums.size() << " elements with std::list : " << time2 << " us\n";
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
    return 0;
}